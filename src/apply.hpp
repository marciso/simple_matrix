#pragma once
#include"matrix_type.hpp"
#include<stdexcept>
#include<type_traits>
#include<utility>

template<typename A, typename B, typename R, typename Op>
    typename std::enable_if_t<is_matrix_type_v<A> && is_matrix_type_v<B>, R> &&
call_op(Op op, A const& a, B const& b, R && result)
{
    auto const sz = a.size();
    if (sz != b.size()) throw std::out_of_range("cannot apply operation on matrices of different size");
    if (sz != result.size()) throw std::out_of_range("result of different size");
    auto const [n,m] = sz;

    for(size_t i = 0; i < n; ++i)
        for(size_t j = 0; j < m; ++j)
            op(a.at(i,j), b.at(i,j), result.at(i,j));

    return std::move(result);
}

template<typename A, typename B, typename R, typename Op>
    typename std::enable_if_t<is_matrix_type_v<A> && is_matrix_type_v<B>, R> &&
apply_op(Op op, A const& a, B const& b, R && result)
{
    return call_op(
            [&op](auto x, auto y, auto & r) { r = op(x, y); },
            a, b, std::forward<R>(result));
}

template<typename A, typename R, typename Op>
    typename std::enable_if_t<is_matrix_type_v<A>, R> &&
call_op(Op op, A const& a, R && result)
{
    auto const sz = a.size();
    if (sz != result.size()) throw std::out_of_range("result of different size");
    auto const [n,m] = sz;

    for(size_t i = 0; i < n; ++i)
        for(size_t j = 0; j < m; ++j)
            op(a.at(i,j), result.at(i,j));

    return std::move(result);
}

template<typename A, typename R, typename Op>
    typename std::enable_if_t<is_matrix_type_v<A>, R> &&
apply_op(Op op, A const& a, R && result)
{
    return call_op(
            [&op](auto x, auto & r) { r = op(x); },
            a, std::forward<R>(result));
}

