import os
import sys
import subprocess
import glob

def main():
    scripts_dir = os.path.dirname(os.path.abspath(__file__))
    
    # Znajdź wszystkie skrypty zaczynające się na "plot"
    plot_scripts = glob.glob(os.path.join(scripts_dir, "plot*.py"))
    
    current_script = os.path.basename(__file__)
    
    for script_path in sorted(plot_scripts):
        script_name = os.path.basename(script_path)
        if script_name == current_script:
            continue
            
        print(f"\n=> Uruchamianie skryptu: {script_name}")
        try:
            subprocess.run([sys.executable, script_name], cwd=scripts_dir, check=True)
            print(f"   [SUKCES] Wygenerowano wykresy z {script_name}.")
        except subprocess.CalledProcessError as e:
            print(f"   [BŁĄD] Wystąpił błąd podczas wykonywania {script_name}: {e}")
        except Exception as e:
            print(f"   [BŁĄD] {e}")

if __name__ == "__main__":
    print("=== Rozpoczęto masowe generowanie wykresów ===")
    main()
    print("\n=== Zakończono. Wszystkie wykresy są w podfolderach katalogu 'plots'. ===")
