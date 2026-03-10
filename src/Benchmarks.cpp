#include "Benchmarks.hpp"
#include "DataHandler.hpp"
#include "IntroSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace fs = std::filesystem;

void Benchmarks::runFullBenchmark() {
  std::cout << "\n============================================\n";
  std::cout << " ROZPOCZECIE BENCHMARKOW EFEKTYWNOSCI \n";
  std::cout << "============================================\n";

  // Upewnijmy sie, ze folder results istnieje:
  fs::create_directory("../results");
  fs::create_directory(
      "results"); // dla pewnosci jak jestesmy bezposrednio w root

  std::vector<int> sizes = {10000, 50000, 100000, 500000, 1000000};
  int numArraysToTest = 100;

  std::vector<double> partialSortedPercentages = {0.25, 0.50, 0.75,
                                                  0.95, 0.99, 0.997};

  // Tworzenie CSV z naglowkami:
  std::vector<std::string> allConfigs;
  allConfigs.push_back("random");
  for (double p : partialSortedPercentages) {
    allConfigs.push_back("sorted_" + std::to_string(static_cast<int>(p * 100)) +
                         "percent");
  }
  allConfigs.push_back("sorted_99_7percent");
  allConfigs.push_back("reverse");

  // Czyszczenie wczesniejszych wynikow tworzac nowe, puste pliki z nagłówkami
  for (const auto &configName : allConfigs) {
    std::ofstream file("../results/" + configName + ".csv");
    if (!file.is_open())
      file.open("results/" + configName + ".csv");
    file << "RozmiarTablicy;SredniCzas_MergeSort[ms];SredniCzas_QuickSort[ms];"
            "SredniCzas_IntroSort[ms]\n";
    file.close();
  }

  // Pętle Główne:
  for (int size : sizes) {
    std::cout << "\n--> Przygotowywanie tablic dla rozmiaru: " << size
              << " ...\n";

    // Konfiguracja 1: W pełni losowe
    testConfig("random", numArraysToTest, size);

    // Konfiguracja 2: Częściowo posortowane
    for (double p : partialSortedPercentages) {
      std::string name =
          "sorted_" + std::to_string(static_cast<int>(p * 100)) + "percent";
      if (p == 0.997)
        name = "sorted_99_7percent";

      testConfig(name, numArraysToTest, size, p);
    }

    // Konfiguracja 3: Odwrotne ułożenie
    testConfig("reverse", numArraysToTest, size);
  }

  std::cout << "\n\n--> ZAKONCZONO! Wyniki wszystkich testow zostaly "
               "wygenerowane w folderze /results .\n";
}

void Benchmarks::testConfig(const std::string &configName, int numArraysToTest,
                            int arraySize, double partialSortedPercentage) {
  std::cout << " |-> Uruchamianie algorytmow dla: [" << configName << "] na "
            << numArraysToTest << " tablicach... ";
  // Wypiszemy na ekran by pokazać, że program żyje (bufor wypisany stąd
  // `std::flush`)
  std::cout << std::flush;

  double totalMergeTime = 0;
  double totalQuickTime = 0;
  double totalIntroTime = 0;

  bool mergeFailed = false;
  bool quickFailed = false;
  bool introFailed = false;

  MergeSort<int> mergeSorter;
  QuickSort<int> quickSorter;
  IntroSort<int> introSorter;

  for (int i = 0; i < numArraysToTest; i++) {
    // 1. Zamiast ładować wszystko na raz jak poprzednio, program generuje TYLKO
    // JEDNĄ tablicę naraz. Zwalnia i nadpisuje poprzednio zajmowaną pamięć
    // dzięki czemu nigdy nie uśmiercimy w ten sposób RAMu.
    std::vector<int> sampleArray;
    if (configName == "random") {
      sampleArray = DataHandler::generateRandom(arraySize);
    } else if (configName == "reverse") {
      sampleArray = DataHandler::generateReverseSorted(arraySize);
    } else {
      sampleArray = DataHandler::generatePartiallySorted(
          arraySize, partialSortedPercentage);
    }

    // --- 1. MergeSort Test ---
    std::vector<int> dataForMerge = DataHandler::copyData(sampleArray);
    auto start = std::chrono::high_resolution_clock::now();
    mergeSorter.sort(dataForMerge.data(), dataForMerge.size());
    auto end = std::chrono::high_resolution_clock::now();
    totalMergeTime +=
        std::chrono::duration<double, std::milli>(end - start).count();

    // Testowanie poprawnosci działania elementu w tle:
    if (!isSorted(dataForMerge)) {
      mergeFailed = true;
    }

    // --- 2. QuickSort Test ---
    std::vector<int> dataForQuick = DataHandler::copyData(sampleArray);
    start = std::chrono::high_resolution_clock::now();
    quickSorter.sort(dataForQuick.data(), dataForQuick.size());
    end = std::chrono::high_resolution_clock::now();
    totalQuickTime +=
        std::chrono::duration<double, std::milli>(end - start).count();

    if (!isSorted(dataForQuick)) {
      quickFailed = true;
    }

    // --- 3. IntroSort Test ---
    std::vector<int> dataForIntro = DataHandler::copyData(sampleArray);
    start = std::chrono::high_resolution_clock::now();
    introSorter.sort(dataForIntro.data(), dataForIntro.size());
    end = std::chrono::high_resolution_clock::now();
    totalIntroTime +=
        std::chrono::duration<double, std::milli>(end - start).count();

    if (!isSorted(dataForIntro)) {
      introFailed = true;
    }

    // Na koniec pojedynczej iteracji pętli `sampleArray`, `dataForMerge` i
    // `dataForQuick` usuwają się z pamięci i robią czyste miejsce dla
    // wygenerowania nowej tablicy na kolejną iterację i.
  }
  std::cout << "[ZROBIONO]\n";

  // Wyciąganie SREDNIEJ Arytmetycznej Czasu z 100 tablic
  double averageMergeTime = totalMergeTime / numArraysToTest;
  double averageQuickTime =
      (totalQuickTime < 0) ? -1 : (totalQuickTime / numArraysToTest);
  double averageIntroTime = totalIntroTime / numArraysToTest;

  // Raportowanie na ekran tego co wyszło w benchmarku obydwóm algorytmom:
  std::cout << "     MergeSort: " << (mergeFailed ? "FAILED" : "PASSED") << " ("
            << averageMergeTime << " ms) \n";
  std::cout << "     QuickSort: " << (quickFailed ? "FAILED" : "PASSED") << " ("
            << averageQuickTime << " ms) \n";
  std::cout << "     IntroSort: " << (introFailed ? "FAILED" : "PASSED") << " ("
            << averageIntroTime << " ms) \n";

  // Zapis do CSV
  std::string path = "../results/" + configName + ".csv";
  std::ofstream file(path, std::ios::app);
  if (!file.is_open())
    file.open("results/" + configName + ".csv", std::ios::app);

  if (file.is_open()) {
    file << std::fixed << std::setprecision(4) << arraySize << ";"
         << averageMergeTime << ";" << averageQuickTime << ";"
         << averageIntroTime << "\n";
    file.close();
  } else {
    std::cout << "\n [BLAD!] Nie mozna bylo zapisac linijki do CSV: " << path
              << "\n";
  }
}

// Implementacja bardzo szybkiej flagi sprawdzającej jedną pętlą do samego końca
// N tablicy
bool Benchmarks::isSorted(const std::vector<int> &data) {
  for (size_t i = 1; i < data.size(); i++) {
    if (data[i - 1] > data[i]) {
      return false; // Tablica nie jest posortowana rosnąco! Wpadka.
    }
  }
  return true;
}
