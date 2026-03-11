import pandas as pd
import matplotlib.pyplot as plt
import os

# Konfiguracje do wczytania (nazwy plikow bez rozszerzenia .csv)
configs = [
    ("random", "Random (0%)"),
    ("sorted_25percent", "Sorted (25%)"),
    ("sorted_50percent", "Sorted (50%)"),
    ("sorted_75percent", "Sorted (75%)"),
    ("sorted_95percent", "Sorted (95%)"),
    ("sorted_99percent", "Sorted (99%)"),
    ("sorted_99_7percent", "Sorted (99.7%)")
]

algorithms = [
    ("MergeSort", "SredniCzas_MergeSort[ms]"),
    ("QuickSort", "SredniCzas_QuickSort[ms]"),
    ("IntroSort", "SredniCzas_IntroSort[ms]")
]

colors = ['black', 'blue', 'green', 'lime', 'orange', 'red', 'purple']
markers = ['o', 's', '^', 'v', 'D', 'p', '*']

results_dir = os.path.join(os.path.dirname(__file__), '..', 'results')
plots_dir = os.path.join(os.path.dirname(__file__), '..', 'plots')
os.makedirs(plots_dir, exist_ok=True)

for algo_name, column_name in algorithms:
    plt.figure(figsize=(10, 6))
    plt.title(f"Wpływ wstępnego posortowania na czas wykonania: {algo_name}")
    plt.xlabel("Rozmiar struktury (ilość elementów)")
    plt.ylabel("Czas wykonania [ms]")
    plt.grid(True, linestyle='--', alpha=0.7)

    for i, (config_file, label_name) in enumerate(configs):
        file_path = os.path.join(results_dir, f"{config_file}.csv")
        try:
            df = pd.read_csv(file_path, sep=';')
            if column_name in df.columns:
                # Wypisujemy tylko wartosci wieksze rowne zero (brak bledu)
                valid_data = df[df[column_name] >= 0]
                plt.plot(valid_data['RozmiarTablicy'], valid_data[column_name], 
                         marker=markers[i], color=colors[i], label=label_name, linewidth=2)
        except Exception as e:
            print(f"Blad przetwarzania pliku {file_path}: {e}")

    plt.legend()
    plt.tight_layout()
    plot_path = os.path.join(plots_dir, f"{algo_name}_partially_sorted_impact.png")
    plt.savefig(plot_path, dpi=300)
    plt.close()
    
    print(f"Wygenerowano wykres: {plot_path}")
