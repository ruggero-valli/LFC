Ci chiediamo quanto a lungo possa camminare un punto che si muove casualmente
sempre evitando i posti che ha già visitato prima di ritrovarsi "intrappolato" cioè "rinchiuso"
all'interno di quadrati tutti già visitati da lui.

Si è implementato questo tramite una matrice 2D di larghe dimensioni (si noti che la distanza percorsa
dipende solo dalla radice del numero dei passi nella random walk quindi il punto si muove poco, la matrice basta
poco più grande per lato del numero di passi). Si segna in questa matrice dove il punto è gia stato e questo permette di 
controllare in tempi molto brevi se una coppia di coordinate è già stata visitata.

Si è generato un grafico che evidenzia la relazione tra numero di passi e probabilità di intrappolamento.
