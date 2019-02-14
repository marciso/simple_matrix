#pragma once
#include "matrix_type.hpp"
#include "slice.hpp"
#include <stdexcept>
#include <utility>
#include <type_traits>
#include <algorithm>
#include <cassert>

template<typename A, typename B, typename R>
    typename std::enable_if_t<is_matrix_type_v<A> && is_matrix_type_v<B>, void>
naive_multiply_result_impl(A const & a, B const & b, R & result, size_t n, size_t m, size_t p)
{
    for(size_t i = 0; i < n; ++i)
        for(size_t j = 0; j < p; ++j)
            for(size_t k = 0; k < m; ++k)
                result.at(i, j) += a.at(i, k) * b.at(k, j);
}

template<typename A, typename B, typename R>
    typename std::enable_if_t<is_matrix_type_v<A> && is_matrix_type_v<B>, R> &&
naive_multiply_result(A const & a, B const & b, R && result)
{
    auto const [ar,ac] = a.size();
    auto const [br,bc] = b.size();
    auto const [cr,cc] = result.size();
    if (ac != br || ar != cr || bc != cc )
        throw std::out_of_range("wrong matrices' sizes for multiplication");

    naive_multiply_result_impl(a, b, result, ar, ac, bc);
    return std::move(result);
}

template<typename R, typename A, typename B>
    typename std::enable_if_t<is_matrix_type_v<A> && is_matrix_type_v<B>, R>
naive_multiply_as(A const & a, B const & b)
{
    return naive_multiply_result(a, b, R{std::get<0>(a.size()), std::get<1>(b.size())});
}

template<typename A, typename B, typename R = A>
    typename std::enable_if_t<is_matrix_type_v<A> && is_matrix_type_v<B>, R>
naive_multiply(A const & a, B const & b)
{
    return naive_multiply_result(a, b, R{std::get<0>(a.size()), std::get<1>(b.size())});
}

template<size_t threshold, typename A, typename B, typename R>
    typename std::enable_if_t<is_matrix_type_v<A> && is_matrix_type_v<B>, void>
div_and_conq_multiply_rec(slice<A> const & a, slice<B> const & b, slice<R> & result, size_t n, size_t m, size_t p)
{
    assert( n == a.size().first && n == result.size().first );
    assert( m == b.size().first && m == a.size().second );
    assert( p == b.size().second && p == result.size().second );
    size_t s = std::max({n,m,p});
    if ( s <= threshold ) {
        naive_multiply_result_impl(a, b, result, n, m, p);
    }
    else {
        if ( s == n ) {
            // slice A horizontally
            auto [a1, a2] = a.halve_horizontally();
            auto [r1, r2] = result.halve_horizontally();
            div_and_conq_multiply_rec<threshold>(a1, b, r1, a1.size().first, m, p);
            div_and_conq_multiply_rec<threshold>(a2, b, r2, a2.size().first, m, p);
        }
        else if ( s == p ) {
            // slice B vertically
            auto [b1, b2] = b.halve_vertically();
            auto [r1, r2] = result.halve_vertically();
            div_and_conq_multiply_rec<threshold>(a, b1, r1, n, m, b1.size().second);
            div_and_conq_multiply_rec<threshold>(a, b2, r2, n, m, b2.size().second);
        }
        else {
            assert( s == m );
            // slice A vertically and B horizontally
            auto [a1, a2] = a.halve_vertically();
            auto [b1, b2] = b.halve_horizontally();
            div_and_conq_multiply_rec<threshold>(a1, b1, result, n, a1.size().second, p);
            // addition of the results is implicit
            div_and_conq_multiply_rec<threshold>(a2, b2, result, n, a2.size().second, p);
        }
    }
}

template<typename A, typename B, typename R>
    typename std::enable_if_t<is_matrix_type_v<A> && is_matrix_type_v<B>, R> &&
div_and_conq_multiply_result(A const & a, B const & b, R && result)
{
    auto const [ar,ac] = a.size();
    auto const [br,bc] = b.size();
    auto const [cr,cc] = result.size();
    if (ac != br || ar != cr || bc != cc )
        throw std::out_of_range("wrong matrices' sizes for multiplication");

    constexpr size_t threshold = 2; // FIXME: increase sensibly
    auto r = slice(result);
    div_and_conq_multiply_rec<threshold>(slice(a), slice(b), r, ar, ac, bc);
    return std::move(result);
}

template<typename R, typename A, typename B>
    typename std::enable_if_t<is_matrix_type_v<A> && is_matrix_type_v<B>, R>
div_and_conq_multiply_as(A const & a, B const & b)
{
    return div_and_conq_multiply_result(a, b, R{std::get<0>(a.size()), std::get<1>(b.size())});
}

template<typename A, typename B, typename R = A>
    typename std::enable_if_t<is_matrix_type_v<A> && is_matrix_type_v<B>, R>
div_and_conq_multiply(A const & a, B const & b)
{
    return div_and_conq_multiply_result(a, b, R{std::get<0>(a.size()), std::get<1>(b.size())});
}



