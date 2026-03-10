#include "MergeSort.hpp"

template <typename T> void MergeSort<T>::sort(T *table, int size) {
  if (size < 2)
    return;

  T *buffer = new T[size];

  mergeSort(table, 0, size - 1, buffer);

  delete[] buffer;
}

template <typename T> const char *MergeSort<T>::getAlgorithmName() const {
  return "MergeSort";
}

template <typename T>
void MergeSort<T>::mergeSort(T *table, int left, int right, T *buffer) {
  if (left >= right)
    return;

  int middle = left + (right - left) / 2;

  mergeSort(table, left, middle, buffer);
  mergeSort(table, middle + 1, right, buffer);

  merge(table, left, middle, right, buffer);
}

template <typename T>
void MergeSort<T>::merge(T *table, int left, int mid, int right, T *buffer) {
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

template class MergeSort<int>;