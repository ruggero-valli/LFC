#gcc integratore.c funzioni.h -lm -o integratore
#gcc errore.c funzioni.h -lm -o errore
#gcc fasi_poincare.c funzioni.h -lm -o fasi_poincare
gcc biforcazione.c funzioni.h -lm -o biforcazione
#./integratore
#./errore
#./fasi_poincare
./biforcazione
#gnuplot gnuscript.gp
gnuplot biforcazione.gp
#rm integratore errore fasi_poincare
rm biforcazione
