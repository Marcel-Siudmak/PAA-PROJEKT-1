#pragma once

class Menu {
public:
  // Konstruktor (wywoływany przy tworzeniu obiektu Menu)
  Menu();

  // Główna funkcja, która "odpala" całe menu i trzyma je w pętli
  void run();

private:
  // Prywatna flaga, która mówi nam czy mamy dalej kręcić pętlą główną
  bool isRunning;

  // Prywatne funkcje pomocnicze, niewidoczne na zewnątrz klasy (w main.cpp).
  // Takie metody pomagają podzielić duży kod menu na małe i czytelne części.
  void showMainMenu();
  void handleManualTest();
  void handleBenchmark();
};
