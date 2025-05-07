#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vektorius.h" 

TEST_CASE("Vector push_back() veikla") {
    Vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    REQUIRE(vec.size() == 2);
    REQUIRE(vec[0] == 10);
    REQUIRE(vec[1] == 20);
}

TEST_CASE("Vector operator[] skaito ir raso") {
    Vector<int> vec(3, 0);
    vec[0] = 5;
    vec[1] = 10;
    REQUIRE(vec[0] == 5);
    REQUIRE(vec[1] == 10);
    REQUIRE(vec[2] == 0);
}

TEST_CASE("Vector copy kosntruktorius veikia teisingai") {
    Vector<int> original;
    original.push_back(1);
    original.push_back(2);

    Vector<int> copy = original;
    REQUIRE(copy.size() == original.size());
    REQUIRE(copy[0] == original[0]);
    REQUIRE(copy[1] == original[1]);
}

TEST_CASE("Vector at() std::out_of_range ismeta invalind") {
    Vector<int> vec(3, 1);
    CHECK_THROWS_AS(vec.at(3), std::out_of_range);
    CHECK_NOTHROW(vec.at(2));
    REQUIRE(vec.at(2) == 1);
}

TEST_CASE("Vector move constructor gerai perne") {
    Vector<int> vec1;
    vec1.push_back(42);
    vec1.push_back(99);

    Vector<int> vec2 = std::move(vec1);
    REQUIRE(vec2.size() == 2);
    REQUIRE(vec2[0] == 42);
    REQUIRE(vec2[1] == 99);
}
