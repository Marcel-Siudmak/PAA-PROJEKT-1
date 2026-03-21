#pragma once
#include "ISort.hpp"
#include <algorithm>

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
    // Tail-call elimination: sortujemy mniejszą partycję rekursyjnie,
    // a większą w pętli while. Ogranicza głębokość stosu do O(log n).
    while (left < right) {
      int p = partition(table, left, right);

      // Rekursja na mniejszą partycję, pętla na większą
      // Hoare partition: podział na [left..p] i [p+1..right]
      if (p - left < right - p) {
        quickSortInternal(table, left, p);
        left = p + 1;
      } else {
        quickSortInternal(table, p + 1, right);
        right = p;
      }
    }
  }

public:
  // --- Hoare Partition z Median-of-Three ---
  // Hoare partition skanuje z obu stron jednocześnie i wykonuje ~3x mniej
  // swapów niż Lomuto. Zwraca indeks j taki, że:
  //   table[left..j] <= pivot  i  table[j+1..right] >= pivot
  static int partition(T *table, int left, int right) {
    int mid = left + (right - left) / 2;

    // Median-of-Three: sortujemy table[left], table[mid], table[right]
    if (table[mid] < table[left])
      std::swap(table[left], table[mid]);
    if (table[right] < table[left])
      std::swap(table[left], table[right]);
    if (table[right] < table[mid])
      std::swap(table[mid], table[right]);

    // Pivot = mediana (na pozycji mid)
    // table[left] <= pivot <= table[right] — naturalne sentinele
    T pivot = table[mid];

    int i = left - 1;
    int j = right + 1;

    for (;;) {
      do { ++i; } while (table[i] < pivot);
      do { --j; } while (table[j] > pivot);
      if (i >= j)
        return j;
      std::swap(table[i], table[j]);
    }
  }
};

template <typename T> inline void quickSort(T *table, int size) {
  QuickSort<T>().sort(table, size);
}