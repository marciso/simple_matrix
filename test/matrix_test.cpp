#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "simple_matrix.hpp"
#include "addition.hpp"
#include "transpose.hpp"
#include "slice.hpp"
#include "compare.hpp"
#include "scalar.hpp"
#include "naive_multiplication.hpp"

using namespace ::testing;

using M = simple_matrix<double>;

struct simple_matrix_test : ::testing::Test
{
    M a{2,3, 1};
    M b{20,30, 2};

    M diag_1{10,10};
    M ones{10,10,1};
    M zeros{10,10};
    M twos{10,10,2};

    void SetUp() override
    {
        auto [r, c] = a.size();
        for(size_t i = 0; i < r; ++i)
            for(size_t j = 0; j < c; ++j)
                a.at(i,j) = (i+1)*100 + (j+1);

        std::tie(r, c) = b.size();
        for(size_t i = 0; i < r; ++i)
            for(size_t j = 0; j < c; ++j)
                b.at(i,j) = (i+1)*100 + (j+1);

        std::tie(r, c) = diag_1.size();
        for(size_t i = 0; i < std::min(r,c); ++i)
            diag_1.at(i,i) = 1.;
    }
};

TEST_F(simple_matrix_test, test_size)
{
    simple_matrix<float> m(2,3);
    EXPECT_EQ(2, m.size().first);
    EXPECT_EQ(3, m.size().second);

    EXPECT_EQ(0., m.at(0,0));
}

TEST_F(simple_matrix_test, init_value)
{
    M m(2,3, 42.);
    EXPECT_EQ(2, m.size().first);
    EXPECT_EQ(3, m.size().second);

    EXPECT_EQ(42., m.at(0,0));
    EXPECT_EQ(42., m.at(0,1));
    EXPECT_EQ(42., m.at(0,2));
    EXPECT_EQ(42., m.at(1,0));
    EXPECT_EQ(42., m.at(1,1));
    EXPECT_EQ(42., m.at(1,2));
}

TEST_F(simple_matrix_test, init_ctor)
{
    M m(2,3, {{1,2,3}, {4,5,6}});

    EXPECT_EQ(1., m.at(0,0));
    EXPECT_EQ(2., m.at(0,1));
    EXPECT_EQ(3., m.at(0,2));
    EXPECT_EQ(4., m.at(1,0));
    EXPECT_EQ(5., m.at(1,1));
    EXPECT_EQ(6., m.at(1,2));

    EXPECT_THROW(M(2,3, {{1,2,3}, {4,5}}), std::out_of_range);
    EXPECT_THROW(M(2,3, std::vector<std::vector<double>>()), std::out_of_range);
}

TEST_F(simple_matrix_test, add_and_sub_long)
{
    M a(2,3, 1);
    M b(2,3, 2);

    auto c = add(a,b);
    auto d = substract(a,b);

    EXPECT_EQ(3., c.at(0,0));
    EXPECT_EQ(3., c.at(0,1));
    EXPECT_EQ(3., c.at(0,2));
    EXPECT_EQ(3., c.at(1,0));
    EXPECT_EQ(3., c.at(1,1));
    EXPECT_EQ(3., c.at(1,2));

    EXPECT_EQ(-1., d.at(0,0));
    EXPECT_EQ(-1., d.at(0,1));
    EXPECT_EQ(-1., d.at(0,2));
    EXPECT_EQ(-1., d.at(1,0));
    EXPECT_EQ(-1., d.at(1,1));
    EXPECT_EQ(-1., d.at(1,2));
}

TEST_F(simple_matrix_test, add_and_sub)
{
    M a(2,3, 1);
    M b(2,3, 2);

    auto c = a + b;
    auto d = a - b;

    M e(2,3, 3);
    EXPECT_EQ(e, c);

    e = M(2,3, -1.);
    EXPECT_EQ(e, d);
}

TEST_F(simple_matrix_test, add_2)
{
    auto c = add(diag_1, twos);

    EXPECT_EQ(3., c.at(0,0));
    EXPECT_EQ(2., c.at(0,1));
    EXPECT_EQ(2., c.at(0,2));
    EXPECT_EQ(2., c.at(1,0));
    EXPECT_EQ(3., c.at(1,1));
    EXPECT_EQ(2., c.at(1,2));
}

TEST_F(simple_matrix_test, out)
{
    std::ostringstream os[2];
    os[0] << a;
    os[1] << b;
    EXPECT_THAT(os[0].str(), HasSubstr("101"));
    EXPECT_THAT(os[1].str(), HasSubstr("..."));

    std::cout << a << std::endl;
    std::cout << b << std::endl;
}

TEST_F(simple_matrix_test, out_transposed)
{
    std::ostringstream os[2];
    os[0] << transpose(a);
    os[1] << transpose(b);
    EXPECT_THAT(os[0].str(), HasSubstr("101"));
    EXPECT_THAT(os[1].str(), HasSubstr("..."));

    std::cout << os[0].str() << std::endl;
    std::cout << os[1].str() << std::endl;
}

