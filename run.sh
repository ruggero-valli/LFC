gcc integratore.c funzioni.h -lm -o integratore
gcc errore.c funzioni.h -lm -o errore
gcc fasi_poincare.c funzioni.h -lm -o fasi_poincare
./integratore
./errore
./fasi_poincare
gnuplot gnuscript.gp
rm integratore errore fasi_poincare
