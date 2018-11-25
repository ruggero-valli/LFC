gcc integratore.c funzioni.h -lm -o integratore
gcc errore.c funzioni.h -lm -o errore
rm funzioni.h.gch
./integratore
./errore
gnuplot gnuscript.gp
