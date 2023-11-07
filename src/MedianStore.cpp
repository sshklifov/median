#include "MedianStore.hpp"

#include <stdexcept>
#include <cassert>

void MedianStore::push(int x) {
    if (smaller.size() == 0) {
        // Implies bigger.size() == 0 and that the container is empty.
        smaller.push(x);
    } else if (smaller.size() == bigger.size()) {
        // 'smaller' should grow with 1 element.
        // This might be 'x' or the min element in 'bigger'.
        if (x <= bigger.top()) {
            smaller.push(x);
        } else {
            bigger.exchangeTop(x);
            smaller.push(x);
        }
    } else {
        // Implies smaller.size() > bigger.size(). 'bigger' should grow with 1 element.
        // This might be 'x' or the max element in 'smaller'.
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
    } else if (smaller.size() != bigger.size()) {
        // Implies smaller.size() == bigger.size() + 1.
        // The median is the max of 'smallest' heap.
        return static_cast<float>(smaller.top());
    } else {
        float median1 = smaller.top();
        float median2 = bigger.top();
        return (median1 + median2) / 2.f;
    }
}
