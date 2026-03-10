#pragma once
#include <string>
#include <vector>

class ManualTester {
public:
  // Glowna funkcja odpalajaca tester
  void run();

private:
  // Metody pomocnicze (ukryte przed uzytkownikiem zewnetrznym klasy)
  std::vector<int> readFromFile(const std::string &filename);
  std::vector<int> parseInputString(const std::string &input);
  void testSort(std::vector<int> &data);
  void printArray(const std::vector<int> &data);
};
