#include "DataHandler.hpp"
#include <algorithm>
#include <random>

std::vector<int> DataHandler::generateRandom(int size) {
  std::vector<int> data(size);
  // Uzywamy bardzo wydajnego i nowoczesnego silnika losujacego w C++
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<int> dist(-1000000,
                                          1000000); // zakres losowych wartosci

  for (int i = 0; i < size; ++i) {
    data[i] = dist(gen);
  }
  return data;
}

std::vector<int> DataHandler::generatePartiallySorted(int size,
                                                      double sortedPercentage) {
  std::vector<int> data = generateRandom(size);
  int sortedCount = static_cast<int>(size * sortedPercentage);

  // Uzywamy wbudowanego std::sort tylko do przygotowania poczatkowej strefy
  // testowych tablic
  std::sort(data.begin(), data.begin() + sortedCount);

  return data;
}

std::vector<int> DataHandler::generateReverseSorted(int size) {
  std::vector<int> data = generateRandom(size);

  // Sortujemy z uzyciem tzw. lambdy odwrotnej (wieksze elementy ida jako
  // pierwsze)
  std::sort(data.begin(), data.end(), [](int a, int b) { return a > b; });

  return data;
}

std::vector<int> DataHandler::copyData(const std::vector<int> &source) {
  return std::vector<int>(source);
}
