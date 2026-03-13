#pragma once
#include "ISort.hpp"
#include <algorithm>

template <typename T> class HeapSort : public ISort<T> {
public:
  void sort(T *table, int size) override {
    if (size < 2)
      return;

    heapSortInternal(table, 0, size - 1);
  }

  const char *getAlgorithmName() const override { return "HeapSort"; }

  static void heapSortInternal(T *table, int left, int right) {
    int n = right - left + 1;

    // Build max-heap
    for (int i = n / 2 - 1; i >= 0; i--) {
      siftDown(table, n, i, left);
    }

    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
      std::swap(table[left], table[left + i]);
      siftDown(table, i, 0, left);
    }
  }

private:
  // Iteracyjny sift-down — eliminuje overhead wywołań rekursyjnych
  // Kompilator lepiej optymalizuje prostą pętlę while
  static void siftDown(T *table, int n, int i, int offset) {
    while (true) {
      int largest = i;
      int leftNode = 2 * i + 1;
      int rightNode = 2 * i + 2;

      if (leftNode < n && table[offset + leftNode] > table[offset + largest])
        largest = leftNode;
      if (rightNode < n && table[offset + rightNode] > table[offset + largest])
        largest = rightNode;

      if (largest == i)
        return;

      std::swap(table[offset + i], table[offset + largest]);
      i = largest;
    }
  }
};

template <typename T> inline void heapSort(T *table, int size) {
  HeapSort<T>().sort(table, size);
}
