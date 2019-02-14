#pragma once
#include"matrix_type.hpp"
#include<cstdlib>
#include<algorithm>
#include<string>
#include<sstream>
#include<ios>
#include<iomanip>
#include<functional>
#include<type_traits>

template<typename M, typename Fmt = std::function<std::string(typename M::value_type)>>
typename std::enable_if<std::is_base_of<matrix_type, M>::value, size_t>::type
output_cell_space(M const & m,
        size_t max_rows = 5, size_t max_cols = 5,
        Fmt fmt = [](auto x){ return std::to_string(x); })
{
    auto const [r, c] = m.size();
    size_t const rr = std::min(r, max_rows);
    size_t const cc = std::min(c, max_cols);
    size_t cell_space = 0;
    for(size_t i = 0; i < rr; ++i)
        for(size_t j = 0; j < cc; ++j)
            cell_space = std::max(cell_space, std::to_string(m.at(i, j)).length());
    for(size_t j = 0; j < cc; ++j)
        cell_space = std::max(cell_space, std::to_string(m.at(r-1, j)).length());
    for(size_t i = 0; i < rr; ++i)
        cell_space = std::max(cell_space, std::to_string(m.at(i, c-1)).length());
    cell_space = std::max(cell_space, std::to_string(m.at(r-1, c-1)).length());

    return cell_space + 1;
}

template<typename M, typename Fmt = std::function<std::string(typename M::value_type)>, typename ostream = std::ostream>
typename std::enable_if<std::is_base_of<matrix_type, M>::value, ostream>::type &
output_debug(ostream & o, M const & m,
        size_t max_rows_ = 5, size_t max_cols_ = 5,
        Fmt fmt = [](auto x){ return std::to_string(x); })
{
    size_t max_rows = std::max<size_t>(3, max_rows_)-2;
    size_t max_cols = std::max<size_t>(3, max_cols_)-2;
    size_t cell_space = output_cell_space(m, max_rows, max_cols, fmt);

    char const * const rs = ",";
    char const * const nl = "]\n";
    char const * const tab = "\t[";
    char const * const elipsis = "...";

    char const * sep = tab;
    auto const [r, c] = m.size();
    o << "(" << r << "x" << c << ") matrix:\n";
    size_t i = 0;
    while(i < r) {
        size_t j = 0;
        if ( i < max_rows || i+1 == r) {
            while(j < c) {
                if ( j < max_cols || j+1 == c) {
                    o << sep << std::setfill(' ') << std::setw(cell_space) << std::right << fmt(m.at(i,j));
                    sep = rs;
                }
                else if ( j+2 < c ) {
                    o << sep << std::setfill(' ') << std::setw(cell_space) << std::right << elipsis;
                    sep = rs;
                    j = c - 2;
                }
                ++j;
            }
        }
        else if ( i+2 < r ) {
            while(j < c) {
                if ( j < max_cols || j+1 == c) {
                    o << sep << std::setfill(' ') << std::setw(cell_space) << std::right << elipsis;
                    sep = rs;
                }
                else if ( j+2 < c ) {
                    o << sep << std::setfill(' ') << std::setw(cell_space) << std::right << ' ';
                    sep = " ";
                    j = c - 2;
                }
                j++;
            }
            i = r - 2;
        }
        ++i;
        o << nl;
        sep = tab;
    }
    o << "\n";

    return o;
}

template<typename M>
    typename std::enable_if_t<std::is_base_of_v<matrix_type, M>, std::ostream> &
operator<<(std::ostream & o, M const & m)
{
    return output_debug(o, m);
}

template<typename M>
    typename std::enable_if_t<std::is_base_of_v<matrix_type, M>, std::string>
to_string(M const & m)
{
    std::ostringstream os;
    return output_debug(os, m).str();
}

