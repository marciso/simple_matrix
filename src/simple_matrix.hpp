#pragma once
#include"matrix_type.hpp"
#include"output.hpp"
#include<cstdlib>
#include<vector>
#include<cassert>
#include<utility>
#include<algorithm>
#include<ostream>
#include<stdexcept>

template<typename T>
struct simple_matrix : public matrix_type
{
    using value_type = T;
    using reference = T&;
    using const_reference = T const&;

    auto size() const { return std::make_pair(rows, cols); }

    simple_matrix(size_t rows, size_t cols, value_type const & value = value_type{})
        : rows(rows), cols(cols), data(rows*cols, value) {}

    simple_matrix(std::pair<size_t, size_t> sz, value_type const & value = value_type{})
        : simple_matrix(std::get<0>(sz), std::get<1>(sz), value) {}

    simple_matrix(size_t rows, size_t cols, std::vector<std::vector<value_type>> const & values)
        : rows(rows), cols(cols), data(rows*cols)
    {
        for(size_t i = 0; i < rows; ++i) {
            for(size_t j = 0; j < cols; ++j) {
                at(i, j) = values.at(i).at(j); // throws
            }
        }
    }

    template<typename M, typename = std::enable_if_t<std::is_base_of_v<matrix_type, M>>>
        simple_matrix(size_t rows, size_t cols, M const & values)
        : rows(rows), cols(cols), data(rows*cols)
        {
            auto sz = values.size();
            if ( rows > std::get<0>(sz) ) throw std::out_of_range("rows out of range");
            if ( cols > std::get<1>(sz) ) throw std::out_of_range("columns out of range");
            for(size_t i = 0; i < rows; ++i) {
                for(size_t j = 0; j < cols; ++j) {
                    at(i, j) = values.at(i, j);
                }
            }
        }

    void fill(value_type const & value) { std::fill(std::begin(data), std::end(data), value); }

    reference at(size_t r, size_t c) {
        assert(r < rows);
        assert(c < cols);
        return data[cols*r+c];
    }

    const_reference at(size_t r, size_t c) const {
        assert(r < rows);
        assert(c < cols);
        return data[cols*r+c];
    }

private:
    size_t rows;
    size_t cols;
    std::vector<T> data;
};

