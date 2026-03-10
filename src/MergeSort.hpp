#pragma once
#include "ISort.hpp"

template <typename T> class MergeSort : public ISort<T> {
public:
  void sort(T *table, int size) override;

  const char *getAlgorithmName() const override;

private:
  void mergeSort(T *table, int left, int right, T *buffer);

  void merge(T *table, int left, int mid, int right, T *buffer);
};