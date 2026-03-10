# PROJEKTOWANIE I ANALIZA ALGORYTMOW - PROJEKT 1

## Spis treści

- [Wymagania](#wymagania)
- [Kompilacja i uruchomienie](#kompilacja-i-uruchomienie)
- [Struktura projektu](#struktura-projektu)
- [Testy](#testy)

## 1. Wymagania

* **Kompilator:** GCC 15+ / Clang 17+ (wymagane wsparcie dla C++20)
* **System budowania:** CMake 3.10+
* **System operacyjny:** macOS / Windows / Linux

## 2. Kompilacja i uruchomienie

Aby zbudować projekt, wykonaj poniższe kroki w terminalu:

1. Stwórz folder budowania:
   ```bash
   mkdir build && cd build
   ```

2. Skonfiguruj projekt za pomocą CMake:
   ```bash
   cmake ..
   ```

3. Skompiluj:
   ```bash
   cmake --build .
   ```

4. Uruchom program:
   ```bash
   ./mini_projekt_1
   ```

## 3. Struktura projektu

```text
├── src/
│   ├── main.cpp
│   ├── ISort.hpp
│   ├── MergeSort.hpp
│   ├── MergeSort.cpp
│   ├── QuickSort.hpp
│   ├── QuickSort.cpp
│   ├── IntroSort.hpp
│   ├── IntroSort.cpp
│   ├── Menu.hpp
│   ├── Menu.cpp
│   ├── Benchmark.hpp
│   ├── Benchmark.cpp
│   ├── DataHandler.hpp
│   └── DataHandler.cpp
├── data/
│   ├── random_data_5000.txt
│   ├── random_data_10000.txt
│   └── ... 
├── build/
│   ├── binary
│   └── ...
├── CMakeLists.txt
└── README.md
```


## 4. Szczegółowy Opis Plików i Modułów

### A. Abstrakcja i Interfejsy

#### `ISort.hpp` (Abstrakcja)
Abstrakcyjna klasa bazowa (interfejs) wykorzystująca szablony (**templates**). Definiuje kontrakt dla wszystkich algorytmów sortowania poprzez czysto wirtualną metodę `sort()`. Pozwala to na polimorficzne zarządzanie różnymi algorytmami w module benchmarkowym.

### B. Algorytmy Sortowania (Moduły implementacyjne)

#### `MergeSort`
`MergeSort.hpp` / `MergeSort.cpp` – Implementacja algorytmu sortowania przez scalanie. Moduł realizuje strategię „dziel i zwyciężaj”, zapewniając stabilność sortowania i złożoność $O(n \log n)$.

#### `QuickSort`
`QuickSort.hpp` / `QuickSort.cpp` – Implementacja sortowania szybkiego. Moduł zawiera logikę partycjonowania tablicy względem elementu osiowego (pivot). Jest to kluczowy algorytm dla uzyskania oceny 4.0+.

#### `IntroSort`
`IntroSort.hpp` / `IntroSort.cpp` – Implementacja sortowania introspektywnego. Algorytm hybrydowy, który zaczyna od QuickSort, a w przypadku zbyt dużej głębokości rekurencji przełącza się na HeapSort, co gwarantuje złożoność $O(n \log n)$ nawet w przypadku pesymistycznym.

### C. Logika Aplikacji i Interfejs Użytkownika

#### `Menu`
`Menu.hpp` / `Menu.cpp` – Warstwa prezentacji. Moduł odpowiada za interakcję z użytkownikiem, wybór typu danych, rozmiaru tablicy oraz algorytmu. Pozwala na ręczne uruchomienie testów i weryfikację poprawności (walidację) sortowania na małych zbiorach.

#### `main.cpp`
Punkt startowy programu. Odpowiada za stworzenie instancji klasy `Menu` i uruchomienie jej głównej pętli. Nie zawiera logiki biznesowej, a jedynie inicjalizuje aplikację.

### D. Narzędzia Badawcze i Zarządzanie Danymi

#### `DataHandler`
`DataHandler.hpp` / `DataHandler.cpp` – Moduł narzędziowy do przygotowania zestawów danych. Zawiera funkcje generujące tablice o zadanych parametrach:
* Całkowicie losowe,
* Częściowo posortowane (25%, 50%, 75%, 95%, 99%, 99.7%),
* Posortowane odwrotnie.
Obsługuje również zapis i odczyt tych danych z plików `.txt`.

#### `Benchmark`
`Benchmark.hpp` / `Benchmark.cpp` – Serce części badawczej. Wykorzystuje bibliotekę `<chrono>` do precyzyjnego pomiaru czasu (mikrosekundy/nanosekundy). Automatyzuje proces testowy: przeprowadza 100 powtórzeń dla każdego rozmiaru tablicy (10k, 50k, 100k, 500k, 1M) i oblicza średni czas wykonania.

### E. Pozostałe Elementy Projektu

#### `data/` (Katalog danych)
Folder przechowujący fizyczne pliki `.txt` z wygenerowanymi zestawami liczb. Zapewnia to, że każdy algorytm jest testowany na identycznych danych wejściowych, co jest niezbędne do rzetelnej analizy porównawczej.

#### `build/` (Katalog kompilacji)
Katalog roboczy generowany przez CMake. Przechowuje plik wykonywalny oraz pliki obiektowe. Jest on ignorowany przez system kontroli wersji.

#### `CMakeLists.txt` (Konfiguracja)
Plik sterujący procesem budowania projektu. Określa standard **C++20**, flagi optymalizacyjne kompilatora (np. `-O3`) oraz definiuje sposób łączenia plików źródłowych w plik wykonywalny.

#### `README.md` (Dokumentacja)
Główny dokument projektu zawierający instrukcje kompilacji, opis struktury oraz końcowe wnioski z przeprowadzonej analizy efektywności algorytmów.



