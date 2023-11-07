#include "MedianStore.hpp"

#include <stdexcept>
#include <cassert>

void MedianStore::push(int x) {
    if (smaller.size() == 0) {
        smaller.push(x);
    } else if (smaller.size() == bigger.size()) {
        if (x <= bigger.top()) {
            smaller.push(x);
        } else {
            bigger.exchangeTop(x);
            smaller.push(x);
        }
    } else {
        // smaller.size() > bigger.size()
        if (x >= smaller.top()) {
            bigger.push(x);
        } else {
            smaller.exchangeTop(x);
            bigger.push(x);
        }
    }
    assert(smaller.size() >= bigger.size());
    assert(smaller.size() <= bigger.size() + 1);
}

float MedianStore::getMedian() const {
    if (smaller.empty()) {
        throw std::out_of_range("Empty container");
    } else if (smaller.size() > bigger.size()) {
        return static_cast<float>(smaller.top());
    } else {
        float median1 = smaller.top();
        float median2 = bigger.top();
        return (median1 + median2) / 2.f;
    }
}
