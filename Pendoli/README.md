# LFC
Laboratorio di fisica computazionale: integrazione di equazioni differenziali
Riccardo Riglietti e Ruggero Valli

compilare i diversi file in questo modo:
```bash
gcc integratore.c funzioni.h -lm -o integratore
gcc errore.c funzioni.h -lm -o errore
gcc fasi_poincare.c funzioni.h -lm -o fasi_poincare
gcc biforcazione.c funzioni.h -lm -o biforcazione
gcc attrazione.c funzioni.h -lm -o attrazione
```
poi eseguire
```bash
./integratore
./errore
./fasi_poincare
./biforcazione
./attrazione
```
`biforcazione` e `attrazione` possono impiegare molto tempo a fornire il risultato.

Per ottenere i plot, lanciare
```bash
gnuplot gnuscript.gp
gnuplot biforcazione.gp
```
I programmi prendono l'input dai file che si trovano dentro `./input/` e
scrivono su file dentro `./data/`.
I plot vengono generati nella cartella `./plots/`.
Prima di eseguire i programmi, controllare che queste tre cartelle siano
presenti nella directory corrente.

Dentro a `./plot finali/` si trovano i plot migliori generati con i programmi.
