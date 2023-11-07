#pragma once

#include <Heap.hpp>

/// Maintains the median of a collection
///
/// Use two heaps to maintain the median.
/// If we know the median of a collection and insert a new element, the
/// new median will be adjacent to the old one in the sorted sequence of
/// the container. So, if we partition the collection into <left, median, right>,
/// where 'left' and 'right' are arrays, the new median will be either max(left)
/// or min(right). 'left' will be a max-heap and 'right' will be a min-heap.
///
/// The same idea is used here, however 'median' is omitted for code simplification.
/// The heaps therefore satisfy the following two conditions:
/// - They will be of equal size. In case of an odd number of elements, 'smaller'
///   will contain the extra element.
/// - All the elements in 'smaller' will be smaller than the elements in 'bigger'.
struct MedianStore {
    void push(int x);

    float getMedian() const;

private:
    MaxHeap smaller;
    MinHeap bigger;
};
