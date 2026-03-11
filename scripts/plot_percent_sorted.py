import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

sns.set_theme(style="whitegrid", palette="deep")

configs = [
    ("random", 0),
    ("sorted_25percent", 25),
    ("sorted_50percent", 50),
    ("sorted_75percent", 75),
    ("sorted_95percent", 95),
    ("sorted_99percent", 99),
    ("sorted_99_7percent", 99.7)
]

algorithms = [
    ("MergeSort", "SredniCzas_MergeSort[ms]"),
    ("QuickSort", "SredniCzas_QuickSort[ms]"),
    ("IntroSort", "SredniCzas_IntroSort[ms]")
]

results_dir = os.path.join(os.path.dirname(__file__), '..', 'results')
plots_dir = os.path.join(os.path.dirname(__file__), '..', 'plots', 'percent_sorted')
os.makedirs(plots_dir, exist_ok=True)

# First, structure data by array size
data_by_size = {}

for config_file, percent in configs:
    file_path = os.path.join(results_dir, f"{config_file}.csv")
    try:
        df = pd.read_csv(file_path, sep=';')
        for index, row in df.iterrows():
            size = int(row['RozmiarTablicy'])
            if size not in data_by_size:
                data_by_size[size] = []
            
            data_entry = {'percent': percent}
            for algo_name, col_name in algorithms:
                if col_name in row:
                    data_entry[algo_name] = row[col_name]
                else:
                    data_entry[algo_name] = None
            
            data_by_size[size].append(data_entry)
            
    except Exception as e:
        print(f"Błąd przetwarzania pliku {file_path}: {e}")

# Now plot for each size
for size, records in data_by_size.items():
    # Sort by percent to ensure plot lines are drawn correctly left to right
    records.sort(key=lambda x: x['percent'])
    
    percents = [r['percent'] for r in records]
    
    plt.figure(figsize=(10, 6))
    plt.xlabel("% Posortowanych Pierwszych Elementów", fontsize=12, fontweight='bold')
    plt.ylabel("Czas Wykonania [ms]", fontsize=12, fontweight='bold')
    plt.grid(True, linestyle='--', alpha=0.6)
    
    colors = {'MergeSort': sns.color_palette("deep")[0], 'QuickSort': sns.color_palette("deep")[1], 'IntroSort': sns.color_palette("deep")[2]}
    markers = {'MergeSort': 'o', 'QuickSort': 'o', 'IntroSort': 'o'}
    
    for algo_name, _ in algorithms:
        times = [r.get(algo_name) for r in records]
        # Wypisujemy tylko poprawne wartości
        valid_percents = []
        valid_times = []
        for p, t in zip(percents, times):
            if t is not None and t >= 0:
                valid_percents.append(p)
                valid_times.append(t)
        
        if valid_percents:
             plt.plot(valid_percents, valid_times, marker=markers[algo_name], color=colors[algo_name], label=algo_name, linewidth=2, markersize=4)
        
    plt.legend(frameon=True, shadow=True, title="Algorytmy", title_fontsize='11', fontsize='10')
    plt.tight_layout()
    plot_path = os.path.join(plots_dir, f"percent_sorted_impact_size_{size}.png")
    plt.savefig(plot_path, dpi=300)
    plt.close()
    print(f"Wygenerowano wykres: {plot_path}")
