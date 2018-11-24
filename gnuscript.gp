#Script for gnuplot
set terminal png size 800,600 enhanced
set title "Legge oraria"
set output "plots/legge_oraria.png"
set xlabel "t"
set ylabel "x"
set grid
plot "data/simulazione.dat" u 1:2 w l notitle

set terminal png size 800,600 enhanced
set title "Spazio delle Fasi"
set output "plots/spazio_fasi.png"
set xlabel "x"
set ylabel "v"
set grid
plot "data/simulazione.dat" u 2:3 w l notitle

set terminal png size 800,600 enhanced
set title "Errore"
set output "plots/energia_errore_vs_dt.png"
set xlabel "dt"
set ylabel "dE/E"
set log xy
set grid
plot "data/energia_errore_vs_dt.dat" u 1:2 notitle, x, x*x*x*x, 4*x