TEST_F(simple_matrix_test, out_sliced)
{
    std::ostringstream os[3];
    os[0] << slice(b, 1, 1);
    EXPECT_EQ(to_string(M{1,1, 101}), os[0].str());
    auto t = transpose(b);
    os[1] << slice(b, 2, 3);
    os[2] << slice(b, 2, 3, 2, 2);
    EXPECT_EQ(to_string(M{2,3, {{101, 102, 103}, {201, 202, 203}}}), os[1].str());
    EXPECT_EQ(to_string(M{2,3, {{303, 304, 305}, {403, 404, 405}}}), os[2].str());
}

TEST_F(simple_matrix_test, slice_throws_out_of_range)
{
    EXPECT_THROW(slice(a, 5, 5), std::out_of_range );
}

TEST_F(simple_matrix_test, slice_same_size)
{
    slice s(a, a.size());
    EXPECT_EQ(a.size(), s.size());
}

TEST_F(simple_matrix_test, scalar_add_sub)
{
    EXPECT_EQ(twos, 1+ones);
    EXPECT_EQ(ones, 1+zeros);
    EXPECT_EQ(zeros+1, 1+zeros);
    EXPECT_EQ((M{10,10, 12}), 10+twos);
    EXPECT_EQ((M{10,10, 42}), twos+40);
    EXPECT_EQ(zeros, 1-ones);
    EXPECT_EQ(ones, 1-zeros);
    EXPECT_EQ((M{10,10, -1}), zeros-1);
    EXPECT_EQ((M{10,10, -8}), twos-10);
}

TEST_F(simple_matrix_test, scalar_mul_div)
{
    EXPECT_EQ(zeros, 0*ones);
    EXPECT_EQ(+ones, 1*ones);
    EXPECT_EQ(-ones, -1*ones);
    EXPECT_EQ(twos, 2*ones);
    EXPECT_EQ(zeros, ones*0);
    EXPECT_EQ((M{10,10, 42}), 20*twos + 2);
    EXPECT_EQ(ones, twos/2);
    EXPECT_EQ((M{10,10, 0.5}), 1/twos);
}

TEST_F(simple_matrix_test, naive_multiply)
{
    EXPECT_EQ(10*twos, naive_multiply(ones, twos));
    EXPECT_NE(diag_1, naive_multiply(diag_1, ones));
    EXPECT_EQ(10*ones, naive_multiply(ones, ones));

    EXPECT_EQ(
            (M{2,3, {{88,9,26},{56,33,62}}}),
            naive_multiply(
                M{2,2, {{11,3},{7,11}}},
                M{2,3, {{8,0,1},{0,3,5}}}));

    EXPECT_EQ(
            (M{2,2, {{11,0},{35,20}}}),
            naive_multiply(
                M{2,3, {{0,-1,2},{4,11,2}}},
                M{3,2, {{3,-1},{1,2},{6,1}}}));

    M a(4,4,{
        {-2, 4, 3,-3},
        { 5, 2, 0, 6},
        { 7,-1,-4, 1},
        { 8, 9,10,11}});
    M b(4,4,{
        {12, 4,-2,-3},
        { 3, 2, 5, 0},
        { 6, 7,13,-1},
        { 8, 1,-4, 9}});
    M c(4,4,{
        {-18, 18, 75,-24},
        {114, 30,-24, 39},
        { 65, -1,-75, -8},
        {271,131,115, 65}});

    EXPECT_EQ(c, naive_multiply(a,b));
}

TEST_F(simple_matrix_test, div_and_conq_multiply)
{
    EXPECT_EQ(10*twos, div_and_conq_multiply(ones, twos));
    EXPECT_NE(diag_1, div_and_conq_multiply(diag_1, ones));
    EXPECT_EQ(10*ones, div_and_conq_multiply(ones, ones));

    EXPECT_EQ(
            (M{2,3, {{88,9,26},{56,33,62}}}),
            div_and_conq_multiply(
                M{2,2, {{11,3},{7,11}}},
                M{2,3, {{8,0,1},{0,3,5}}}));

    EXPECT_EQ(
            (M{2,2, {{11,0},{35,20}}}),
            div_and_conq_multiply(
                M{2,3, {{0,-1,2},{4,11,2}}},
                M{3,2, {{3,-1},{1,2},{6,1}}}));

    M a(4,4,{
        {-2, 4, 3,-3},
        { 5, 2, 0, 6},
        { 7,-1,-4, 1},
        { 8, 9,10,11}});
    M b(4,4,{
        {12, 4,-2,-3},
        { 3, 2, 5, 0},
        { 6, 7,13,-1},
        { 8, 1,-4, 9}});
    M c(4,4,{
        {-18, 18, 75,-24},
        {114, 30,-24, 39},
        { 65, -1,-75, -8},
        {271,131,115, 65}});

    EXPECT_EQ(c, div_and_conq_multiply(a,b));
}


