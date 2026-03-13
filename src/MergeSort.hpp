#pragma once
#include "ISort.hpp"
#include <algorithm>

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

    // Pominięcie merge gdy dane już posortowane naturalnie — ogromne
    // przyspieszenie na danych częściowo posortowanych
    if (table[middle] <= table[middle + 1])
      return;

    mergeInternal(table, left, middle, right, buffer);
  }

  static void mergeInternal(T *table, int left, int mid, int right, T *buffer) {
    // Kopiujemy do bufora za pomocą std::copy (kompilator wektoryzuje)
    std::copy(table + left, table + right + 1, buffer + left);

    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
      if (buffer[i] <= buffer[j])
        table[k++] = std::move(buffer[i++]);
      else
        table[k++] = std::move(buffer[j++]);
    }

    // Kopiujemy resztę lewej połówki (prawa już jest na miejscu w table)
    while (i <= mid)
      table[k++] = std::move(buffer[i++]);

    // Reszta prawej połówki jest już na właściwych pozycjach w table
    // — nie trzeba jej kopiować (j..right to oryginalne pozycje)
  }
};

template <typename T> inline void mergeSort(T *table, int size) {
  MergeSort<T>().sort(table, size);
}