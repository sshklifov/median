#pragma once

#include <Heap.hpp>

struct MedianStore {
    void push(int x);
    float getMedian() const;

private:
    MaxHeap smaller;
    MinHeap bigger;
};
