#pragma once

template <typename T> class ISort {
public:
  virtual ~ISort() = default;

  virtual void sort(T *table, int size) = 0;

  virtual const char *getAlgorithmName() const = 0;
};