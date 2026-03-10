#pragma once
#include "ISort.hpp"

template <typename T> class InsertionSort : public ISort<T> {
public:
  void sort(T *table, int size) override {
    if (size < 2)
      return;

    // Klasyczny algorytm układania po kolei
    for (int i = 1; i < size; i++) {
      T key = table[i];
      int j = i - 1;
      while (j >= 0 && table[j] > key) {
        table[j + 1] = table[j];
        j--;
      }
      table[j + 1] = key;
    }
  }

  const char *getAlgorithmName() const override { return "InsertionSort"; }

  // Skopiowany dedykowany statyczny Insertion Sort do zadań na wskazanym
  // wycinku między [left, right] (używany przez IntroSort w momentach
  // rekursywnego podziału skrawków tablic!)
  static void insertionSortInternal(T *table, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
      T key = table[i];
      int j = i - 1;
      while (j >= left && table[j] > key) {
        table[j + 1] = table[j];
        j--;
      }
      table[j + 1] = key;
    }
  }
};

template <typename T> inline void insertionSort(T *table, int size) {
  InsertionSort<T>().sort(table, size);
}
