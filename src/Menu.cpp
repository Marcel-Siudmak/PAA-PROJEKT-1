#include "Menu.hpp"
#include "Benchmarks.hpp"
#include "ManualTester.hpp"
#include <iostream>

// --- Konstruktor ---
// Tutaj ustawiamy początkowy stan naszego menu.
Menu::Menu() { isRunning = true; }

// --- Główna pętla menu ---
// To ona wyświetla opcje w kółko dopóki nie zmienimy statusu na fałsz
void Menu::run() {
  int choice;

  while (isRunning) {
    showMainMenu(); // Wyśwetlenie tekstu menu

    std::cout << "\nTwój wybór: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
      handleManualTest();
      break;
    case 2:
      handleBenchmark();
      break;
    case 0:
      std::cout << "Zamykanie programu...\n";

      isRunning = false;
      break;
    default:
      std::cout << "Nieznana opcja. Sprobuj ponownie.\n";
      break;
    }
  }
}

void Menu::showMainMenu() {
  std::cout << "\n==============================\n";
  std::cout << "       PROJEKT: SORTOWANIE      \n";
  std::cout << "==============================\n";
  std::cout << "1. Ręczne testowanie sortowania\n";
  std::cout << "2. Uruchom duży Benchmark\n";
  std::cout << "0. Wyjście\n";
}

void Menu::handleManualTest() {
  ManualTester tester;
  tester.run();
}

void Menu::handleBenchmark() {
  Benchmarks bench;
  bench.runFullBenchmark();
}
