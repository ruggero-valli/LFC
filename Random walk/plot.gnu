#1D
set term png size 800, 600 enhanced font "Helvetica,20"
set output "distanza2_vs_tempo1D.png"
set xlabel "t"
set ylabel "d*d"
set log xy
f(x) = m*x + c
fit f(x) 'xt.dat' u 1:2 via m, c
plot "xt.dat", x, m*x +c title "fit"

set term png size 600, 400 enhanced font "Helvetica,20"
set output "distribuzione_posizioni_finali1D.png"
unset log xy
plot "px.dat" with boxes


#2D
set term png size 800, 600 enhanced font "Helvetica,20"
set output "distanza2_vs_tempo2D.png"
set xlabel "t"
set ylabel "d*d"
set log xy
f(x) = m*x + c
fit f(x) 'xt2d.dat' u 1:2 via m, c
plot "xt2d.dat", x, m*x +c title "fit"

set term png size 800, 600 enhanced font "Helvetica,20"
set output "distribuzione_posizioni_finali_2D.png"
unset log xy
set xlabel "x finale"
set ylabel "y finale"
set zlabel "Probabilita' "
splot "px2d.dat" with boxes
pause mouse keypress
