#pragma once
#include "apply.hpp"
#include "matrix_type.hpp"

template<typename A, typename B, typename R = A>
    typename std::enable_if_t<is_matrix_type_v<A> && is_matrix_type_v<B>, R>
add(A const & a, B const & b)
{
    return apply_op([](auto x, auto y){return x+y;}, a, b, R{a.size()});
}

template<typename A, typename B, typename R = A>
    typename std::enable_if_t<is_matrix_type_v<A> && is_matrix_type_v<B>, R>
substract(A const & a, B const & b)
{
    return apply_op([](auto x, auto y){return x-y;}, a, b, R{a.size()});
}

template<typename A, typename B, typename R = A>
    typename std::enable_if_t<is_matrix_type_v<A> && is_matrix_type_v<B>, R>
operator+(A const & a, B const & b) { return add(a,b); }

template<typename A, typename B, typename R = A>
    typename std::enable_if_t<is_matrix_type_v<A> && is_matrix_type_v<B>, R>
operator-(A const & a, B const & b) { return substract(a,b); }
