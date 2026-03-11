import os
import pandas as pd
import glob

def generate_csv_tables():
    results_dir = os.path.join(os.path.dirname(__file__), '..', 'results')
    tables_dir = os.path.join(os.path.dirname(__file__), '..', 'tables')
    
    # Utworz folder tables jesli nie istnieje
    os.makedirs(tables_dir, exist_ok=True)
    
    algos = {
        "MergeSort": "SredniCzas_MergeSort[ms]",
        "QuickSort": "SredniCzas_QuickSort[ms]",
        "IntroSort": "SredniCzas_IntroSort[ms]"
    }
    
    # Słownik przechowujący dane w formacie:
    # { AlgoName: { DistributionName: { Size: Time } } }
    data = {"MergeSort": {}, "QuickSort": {}, "IntroSort": {}}
    
    # Znajdź wszystkie pliki .csv w folderze results
    csv_files = glob.glob(os.path.join(results_dir, "*.csv"))
    
    for file_path in csv_files:
        filename = os.path.basename(file_path)
        dist_name = os.path.splitext(filename)[0]
        
        try:
            df = pd.read_csv(file_path, sep=';')
            
            # Wypełniamy słownik dla każdego algorytmu
            for algo, col_name in algos.items():
                if col_name in df.columns:
                    if dist_name not in data[algo]:
                        data[algo][dist_name] = {}
                        
                    for _, row in df.iterrows():
                        size = int(row['RozmiarTablicy'])
                        time = row[col_name]
                        
                        # Zapisuj tylko jeśli czas jest poprawny
                        if time >= 0:
                            data[algo][dist_name][size] = time
                            
        except Exception as e:
            print(f"Błąd przetwarzania pliku {file_path}: {e}")
            
    # Teraz generujemy i zapisujemy pliki CSV
    for algo, dist_data in data.items():
        if not dist_data:
            continue
            
        # Zbuduj DataFrame
        # dist_data to słownik {dist: {size: time}}
        # Orient="index" utworzy wiersze z kluczy głównego słownika (dist), kolumny to size
        df_out = pd.DataFrame.from_dict(dist_data, orient='index')
        
        # Posortuj kolumny (Rozmiar tablicy) rosnąco, jeśli istnieją
        df_out = df_out.reindex(sorted(df_out.columns), axis=1)
        
        # Sortuj wiersze po nazwie dystrybucji, by było czytelniej
        df_out = df_out.sort_index()
        
        # Nazwij indeks ("Oś y")
        df_out.index.name = "Rozkład Danych \\ Rozmiar"
        
        output_file = os.path.join(tables_dir, f"{algo}_times.csv")
        # Zapisz do CSV z separatorem średnika dla łatwego importu np. do Excela
        df_out.to_csv(output_file, sep=';')
        
        print(f"Wygenerowano tabelę dla {algo}: {output_file}")
        
if __name__ == "__main__":
    print("Rozpoczęto generowanie tabel...")
    generate_csv_tables()
    print("Zakończono.")
