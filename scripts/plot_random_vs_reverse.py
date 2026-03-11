import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

sns.set_theme(style="whitegrid", palette="deep")

results_dir = os.path.join(os.path.dirname(__file__), '..', 'results')
plots_dir = os.path.join(os.path.dirname(__file__), '..', 'plots', 'random_vs_reverse')
os.makedirs(plots_dir, exist_ok=True)

algorithms = [
    ("MergeSort", "SredniCzas_MergeSort[ms]"),
    ("QuickSort", "SredniCzas_QuickSort[ms]"),
    ("IntroSort", "SredniCzas_IntroSort[ms]")
]

colors = {'MergeSort': sns.color_palette("deep")[0], 'QuickSort': sns.color_palette("deep")[1], 'IntroSort': sns.color_palette("deep")[2]}
markers = {'MergeSort': 'o', 'QuickSort': 'o', 'IntroSort': 'o'}

try:
    df_random = pd.read_csv(os.path.join(results_dir, "random.csv"), sep=';')
    df_reverse = pd.read_csv(os.path.join(results_dir, "reverse.csv"), sep=';')
except Exception as e:
    print(f"Błąd wczytywania plików CSV: {e}")
    exit(1)

plt.figure(figsize=(10, 6))
plt.xlabel("Rozmiar Struktury (Ilość Elementów)", fontsize=12, fontweight='bold')
plt.ylabel("Czas Wykonania [ms]", fontsize=12, fontweight='bold')
plt.grid(True, linestyle='--', alpha=0.6)

# Mamy x=RozmiarTablicy i y=Czas
for algo_name, col_name in algorithms:
    if col_name in df_random.columns and col_name in df_reverse.columns:
        
        # Filtrujemy tylko wartości poprawne (>= 0)
        valid_random = df_random[df_random[col_name] >= 0]
        valid_reverse = df_reverse[df_reverse[col_name] >= 0]
        
        # Plot random (ciągła linia)
        plt.plot(valid_random['RozmiarTablicy'], valid_random[col_name],
                 color=colors[algo_name], marker=markers[algo_name], linestyle='-',
                 linewidth=2, markersize=4, label=f"{algo_name} (Losowe)")
        
        # Plot reverse (przerywana linia)
        plt.plot(valid_reverse['RozmiarTablicy'], valid_reverse[col_name],
                 color=colors[algo_name], marker=markers[algo_name], linestyle='--',
                 linewidth=2, markersize=4, label=f"{algo_name} (Odwrotne)")

plt.legend(frameon=True, shadow=True, title="Algorytm i Dane", title_fontsize='11', fontsize='10')
plt.tight_layout()
plot_path = os.path.join(plots_dir, "random_vs_reverse_comparison.png")
plt.savefig(plot_path, dpi=300)
plt.close()

print(f"Wygenerowano wykres: {plot_path}")
