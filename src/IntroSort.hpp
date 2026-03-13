#pragma once
#include "HeapSort.hpp"
#include "ISort.hpp"
#include "InsertionSort.hpp"
#include "QuickSort.hpp"

template <typename T> class IntroSort : public ISort<T> {
public:
  void sort(T *table, int size) override {
    if (size < 2)
      return;

    // __builtin_clz daje liczbę wiodących zer; floor(log2(n)) = 31 - clz(n)
    // Szybsza operacja bitowa zamiast std::log2 (floating-point)
    int log2n = (sizeof(unsigned) * 8 - 1) - __builtin_clz(static_cast<unsigned>(size));
    int maxDepth = 2 * log2n;
    introSortInternal(table, 0, size - 1, maxDepth);
  }

  const char *getAlgorithmName() const override { return "IntroSort"; }

private:
  static void introSortInternal(T *table, int left, int right, int maxDepth) {
    int size = right - left + 1;

    if (size < 16) {
      InsertionSort<T>::insertionSortInternal(table, left, right);
      return;
    }

    if (maxDepth == 0) {
      HeapSort<T>::heapSortInternal(table, left, right);
      return;
    }

    int pivotIndex = QuickSort<T>::partition(table, left, right);

    // Hoare partition: podział na [left..pivotIndex] i [pivotIndex+1..right]
    introSortInternal(table, left, pivotIndex, maxDepth - 1);
    introSortInternal(table, pivotIndex + 1, right, maxDepth - 1);
  }
};

template <typename T> inline void introSort(T *table, int size) {
  IntroSort<T>().sort(table, size);
}
