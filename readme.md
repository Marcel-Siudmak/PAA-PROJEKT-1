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
│   ├── QuickSort.hpp
│   ├── InsertionSort.hpp
│   ├── HeapSort.hpp
│   ├── IntroSort.hpp
│   ├── Menu.hpp
│   ├── Menu.cpp
│   ├── ManualTester.hpp
│   ├── ManualTester.cpp
│   ├── Benchmarks.hpp
│   ├── Benchmarks.cpp
│   ├── DataHandler.hpp
│   └── DataHandler.cpp
├── results/
│   ├── random.csv
│   ├── reverse.csv
│   └── ... 
├── build/
│   ├── paa_projekt_1
│   └── ...
├── CMakeLists.txt
└── readme.md
```


## 4. Szczegółowy Opis Plików i Modułów

### A. Abstrakcja i Interfejsy

#### `ISort.hpp` (Abstrakcja)
Abstrakcyjna klasa bazowa (interfejs) wykorzystująca szablony (**templates**). Definiuje kontrakt dla wszystkich algorytmów sortowania poprzez czysto wirtualną metodę `sort()`. Pozwala to na polimorficzne zarządzanie różnymi algorytmami w module benchmarkowym.

### B. Algorytmy Sortowania (Moduły implementacyjne)

#### `MergeSort`
`MergeSort.hpp` – Implementacja algorytmu sortowania przez scalanie bazująca na `ISort<T>`. Moduł realizuje strategię „dziel i zwyciężaj”, zapewniając stabilność sortowania i niezawodną złożoność $O(n \log n)$.

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



