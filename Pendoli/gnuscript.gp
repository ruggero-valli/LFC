#Script for gnuplot
set terminal png size 800,600 enhanced
set title "Legge oraria"
set output "plots/legge_oraria.png"
set xlabel "t"
set ylabel "x"
set grid
plot "data/simulazione.dat" u 1:2 w l notitle
reset

set terminal png size 800,600 enhanced
set title "Spazio delle Fasi"
set output "plots/spazio_fasi.png"
set xlabel "x"
set ylabel "v"
set grid
plot "data/simulazione.dat" u 2:3 w l notitle
reset

set terminal png size 800,600 enhanced
set title "Sezioni di Poincare"
set output "plots/poincare.png"
set xlabel "x"
set ylabel "v"
set grid
plot "data/spazio_fasi_poincare.dat" w d notitle, "data/poincare.dat" pt 7 ps 0.5 notitle
reset

set terminal png size 800,600 enhanced
set title "Errore nell'oscillatore armonico"
set output "plots/energia_errore_vs_dt.png"
set xlabel "dt"
set ylabel "dE/E"
set log xy
set format y "10^{%L}"
set format x "10^{%L}"
set grid
plot "data/energia_errore_vs_dt.dat" u 2:1 notitle, x, x**2, x**3, x**4, x**5
reset

#set contour base
#set cntrparam level incremental -3, 1, 3
#unset surface
#set table 'contour.dat'
#splot 'attrazione_out.dat'
#unset table
reset

set output "plots/attrazione.png"
#set xrange [-20:20]
#set yrange [-20:20]
unset key
set palette rgbformulae 33,13,10
#set palette gray
#plot 'data/attrazione_out.dat' with image#, 'contour.dat' with lines linetype -1 linewidth 1.5
