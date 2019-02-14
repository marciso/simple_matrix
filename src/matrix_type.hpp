#pragma once
#include <type_traits>

struct matrix_type {};

template<typename M> using is_matrix_type = std::is_base_of<matrix_type,M>;
template<typename M> inline constexpr bool is_matrix_type_v = is_matrix_type<M>::value;

