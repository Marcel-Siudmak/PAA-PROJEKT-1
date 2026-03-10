#pragma once
#include "ISort.hpp"

template <typename T> class HeapSort : public ISort<T> {
public:
  void sort(T *table, int size) override {
    if (size < 2)
      return;

    heapSortInternal(table, 0, size - 1);
  }

  const char *getAlgorithmName() const override { return "HeapSort"; }

  // Podstawowa klasyczna część sortująca na kopcach podawana pod dowolny
  // zakres:
  static void heapSortInternal(T *table, int left, int right) {
    int n = right - left + 1;

    // 1. Budowanie kopca
    for (int i = n / 2 - 1; i >= 0; i--) {
      heapify(table, n, i, left); // Przekazujemy offset tablicowy
    }

    // 2. Wyciąganie "szczytu" po jednym elemencie
    for (int i = n - 1; i > 0; i--) {
      T tmp = table[left];
      table[left] = table[left + i];
      table[left + i] = tmp;
      heapify(table, i, 0, left);
    }
  }

private:
  static void heapify(T *table, int n, int i, int offset) {
    int largest = i;
    int leftNode = 2 * i + 1;
    int rightNode = 2 * i + 2;

    if (leftNode < n && table[offset + leftNode] > table[offset + largest]) {
      largest = leftNode;
    }
    if (rightNode < n && table[offset + rightNode] > table[offset + largest]) {
      largest = rightNode;
    }

    if (largest != i) {
      T tmp = table[offset + i];
      table[offset + i] = table[offset + largest];
      table[offset + largest] = tmp;
      heapify(table, n, largest, offset);
    }
  }
};

template <typename T> inline void heapSort(T *table, int size) {
  HeapSort<T>().sort(table, size);
}
