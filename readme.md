# Projektowanie i Analiza Algorytmów (PAA) — Projekt 1
## Porównanie Efektywności Algorytmów Sortowania

Projekt zawiera implementacje i porównanie wydajności trzech algorytmów sortowania: **MergeSort**, **QuickSort** i **IntroSort** na różnych rozkładach danych (losowe, posortowane, częściowo posortowane, itp.).

## Spis treści

- [Wymagania](#wymagania)
- [Kompilacja i uruchomienie](#kompilacja-i-uruchomienie)
- [Struktura projektu](#struktura-projektu)
- [Moduły i komponenty](#moduły-i-komponenty)
- [Procedura benchmarkowania](#procedura-benchmarkowania)
- [Analiza wyników](#analiza-wyników)

---

## 1. Wymagania

- **Kompilator:** GCC 9+ / Clang 10+ (C++20 lub wyżej)
- **System budowania:** CMake 3.15+
- **System operacyjny:** macOS / Linux / Windows
- **Python:** 3.8+ (do generowania wykresów)

---

## 2. Kompilacja i uruchomienie

### Budowanie projektu

```bash
# Przejdź do katalogu projektu
cd /Users/marcelsiudmak/Code/PAA-PROJEKT-1

# Stwórz folder budowania
mkdir -p build && cd build

# Konfiguracja CMake
cmake ..

# Kompilacja
cmake --build .
```

### Uruchomienie głównego programu

```bash
./paa_projekt_1
```

Program uruchomi interaktywne menu z opcjami:
- **Testowanie ręczne** — wprowadzenie własnych danych
- **Benchmarki** — automatyczne pomiary wydajności na różnych rozmiarach i rozkładach

### Uruchomienie benchmarków i generowanie wykresów

```bash
# W katalogu /scripts
cd ../scripts

# Zainstaluj zależności Pythona (jednorazowo)
pip install -r requirements.txt

# Wygeneruj wykresy z wyników w /results
python run_all_plots.py
```

Wykresy zostaną zapisane w: `../plots/`

---

## 3. Struktura projektu

```
PAA-PROJEKT-1/
├── src/                           # Kod źródłowy C++
│   ├── main.cpp                   # Punkt wejścia aplikacji
│   ├── ISort.hpp                  # Interfejs abstrakcyjny algorytmów
│   ├── MergeSort.hpp              # Implementacja MergeSort
│   ├── QuickSort.hpp              # Implementacja QuickSort
│   ├── IntroSort.hpp              # Implementacja IntroSort (hybrydowy)
│   ├── HeapSort.hpp               # Pomocniczy HeapSort
│   ├── InsertionSort.hpp          # Pomocniczy InsertionSort
│   ├── Benchmarks.hpp/.cpp        # Moduł benchmarkowania
│   ├── DataHandler.hpp/.cpp       # Generator danych testowych
│   ├── Menu.hpp/.cpp              # Interfejs użytkownika
│   └── ManualTester.hpp/.cpp      # Tester manualny
│
├── scripts/                       # Skrypty Python do analizy
│   ├── run_all_plots.py           # Generator wszystkich wykresów
│   ├── plot.py                    # Wykresy podstawowe (random vs reverse)
│   ├── plot_random_vs_reverse.py
│   ├── plot_percent_sorted.py     # Wykresy dla różnych % sortowania
│   ├── plot_partially_sorted.py
│   ├── generate_tables.py         # Generator tabel CSV
│   └── requirements.txt           # Zależności Pythona
│
├── build/                         # Folder budowania (CMake)
│   ├── paa_projekt_1              # Plik wykonywalny
│   ├── CMakeFiles/
│   └── ...
│
├── data/                          # Dane testowe
│   └── test.txt
│
├── results/                       # Wyniki benchmarków (CSV)
│   ├── random.csv
│   ├── reverse.csv
│   ├── sorted_25percent.csv
│   ├── sorted_50percent.csv
│   ├── sorted_75percent.csv
│   ├── sorted_95percent.csv
│   ├── sorted_99percent.csv
│   └── sorted_99_7percent.csv
│
├── tables/                        # Tabele czasów (czasowo)
│   ├── IntroSort_times.csv
│   ├── MergeSort_times.csv
│   └── QuickSort_times.csv
│
├── plots/                         # Wygenerowane wykresy
│   ├── basic_distributions/       # Wykresy random vs reverse
│   ├── percent_sorted/            # Wykresy dla % sortowania
│   ├── partially_sorted/          # Wykresy dla różnych % presortowania
│   └── random_vs_reverse/         # Porównanie dwóch rozkładów
│
├── CMakeLists.txt                 # Konfiguracja budowania
├── readme.md                      # Ten plik
└── .gitignore
```


## 4. Moduły i komponenty

### 4.1 Interfejs abstrakcyjny

#### `ISort.hpp`
Abstrakcyjna klasa bazowa definiująca kontrakt dla wszystkich algorytmów sortowania. Każda implementacja musi realizować:
- `sort(T* table, int size)` — główna metoda sortowania
- `getAlgorithmName()` — zwraca nazwę algorytmu

Umożliwia polimorficzne zarządzanie różnymi algorytmami w module benchmarkowym.

---

### 4.2 Algorytmy sortowania

#### MergeSort.hpp
**Sortowanie przez scalanie** — algorytm oparty na paradygmacie „dziel i zwyciężaj".

#### `QuickSort`
`QuickSort.hpp` – Implementacja sortowania szybkiego bazująca na `ISort<T>`. Algorytm wykorzystuje publiczny silnik partycjonowania tablicy względem elementu osiowego (pivot) wzbogacony o optymalizację Median-of-Three (Mediana z trzech).

#### `InsertionSort` i `HeapSort`
`InsertionSort.hpp` / `HeapSort.hpp` – Dwie dodatkowe metody sortowania pod spodem `ISort<T>`. InsertionSort używany jest do niesamowicie szybkiego, liniowego układania małych list (np. używając Cache'a klastra procesora). HeapSort wykorzystuje naprawę Kopca Binarnego i chroni przed przepięciami rekursji. Przechowują publiczne funkcje statyczne do sortowania we wskazanych zasięgach podprzestrzeni (od lewej do prawej).

#### `IntroSort`
`IntroSort.hpp` – Implementacja wielomodułowego i hybrydowego sortowania introspektywnego. Rdzeń klasy to system warunkujący zaciągający powyższe implementacje klocków (`InsertionSort`, `HeapSort`, i `QuickSort::partition`). Gwarantuje piorunującą szybkość dla dobrych przypadków i limituje glebokość w $O(n \log n)$ dla przypadków oszukanych i pesymistycznych.

### C. Logika Aplikacji i Interfejs Użytkownika

#### `Menu`
`Menu.hpp` / `Menu.cpp` – Warstwa prezentacji, główne powitanie, z którego uruchamia się odrębne testy.

#### `ManualTester`
`ManualTester.hpp` / `ManualTester.cpp` - Submoduł konsoli służący do swobodnego, ręcznego rzucania wybranymi algorytmami sortującymi na krótkotrwałych testach wprowadzanych z klawiatury użytkownika. 

#### `main.cpp`
Punkt startowy programu. Odpowiada wyłącznie za stworzenie instancji klasy `Menu` i pobudzenie do życia w pętli UI.

### D. Narzędzia Badawcze i Zarządzanie Danymi

#### `DataHandler`
`DataHandler.hpp` / `DataHandler.cpp` – Moduł narzędziowy będący fabryką danych w formacie generowania `std::vector<int>`. W zaleźności od wezwania "wypluwa" tablicę:
* Całkowicie losową,
* Częściowo posortowaną z idealnie dopasowanym procentem przedziału początkowego,
* Posortowaną od największej do najmniejszej (Reverse).

#### `Benchmarks`
`Benchmarks.hpp` / `Benchmarks.cpp` – Niezależne serce części badawczej i pomiarowej o rygorystycznych ograniczeniach dla środowiska roboczego. Dynamicznie, dla mniejszych zakresów, zwalnia i przydziela w pamięci macierze (chroniąc system RAM operacyjny przez uduszeniem) pod czułym okiem `std::chrono`. Wykonuje serię posortowań każdej z klas na setkach tablic pod presją badawczą i generuje wyniki statystyczne do odczytu w `.csv`. Dodatkowo, posiada wbudowany licznik walidacyjny `isSorted`, który testuje każdy produkt tablicowy, zapalając "FAILED" na ekranie benchmarku w trybie runtime.

### E. Pozostałe Elementy Projektu

#### `results/` (Katalog danych)
Folder docelowy, zbierający zautomatyzowane logi i raporty odzwierciedlające obciążenie czasowe wygenerowane z uruchomienia Menu -> 2. Benchmark. Gotowe `.csv` do użycia w arkuszu. Zastępuje stary folder ręcznych txt z tablicami.

#### `build/` (Katalog kompilacji)
Katalog roboczy generowany przez wbudowany ustrój. Przechowuje binarne pliki egzekutora `paa_projekt_1` powstałe po wpisaniu komendy `cmake --build .`. Ignorowany przez system git dla lekkości repozytorium.

#### `CMakeLists.txt` (Konfiguracja)
Plik sterujący procesem budowania projektu. Określa standard **C++20**, flagi optymalizacyjne kompilatora (np. `-O3`) oraz definiuje sposób łączenia plików źródłowych w plik wykonywalny.

#### `README.md` (Dokumentacja)
Główny dokument projektu zawierający instrukcje kompilacji, opis struktury oraz końcowe wnioski z przeprowadzonej analizy efektywności algorytmów.



