set terminal png size 800,600 enhanced
set title "Diagrammi di biforcazione"
set output "plots/biforcazione.png"
set xlabel "a0 (ampiezza forzante)"
set ylabel "v finale"
set grid
plot "data/biforcazione.dat" u 1:2 w d notitle
