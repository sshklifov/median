#pragma once

#include <queue>

struct MedianStore {
    /* MedianStore(); */

    void add(int x);
    float getMedian() const;

private:
    std::priority_queue<int> smaller;
    std::priority_queue<int, std::vector<int>, std::greater<int>> bigger;
};
