#pragma once
#include <string>
#include <vector>

class Benchmarks {
public:
  // Uruchamia wszystkie scenariusze i zapisuje wyniki do folderu
  void runFullBenchmark();

private:
  // Funkcja uruchamiająca pomiary i generująca poszczególne tablice po kolei
  // (oszczędza RAM)
  void testConfig(const std::string &configName, int numArraysToTest,
                  int arraySize, double partialSortedPercentage = -1.0);

  // Formatuje liczbe float do stringa pod format CSV
  std::string formatTime(double timeMs);

  // Funkcja pomagajaca zweryfikowac, czy sortowanie po wywolaniu faktycznie
  // mialo miejsce
  bool isSorted(const std::vector<int> &data);
};
