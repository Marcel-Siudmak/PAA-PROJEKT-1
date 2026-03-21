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

    // Jeśli lewy i prawy fragment są już w kolejności (naturalnie posortowane),
    // nie trzeba ich scalać — możemy zaoszczędzić czas.
    if (table[middle] <= table[middle + 1])
      return;

    mergeInternal(table, left, middle, right, buffer);
  }

  static void mergeInternal(T *table, int left, int mid, int right, T *buffer) {
    // Skopiuj część tablicy, którą będziemy scalać, do bufora.
    // Ta operacja jest zoptymalizowana przez kompilator.
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

    // Skopiuj ewentualne pozostałe elementy z lewej połowy.
    // Prawa połowa już znajduje się we właściwych miejscach w table.
    while (i <= mid)
      table[k++] = std::move(buffer[i++]);

    // Pozostałe elementy prawej połowy są już we właściwym miejscu,
    // więc nie musimy ich przenosić ponownie.
  }
};

template <typename T> inline void mergeSort(T *table, int size) {
  MergeSort<T>().sort(table, size);
}