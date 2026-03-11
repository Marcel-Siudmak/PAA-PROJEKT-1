import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

sns.set_theme(style="whitegrid", palette="colorblind")

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

palette = sns.color_palette("colorblind", 10)
# Pomijamy różowy (indeks 6), wybieramy 7 wyraźnych kolorów
colors = [palette[0], palette[1], palette[2], palette[3], palette[4], palette[5], palette[7]]
markers = ['o'] * 7

results_dir = os.path.join(os.path.dirname(__file__), '..', 'results')
plots_dir = os.path.join(os.path.dirname(__file__), '..', 'plots', 'partially_sorted')
os.makedirs(plots_dir, exist_ok=True)

for algo_name, column_name in algorithms:
    plt.figure(figsize=(10, 6))
    plt.xlabel("Rozmiar struktury (ilość elementów)", fontsize=12, fontweight='bold')
    plt.ylabel("Czas wykonania [ms]", fontsize=12, fontweight='bold')
    plt.grid(True, linestyle='--', alpha=0.6)

    for i, (config_file, label_name) in enumerate(configs):
        file_path = os.path.join(results_dir, f"{config_file}.csv")
        try:
            df = pd.read_csv(file_path, sep=';')
            if column_name in df.columns:
                # Wypisujemy tylko wartosci wieksze rowne zero (brak bledu)
                valid_data = df[df[column_name] >= 0]
                plt.plot(valid_data['RozmiarTablicy'], valid_data[column_name], 
                         marker=markers[i], color=colors[i], label=label_name, linewidth=2, markersize=4)
        except Exception as e:
            print(f"Blad przetwarzania pliku {file_path}: {e}")

    plt.legend(frameon=True, shadow=True, title="Układ Danych", title_fontsize='11', fontsize='10')
    plt.tight_layout()
    plot_path = os.path.join(plots_dir, f"{algo_name}_partially_sorted_impact.png")
    plt.savefig(plot_path, dpi=300)
    plt.close()
    
    print(f"Wygenerowano wykres: {plot_path}")
