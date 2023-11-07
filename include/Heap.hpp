#pragma once

#include <vector>
#include <functional>

template <typename Compare>
struct Heap {
    void push(int x) {
        heap.push_back(x);
        siftUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        heap.front() = heap.back();
        heap.pop_back();
        siftDown(0);
    }

    int top() const {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap[0];
    }

    bool empty() const {
        return heap.empty();
    }

    int size() const {
        return heap.size();
    }

    void exchangeTop(int& newTop) {
        std::swap(heap.at(0), newTop);
        return siftDown(0);
    }

private:
    void siftDown(int i) {
        int left = i * 2 + 1;
        int right = i * 2 + 2;
        int best = i;

        Compare less;
        if (left < heap.size() && less(heap[left], heap[i])) {
            best = left;
        }
        if (right < heap.size() && less(heap[right], heap[best])) {
            best = right;
        }

        if (best != i) {
            std::swap(heap[i], heap[best]);
            return siftDown(best);
        }
    }

    void siftUp(int i) {
        Compare less;
        if (i > 0) {
            int parent = (i - 1) / 2;
            if (less(heap[i], heap[parent])) {
                std::swap(heap[i], heap[parent]);
                return siftUp(parent);
            }
        }
    }

private:
    std::vector<int> heap;
};

using MinHeap = Heap<std::less<int>>;
using MaxHeap = Heap<std::greater<int>>;
