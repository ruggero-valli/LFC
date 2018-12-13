Facciamo statistica su quanto a lungo possa camminare un punto che si muove casualmente
sempre evitando i posti che ha già visitato prima di ritrovarsi "intrappolato" cioè "rinchiuso"
all'interno di quadrati tutti già visitati da lui.

Si è implementato questo tramite una matrice 2D di larghe dimensioni (si noti che la distanza percorsa
dipende solo dalla radice del numero dei passi nella random walk quindi il punto si muove poco, la matrice basta
poco più grande per lato del numero di passi). Si segna in questa matrice dove il punto è gia stato e questo permette di
controllare in tempi molto brevi se una coppia di coordinate è già stata visitata.

Si è generato un grafico che evidenzia la relazione tra numero di passi e probabilità di intrappolamento.

Eseguire con:
```bash
 $ gcc -pedantic -Wall random_walk_autoevitante.c -lm -O3 && ./a.out > "autoevitante_blocco.dat"
 $ gnuplot plot_autoevitante.gnu
```

In caso di mancanza di tempo ridurre le costanti definite all'inizio, il grafico verrà
meno preciso e fino a un numero massimo di passi minore ma ci vorrà meno tempo per eseguire il codice:
```c
    #define N_SIMULAZIONI 15000
    #define MAX_PASSI 300
```
