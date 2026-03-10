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
    // --- Algorytm Median-Of-Three (Mediana z trzech) ---
    // Wybieramy trzy elementy (pierwszy, środek i ostatni) i ustawiamy je tak,
    // by na miejsce ostatniego wędrowała Mediana z najgorszych prób, a na
    // miejsce pierwsze wartość najmniejsza. Zabezpiecza nas to przed tablicami
    // z góry ułożonymi!
    int mid = left + (right - left) / 2;

    if (table[mid] < table[left]) {
      T tmp = table[left];
      table[left] = table[mid];
      table[mid] = tmp;
    }
    if (table[right] < table[left]) {
      T tmp = table[left];
      table[left] = table[right];
      table[right] = tmp;
    }
    // Finalnie z pozostałych "dwóch" wyrzucamy ten mniejszy (medianę) do
    // table[right] jako Pivot
    if (table[mid] < table[right]) {
      T tmp = table[mid];
      table[mid] = table[right];
      table[right] = tmp;
    }
    // Pivot jest teraz na ostatniej pozycji (table[right]), gotowy na stary
    // podział Lomuto
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