#pragma once
#include"matrix_type.hpp"
#include<cstdlib>
#include<utility>
#include<stdexcept>
#include<cassert>

template<typename M>
struct slice : public matrix_type
{
    using value_type = typename M::value_type;
    using reference = typename M::reference;
    using const_reference = typename M::const_reference;

    slice(M & m, size_t rows, size_t cols, size_t row_offset, size_t col_offset)
        : m(m), rows(rows), cols(cols), row_offset(row_offset), col_offset(col_offset)
    {
        auto const [r, c] = m.size();
        if ((row_offset + rows > r) || (col_offset + cols > c)) {
            throw std::out_of_range("slice bigger than original matrix");
        }
    }
    slice(M & m, std::pair<size_t, size_t> sz, std::pair<size_t, size_t> offset)
        : slice(m, std::get<0>(sz), std::get<1>(sz), std::get<0>(offset), std::get<1>(offset)) {}

    slice(M & m, size_t rows, size_t cols) : slice(m, rows, cols, 0, 0) {}
    slice(M & m, std::pair<size_t, size_t> sz) : slice(m, std::get<0>(sz), std::get<1>(sz), 0, 0) {}
    slice(M & m) : slice(m, m.size()) {}

    auto size() const { return std::make_pair(rows, cols); }

    M copy() const {
        M r(size());
        for(size_t i = 0; i < std::get<0>(r.size()); ++i)
            for(size_t j = 0; j < std::get<1>(r.size()); ++j)
                r.at(i,j) = at(i,j);
        return r;
    }

    slice<M> split(size_t rows, size_t cols, size_t row_off = 0, size_t col_off = 0) const
    {
        assert( this->rows >= rows && this->cols >= cols );
        return slice(m, rows, cols, row_offset + row_off, col_offset + col_off);
    }

    std::pair<slice<M>, slice<M>> halve_horizontally() const
    {
        return std::make_pair(split(rows/2, cols, 0, 0), split(rows-rows/2, cols, rows/2, 0));
    }

    std::pair<slice<M>, slice<M>> halve_vertically() const
    {
        return std::make_pair(split(rows, cols/2, 0, 0), split(rows, cols-cols/2, 0, cols/2));
    }

    reference at(size_t r, size_t c) {
        assert( r < rows && c < cols);
        return m.at(r+row_offset, c+col_offset);
    }
    const_reference at(size_t r, size_t c) const {
        assert( r < rows && c < cols);
        return m.at(r+row_offset, c+col_offset);
    }
private:
    M & m;
    size_t rows;
    size_t cols;
    size_t row_offset = 0;
    size_t col_offset = 0;
};
