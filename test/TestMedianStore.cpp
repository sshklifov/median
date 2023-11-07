#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "MedianStore.hpp"
#include <random>
#include <algorithm>

TEST_CASE("empty container check") {
    MedianStore m;
    CHECK_THROWS(m.getMedian());
}

TEST_CASE("odd elements median") {
    MedianStore m;
    m.push(1);
    m.push(2);
    m.push(18);
    m.push(3);
    m.push(4);

    CHECK(m.getMedian() == 3.f);
}

TEST_CASE("even elements median") {
    MedianStore m;
    m.push(10);
    m.push(14);
    m.push(17);
    m.push(20);
    m.push(8);
    m.push(19);

    CHECK(m.getMedian() == 15.5f);
}

TEST_CASE("overflow check") {
    MedianStore m;
    m.push(INT_MAX);
    m.push(INT_MAX);
    CHECK(m.getMedian() == doctest::Approx(INT_MAX));
}

TEST_CASE("underflow check") {
    MedianStore m;
    m.push(INT_MIN);
    m.push(INT_MIN);
    CHECK(m.getMedian() == doctest::Approx(INT_MIN));
}

TEST_CASE("repeated elements") {
    MedianStore m;
    const int repeated = 5;
    m.push(repeated);
    m.push(20);
    m.push(repeated);
    m.push(3);
    m.push(repeated);
    m.push(9);
    m.push(repeated);
    CHECK(m.getMedian() == repeated);
}

TEST_CASE("a hundred elements") {
    MedianStore m;
    for (int i = 0; i < 100; ++i) {
        m.push(i);
        float median = i / 2.f;
        CHECK(m.getMedian() == median);
    }
}

TEST_CASE("bench test") {
    const unsigned seed = 9;
    std::default_random_engine eng(seed);
    std::uniform_int_distribution<int> distribution(INT_MIN, INT_MAX);

    const int tries = 10;
    const int n = 10'001;
    for (int t = 0; t < tries; ++t) {
        MedianStore m;
        std::vector<int> v;
        v.reserve(n);
        for (int i = 0; i < n; ++i) {
            int r = distribution(eng);
            m.push(r);
            v.push_back(r);
        }
        std::vector<int>::iterator medianIt = v.begin() + n / 2;
        std::nth_element(v.begin(), medianIt, v.end());
        CHECK(m.getMedian() == *medianIt);
    }
}
