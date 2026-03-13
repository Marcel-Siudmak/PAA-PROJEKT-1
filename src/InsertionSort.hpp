#pragma once
#include "ISort.hpp"
#include <utility>

template <typename T> class InsertionSort : public ISort<T> {
public:
  void sort(T *table, int size) override {
    if (size < 2)
      return;

    for (int i = 1; i < size; i++) {
      T key = std::move(table[i]);
      int j = i - 1;
      while (j >= 0 && table[j] > key) {
        table[j + 1] = std::move(table[j]);
        j--;
      }
      table[j + 1] = std::move(key);
    }
  }

  const char *getAlgorithmName() const override { return "InsertionSort"; }

  static void insertionSortInternal(T *table, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
      T key = std::move(table[i]);
      int j = i - 1;
      while (j >= left && table[j] > key) {
        table[j + 1] = std::move(table[j]);
        j--;
      }
      table[j + 1] = std::move(key);
    }
  }
};

template <typename T> inline void insertionSort(T *table, int size) {
  InsertionSort<T>().sort(table, size);
}
