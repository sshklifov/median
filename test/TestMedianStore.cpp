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
    m.add(1);
    m.add(2);
    m.add(18);
    m.add(3);
    m.add(4);

    CHECK(m.getMedian() == 3.f);
}

TEST_CASE("even elements median") {
    MedianStore m;
    m.add(10);
    m.add(14);
    m.add(17);
    m.add(20);
    m.add(8);
    m.add(19);

    CHECK(m.getMedian() == 15.5f);
}

TEST_CASE("overflow check") {
    MedianStore m;
    m.add(INT_MAX);
    m.add(INT_MAX);
    CHECK(m.getMedian() == doctest::Approx(INT_MAX));
}

TEST_CASE("underflow check") {
    MedianStore m;
    m.add(INT_MIN);
    m.add(INT_MIN);
    CHECK(m.getMedian() == doctest::Approx(INT_MIN));
}

TEST_CASE("repeated elements") {
    MedianStore m;
    const int repeated = 5;
    m.add(repeated);
    m.add(20);
    m.add(repeated);
    m.add(3);
    m.add(repeated);
    m.add(9);
    m.add(repeated);
    CHECK(m.getMedian() == repeated);
}

TEST_CASE("a hundred elements") {
    MedianStore m;
    for (int i = 0; i < 100; ++i) {
        m.add(i);
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
            m.add(r);
            v.push_back(r);
        }
        std::vector<int>::iterator medianIt = v.begin() + n / 2;
        std::nth_element(v.begin(), medianIt, v.end());
        CHECK(m.getMedian() == *medianIt);
    }
}
