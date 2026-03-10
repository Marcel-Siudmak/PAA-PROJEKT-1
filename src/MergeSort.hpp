#pragma once
#include "ISort.hpp"

template <typename T> class MergeSort : public ISort<T> {
public:
  void sort(T *table, int size) override {
    if (size < 2)
      return;

    T *buffer = new T[size];
    mergeSortInternal(table, 0, size - 1, buffer);
    delete[] buffer;
  }

  const char *getAlgorithmName() const override { return "MergeSort"; }

private:
  static void mergeSortInternal(T *table, int left, int right, T *buffer) {
    if (left >= right)
      return;

    int middle = left + (right - left) / 2;

    mergeSortInternal(table, left, middle, buffer);
    mergeSortInternal(table, middle + 1, right, buffer);

    mergeInternal(table, left, middle, right, buffer);
  }

  static void mergeInternal(T *table, int left, int mid, int right, T *buffer) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
      if (table[i] <= table[j])
        buffer[k++] = table[i++];
      else
        buffer[k++] = table[j++];
    }

    while (i <= mid)
      buffer[k++] = table[i++];

    while (j <= right)
      buffer[k++] = table[j++];

    for (int idx = left; idx <= right; idx++)
      table[idx] = buffer[idx];
  }
};

template <typename T> inline void mergeSort(T *table, int size) {
  MergeSort<T>().sort(table, size);
}