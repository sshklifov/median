#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "Heap.hpp"
#include <random>
#include <algorithm>
#include <set>

TEST_CASE("empty container check") {
    MaxHeap h;
    CHECK_THROWS(h.top());
    CHECK_THROWS(h.pop());

    int newTop = 0;
    CHECK_THROWS(h.exchangeTop(newTop));
}

TEST_CASE("five element container") {
    SUBCASE("MinHeap") {
        MinHeap h;
        h.push(1);
        h.push(2);
        h.push(18);
        h.push(3);
        h.push(4);

        CHECK(h.size() == 5);
        CHECK(!h.empty());

        CHECK(h.top() == 1);
        h.pop();
        CHECK(h.top() == 2);
        h.pop();
        CHECK(h.top() == 3);
        h.pop();
        CHECK(h.top() == 4);
        h.pop();
        CHECK(h.top() == 18);
        h.pop();

        CHECK(h.empty());
    }

    SUBCASE("MaxHeap") {
        MaxHeap h;
        h.push(2);
        h.push(17);
        h.push(18);
        h.push(7);
        h.push(5);

        CHECK(h.size() == 5);
        CHECK(!h.empty());

        CHECK(h.top() == 18);
        h.pop();
        CHECK(h.top() == 17);
        h.pop();
        CHECK(h.top() == 7);
        h.pop();
        CHECK(h.top() == 5);
        h.pop();
        CHECK(h.top() == 2);
        h.pop();

        CHECK(h.empty());
    }
}

TEST_CASE("exchangeTop") {
    SUBCASE("MaxHeap") {
        MaxHeap h;
        h.push(7);
        h.push(1);
        h.push(19);
        h.push(6);
        h.push(8);
        h.push(20);

        int top = 13;
        h.exchangeTop(top); //< h = {19 13 8 7 6 1}
        CHECK(top == 20);
        CHECK(h.top() == 19);

        top = 31;
        h.exchangeTop(top); //< h = {31 13 8 7 6 1}
        CHECK(top == 19);

        CHECK(h.top() == 31);
        h.pop();
        CHECK(h.top() == 13);
        h.pop();
        CHECK(h.top() == 8);
        h.pop();
        CHECK(h.top() == 7);
        h.pop();
        CHECK(h.top() == 6);
        h.pop();
        CHECK(h.top() == 1);
        h.pop();
        CHECK(h.empty());
    }

    SUBCASE("MinHeap") {
        MinHeap h;
        h.push(12);
        h.push(9);
        h.push(16);
        h.push(15);
        h.push(13);
        h.push(6);

        int top = 13;
        h.exchangeTop(top); //< h = {9 12 13 13 15 16}
        CHECK(top == 6);
        CHECK(h.top() == 9);

        top = -5;
        h.exchangeTop(top);
        CHECK(top == 9);
        CHECK(h.top() == -5); //< h = {-5 12 13 13 15 16}

        h.pop();
        CHECK(h.top() == 12);
        h.pop();
        CHECK(h.top() == 13);
        h.pop();
        CHECK(h.top() == 13);
        h.pop();
        CHECK(h.top() == 15);
        h.pop();
        CHECK(h.top() == 16);
        h.pop();
        CHECK(h.empty());
    }
}

TEST_CASE("bench test") {
    const unsigned seed = 9;
    std::default_random_engine eng(seed);
    std::uniform_int_distribution<int> distribution(INT_MIN, INT_MAX);

    const int tries = 10;
    const int n = 10'001;
    SUBCASE("push/pop") {
        for (int t = 0; t < tries; ++t) {
            MinHeap minh;
            MaxHeap maxh;
            std::vector<int> ref;
            ref.reserve(n);
            for (int i = 0; i < n; ++i) {
                int randomInt = distribution(eng);
                maxh.push(randomInt);
                minh.push(randomInt);
                ref.push_back(randomInt);
            }

            std::sort(ref.begin(), ref.end());
            bool same = true;
            for (int i = 0; i < n; ++i) {
                if (ref[i] != minh.top()) {
                    same = false;
                    break;
                }
                minh.pop();
            }
            REQUIRE_MESSAGE(same, "MinHeap ascending sort differes from std::sort");
            for (int i = 0; i < n; ++i) {
                if (ref[n - 1 - i] != maxh.top()) {
                    same = false;
                    break;
                }
                maxh.pop();
            }
            REQUIRE_MESSAGE(same, "MaxHeap descending sort differes from std::sort");
        }
    }

    SUBCASE("exchangeTop") {
        for (int t = 0; t < tries; ++t) {
            // Test both MinHeap and MaxHeap simultaneously
            MinHeap minHeap;
            MaxHeap maxHeap;
            std::set<int> minSet; //< Expected state of minHeap as a std::set
            std::set<int> maxSet; //< Expected state of maxHeap as a std::set
            for (int i = 0; i < n; ++i) {
                int randomInt = distribution(eng);
                minHeap.push(randomInt);
                maxHeap.push(randomInt);
                minSet.emplace(randomInt);
                maxSet.emplace(randomInt);
            }
            const int m = 100;
            for (int i = 0; i < m; ++i) {
                const int randomInt = distribution(eng);

                minSet.erase(minSet.begin());
                minSet.emplace(randomInt);
                int newTop = randomInt;
                minHeap.exchangeTop(newTop);

                maxSet.erase(--maxSet.end());
                maxSet.emplace(randomInt);
                newTop = randomInt;
                maxHeap.exchangeTop(newTop);
            }

            bool same = true;
            for (auto it = minSet.begin(); it != minSet.end(); ++it) {
                if (minHeap.top() != *it) {
                    same = false;
                    break;
                }
                minHeap.pop();
            }
            REQUIRE_MESSAGE(same, "MinHeap exchangeTop differes from std::set erase+emplace");
            for (auto it = maxSet.rbegin(); it != maxSet.rend(); ++it) {
                if (maxHeap.top() != *it) {
                    same = false;
                    break;
                }
                maxHeap.pop();
            }
            REQUIRE_MESSAGE(same, "MaxHeap exchangeTop differes from std::set erase+emplace");
        }
    }
}
