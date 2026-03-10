# 1. Wymagana wersja CMake
cmake_minimum_required(VERSION 3.10)

# 2. Nazwa projektu 
project(PAA_PROJEKT_1 VERSION 1.0 LANGUAGES CXX)

# 3. Konfiguracja standardu C++ (C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 4. Automatyczne wyszukiwanie wszystkich plików .cpp w folderze src
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 5. Dodanie folderu src do ścieżek poszukiwań nagłówków (.hpp)
# Dzięki temu w kodzie piszesz #include "ArrayList.hpp" zamiast #include "src/ArrayList.hpp"
include_directories(src)

# 6. Tworzenie pliku wykonywalnego
add_executable(paa_projekt_1 ${SOURCES})

# 7. Automatyczne kopiowanie folderu 'data' do folderu 'build'
# Dzięki temu program zawsze znajdzie pliki tekstowe w folderze "data/" obok pliku .exe
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# 8. Flagi ostrzeżeń (Warnings) - pomagają wyłapać błędy w kodzie na etapie kompilacji
if(MSVC)
    target_compile_options(paa_projekt_1 PRIVATE /W4)
else()
    target_compile_options(paa_projekt_1 PRIVATE -Wall -Wextra -Wpedantic)
endif()