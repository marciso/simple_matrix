#pragma once
#include "apply.hpp"
#include "matrix_type.hpp"
#include <type_traits>

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
scalar_add(M const & a, V && v)
{
    return apply_op([v](auto x){ return x+v;}, a, R{a.size()});
}

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
scalar_add(V && v, M const & a)
{
    return apply_op([v](auto x){ return v+x;}, a, R{a.size()});
}

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
scalar_substract(M const & a, V && v)
{
    return apply_op([v](auto x){ return x-v;}, a, M{a.size()});
}

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
scalar_substract(V && v, M const & a)
{
    return apply_op([v](auto x){ return v-x;}, a, R{a.size()});
}

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
scalar_multiply(M const & a, V && v)
{
    return apply_op([v](auto x){ return x*v;}, a, R{a.size()});
}

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
scalar_multiply(V && v, M const & a)
{
    return apply_op([v](auto x){ return v*x;}, a, R{a.size()});
}

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
scalar_divide(M const & a, V && v)
{
    return apply_op([v](auto x){ return x/v;}, a, R{a.size()});
}

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
scalar_divide(V && v, M const & a)
{
    return apply_op([v](auto x){ return v/x;}, a, R{a.size()});
}

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
operator+(V && v, M const & m) { return scalar_add<M,V,R>(std::forward<V>(v), m); }

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
operator+(M const & m, V && v) { return scalar_add<M,V,R>(m, std::forward<V>(v)); }

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
operator-(V && v, M const & m) { return scalar_substract<M,V,R>(std::forward<V>(v), m); }

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
operator-(M const & m, V && v) { return scalar_substract<M,V,R>(m, std::forward<V>(v)); }

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
operator*(V && v, M const & m) { return scalar_multiply<M,V,R>(std::forward<V>(v), m); }

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
operator*(M const & m, V && v) { return scalar_multiply<M,V,R>(m, std::forward<V>(v)); }

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
operator/(M const & m, V && v) { return scalar_divide<M,V,R>(m, std::forward<V>(v)); }

template<typename M, typename V = typename M::value_type, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M> && std::is_convertible_v<V, typename M::value_type>, R>
operator/(V && v, M const & m) { return scalar_divide<M,V,R>(std::forward<V>(v), m); }

template<typename M, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M>, R>
operator-(M const & m) { return apply_op([](auto x){ return -x;}, m, R{m.size()}); }

template<typename M, typename R = M>
    std::enable_if_t<std::is_base_of_v<matrix_type,M>, R>
operator+(M const & m) { return R{m}; }

