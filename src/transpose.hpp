#pragma once
#include"matrix_type.hpp"
#include<cstdlib>
#include<utility>
#include<ostream>

template<typename M>
struct transpose : public matrix_type
{
    using value_type = typename M::value_type;
    using reference = typename M::reference;
    using const_reference = typename M::const_reference;

    transpose(M & m) : m(m) {}

    void fill(value_type const & value) { m.fill(value); }

    M copy() const {
        M r(size());
        for(size_t i = 0; i < std::get<0>(r.size()); ++i)
            for(size_t j = 0; j < std::get<1>(r.size()); ++j)
                r.at(i,j) = at(j,i);
        return r;
    }

    auto size() const { return std::make_pair(std::get<1>(m.size()), std::get<0>(m.size())); }

    reference at(size_t r, size_t c) { return m.at(c, r); }
    const_reference at(size_t r, size_t c) const { return m.at(c, r); }
private:
    M & m;
};

