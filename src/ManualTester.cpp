#include "ManualTester.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

void ManualTester::run() {
  std::string input;
  std::cout << "\n--- TESTOWANIE RECZNE ---\n";
  std::cout << "Wpisz nazwe pliku tekstowego (np. test.txt) ALBO po prostu "
               "wprowadz liczby oddzielone spacja:\n> ";

  // Pozbywamy sie tzw. resztek "znakow nowej linii" (enterow) z bufora wejscia
  // uzytkownika (std::ws powoduje pochloniecie bialych znakow z poczatku w tym
  // znaku Enter z porzednich opcji menu)
  std::getline(std::cin >> std::ws, input);

  std::vector<int> data;

  // Bardzo prosty trik zeby sprawdzic czy ktos wpisal ".txt" (czy input konczy
  // sie na ".txt")
  if (input.length() >= 4 && input.substr(input.length() - 4) == ".txt") {
    data = readFromFile(input);
  } else {
    // Skoro nikt nie podal pliku to bierzemy wejscie i wyciagamy z niego reczne
    // liczby spacjami
    data = parseInputString(input);
  }

  if (data.empty()) {
    std::cout << "Blad: Brak danych do posortowania!\n";
    return; // wychodzimy z procedury
  }

  // Jak mamy dane, to przekazujemy je do funkcji zlecajacej sortowanie
  testSort(data);
}

// Funkcja odpowiedzialna za probne wczytanie z pliku:
std::vector<int> ManualTester::readFromFile(const std::string &filename) {
  std::vector<int> result;
  // Dolaczamy przedrostek sciezki w zaleznosci od tego z jakiego folderu
  // uruchamiany jest program. Najczesciej pliki takie laduja w folderze data w
  // root directory projektu.
  std::string path = "../data/" + filename;

  std::ifstream file(path);
  if (!file.is_open()) {
    // Awaryjna sciezka na wypadek gdyby program odpalono bezposrednio w
    // folderze projektu, a nie z folderu np. build/
    path = "data/" + filename;
    file.open(path);
    if (!file.is_open()) {
      std::cout << "Blad: Nie mozna otworzyc pliku: " << filename
                << " (probowano otworzyc: " << path << ")\n";
      return result;
    }
  }

  int num;
  while (file >> num) {
    result.push_back(num);
  }

  file.close();
  std::cout << "Wczytano " << result.size() << " element(ow) z pliku.\n";
  return result;
}

// Funkcja uzywajaca tak zwanego Streamu Stringu - bardzo popularny chwyt w C++
std::vector<int> ManualTester::parseInputString(const std::string &input) {
  std::vector<int> result;
  std::stringstream ss(
      input); // Tworzymy z tekstu strumien taki sam jak std::cin

  int num;
  while (ss >>
         num) { // czytamy strumien linijka po linijce, az trafimy na nie-liczby
    result.push_back(num);
  }

  return result;
}

void ManualTester::testSort(std::vector<int> &data) {
  std::cout << "\nTablica PRZED sortowaniem:\n";
  printArray(data);

  std::cout << "\nWybierz algorytm ktory chcesz przetestowac:\n"
            << "1. MergeSort\n"
            << "2. QuickSort\n"
            << "> ";

  int choice;
  std::cin >> choice;

  // Tworzymy tu pusty wskaznik na interfejs, ktory jest generyczny - tzw.
  // Polimorfizm!
  ISort<int> *sorter = nullptr;

  if (choice == 1) {
    sorter = new MergeSort<int>();
  } else if (choice == 2) {
    sorter = new QuickSort<int>();
  } else {
    std::cout << "Nieprawidlowy wybor algorytmu!\n";
    return;
  }

  std::cout << "\n[===================================]\n";
  std::cout << "  Start Sortowania: " << sorter->getAlgorithmName() << "\n";
  std::cout << "[===================================]\n";

  // Interfejsy uzywaja golego pointera w C++ bo narzucilismy to w ISort.hpp.
  // data.data() "dobiera" sie do "wnetrznosci" czyli tablicy jaka kryje sie pod
  // std::vector
  sorter->sort(data.data(), data.size());

  std::cout << "\nTablica PO sortowaniu:\n";
  printArray(data);

  // Sprawdzamy recznie czy tablica serio sie posortowala
  bool isSortedCorrectly = true;
  for (size_t i = 1; i < data.size(); i++) {
    if (data[i] < data[i - 1]) { // Znalezlismy element nastepny ktory jest
                                 // mniejszy! Błąd w sortowaniu.
      isSortedCorrectly = false;
      break;
    }
  }

  if (isSortedCorrectly) {
    std::cout << "\n--> WYNIK: Tablica zostala poprawnie POSORTOWANA.\n";
  } else {
    std::cout << "\n--> WYNIK: BLAD! Cos nie zadzialalo w Twoim algorytmie.\n";
  }

  // Skoro polimorficznie zaalokowalismy obiekt algorytmu `new` to go niszczymy
  // zbey zwolnic pamiec
  delete sorter;
}

void ManualTester::printArray(const std::vector<int> &data) {
  std::cout << "[ ";
  for (int el : data) {
    std::cout << el << " ";
  }
  std::cout << "]\n";
}
