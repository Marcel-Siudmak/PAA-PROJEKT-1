#pragma once
#include "ISort.hpp"

template <typename T> class QuickSort : public ISort<T> {
public:
  void sort(T *table, int size) override {
    if (size < 2)
      return;

    quickSortInternal(table, 0, size - 1);
  }

  const char *getAlgorithmName() const override { return "QuickSort"; }

private:
  static void quickSortInternal(T *table, int left, int right) {
    if (left >= right)
      return;

    int pivotIndex = partition(table, left, right);
    quickSortInternal(table, left, pivotIndex - 1);
    quickSortInternal(table, pivotIndex + 1, right);
  }

  static int partition(T *table, int left, int right) {
    T pivot = table[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
      if (table[j] <= pivot) {
        i++;
        T temp = table[i];
        table[i] = table[j];
        table[j] = temp;
      }
    }

    T temp = table[i + 1];
    table[i + 1] = table[right];
    table[right] = temp;

    return i + 1;
  }
};

template <typename T> inline void quickSort(T *table, int size) {
  QuickSort<T>().sort(table, size);
}