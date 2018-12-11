# LFC Gas Reticolare
### Riccardo Riglietti e Ruggero Valli

Questa cartella contiene i file relativi al gas reticolare.
Non è presente uno script di gnuplot perché i programmi c scrivono direttamente i comandi per gnuplot attraverso una pipe.

Dentro a `./plot finali/` sono presenti i migliori plot generati.
Gli altri file sono:
 * `funzioni.h` libreria di funzioni
 * `diffusione_limite.c` genera il grafico del coefficiente di diffusione asintotico per tempi molto lunghi in funzione della densità del gas.
 * `diff_L.c` genera il grafico del coefficiente di diffusione in funzione del numero di passi, per diversi valori della dimensione del reticolo. In questo modo si mostra che il coefficiente è indipendente dalla dimensione del reticolo e che gli effetti di taglia sono trascurabili per grandi dimensioni.
 * `diff_ro.c` genera il grafico del coefficiente di diffusione in funzione del numero di passi, per diversi valori di densità.

eseguire con
```bash
$ gcc -lm diffusione_limite.c funzioni.h && ./a.out
$ gcc -lm diff_L.c funzioni.h && ./a.out
$ gcc -lm diff_ro.c funzioni.h && ./a.out
```
