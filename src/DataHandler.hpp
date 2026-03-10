#pragma once
#include <vector>

class DataHandler {
public:
  // Zwraca wektor wypelniony losowymi liczbami
  static std::vector<int> generateRandom(int size);

  // Zwraca wektor, w ktorym pewien rzadek poczatkowych elementow (np. 0.25 dla
  // 25%) jest posortowany rosnaco, a reszta jest losowa.
  static std::vector<int> generatePartiallySorted(int size,
                                                  double sortedPercentage);

  // Zwraca wektor posortowany calkowicie malejaco (odwrotnie)
  static std::vector<int> generateReverseSorted(int size);

  // Na wszelki wypadek metoda kopiujaca cala tablice zeby miec "czyste" kopie
  // do kolejnych sortowan
  static std::vector<int> copyData(const std::vector<int> &source);
};
