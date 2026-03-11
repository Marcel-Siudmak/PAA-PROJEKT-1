import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

sns.set_theme(style="whitegrid", palette="deep")

def generate_plots(results_dir='../results', plots_dir='../plots/basic_distributions'):
    if not os.path.exists(results_dir):
        return

    if not os.path.exists(plots_dir):
        os.makedirs(plots_dir)

    for filename in os.listdir(results_dir):
        if filename.endswith('.csv'):
            filepath = os.path.join(results_dir, filename)
            # Wczytywanie z separatorem średnika (tak jak zapisuje C++)
            df = pd.read_csv(filepath, sep=';')
            
            distribution_name = os.path.splitext(filename)[0]
            
            plt.figure(figsize=(10, 6))
            
            # Nasze CSV ma kolumny: RozmiarTablicy;SredniCzas_MergeSort[ms];SredniCzas_QuickSort[ms];SredniCzas_IntroSort[ms]
            plt.plot(df['RozmiarTablicy'], df['SredniCzas_MergeSort[ms]'], marker='o', linestyle='-', label='MergeSort', linewidth=2, markersize=4)
            plt.plot(df['RozmiarTablicy'], df['SredniCzas_QuickSort[ms]'], marker='o', linestyle='-', label='QuickSort', linewidth=2, markersize=4)
            plt.plot(df['RozmiarTablicy'], df['SredniCzas_IntroSort[ms]'], marker='o', linestyle='-', label='IntroSort', linewidth=2, markersize=4)
            
            plt.xlabel('Rozmiar Struktury (Ilość Elementów)', fontsize=12, fontweight='bold')
            plt.ylabel('Czas Wykonania [ms]', fontsize=12, fontweight='bold')
            plt.legend(frameon=True, shadow=True, title="Algorytmy", title_fontsize='11', fontsize='10')
            plt.grid(True, linestyle='--', alpha=0.6)
            plt.tight_layout()
            
            output_path = os.path.join(plots_dir, f'{distribution_name}_plot.png')
            plt.savefig(output_path)
            plt.close()

if __name__ == "__main__":
    generate_plots()

