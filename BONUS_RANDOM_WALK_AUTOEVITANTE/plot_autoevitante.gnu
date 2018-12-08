set terminal png size 800,600;
set output 'random_walk_autoevitante_blocco.png';
set title "Random Walk Auto-Evitante"
set xlabel "Numero di passi"
set ylabel "Probabilità di blocco"
plot "autoevitante_blocco.dat" using 1:2

