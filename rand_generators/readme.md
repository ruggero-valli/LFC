Si sono implementatati l' "infamous" randu e il minimal standard, al fine
di mettere in evidenza tramite rappresentazione a 3 a 3 dei numeri generati che i numeri
generati con randu si posizionano su pochi piani, quelli con minimal standard no.

Eseguire con

    > gcc -pedantic -Wall rand_generator.c -lm -O3 &&  ./a.out
    > gnuplot 'gauss_hist.gnu' -persist
    > gnuplot 'plot_minimal_standard.gnu' -persist
    > gnuplot 'plot_randu.gnu' -persist

E' possibile ruotare i grafici tridimensionali. Questo è specialmente interessante nel caso di randu perchè si vedono piani con la rotazione giusta.

Si sfrutta anche il metodo di Box-Muller per ottenere una variabile distribuita
come una gaussiana e se ne fa l'istogramma.

