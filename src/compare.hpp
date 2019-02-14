#pragma once
#include"matrix_type.hpp"
#include<cstdlib>
#include<utility>
#include<type_traits>

template<typename A, typename B>
    typename std::enable_if<
        std::is_base_of<matrix_type,A>::value &&
        std::is_base_of<matrix_type,B>::value, bool>::type
equal(A const & a, B const & b)
{
    auto asz = a.size();
    auto bsz = b.size();
    if (asz == bsz) {
        for(size_t i = 0; i < std::get<0>(asz); ++i)
            for(size_t j = 0; j < std::get<1>(asz); ++j)
                if ( a.at(i,j) != b.at(i,j) ) return false;
        return true;
    }
    return false;
}

template<typename A, typename B, typename Cmp>
    typename std::enable_if<
        std::is_base_of<matrix_type,A>::value &&
        std::is_base_of<matrix_type,B>::value, bool>::type
equal(A const & a, B const & b, Cmp cmp)
{
    auto asz = a.size();
    auto bsz = b.size();
    if (asz == bsz) {
        for(size_t i = 0; i < std::get<0>(asz); ++i)
            for(size_t j = 0; j < std::get<1>(asz); ++j)
                if ( !cmp(a.at(i,j), b.at(i,j)) ) return false;
        return true;
    }
    return false;
}

template<typename A, typename B>
    typename std::enable_if<
        std::is_base_of<matrix_type,A>::value &&
        std::is_base_of<matrix_type,B>::value, bool>::type
operator==(A const & a, B const & b) { return equal(a, b); }

template<typename A, typename B>
    typename std::enable_if<
        std::is_base_of<matrix_type,A>::value &&
        std::is_base_of<matrix_type,B>::value, bool>::type
operator!=(A const & a, B const & b) { return !equal(a, b); }


