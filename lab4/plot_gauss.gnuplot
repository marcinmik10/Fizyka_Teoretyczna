##############################
# 1. Mapa wychyleń x(i,t)
##############################
set terminal pngcairo size 1000,800 enhanced font 'Arial,12'
set output "x_gauss_map.png"

set title "Wychylenia atomów w czasie (x(i,t))"
set xlabel "Numer atomu i"
set ylabel "Czas t"
set cblabel "Wychylenie x_i - x_i,0"
set palette rgb 33,13,10
set view map
set size ratio -1
unset key

splot "x_gauss.dat" using 2:1:3 with image

##############################
##############################
# 2. Energia w czasie
##############################
set terminal pngcairo size 1200,800 enhanced font 'Arial,14'
set output "energy_plot.png"

set title "Energia kinetyczna, potencjalna i całkowita"
set xlabel "Czas t"
set ylabel "Energia (x10^-5)"
set grid
set key top right
unset size
set autoscale
set yrange [0:*]

plot "energy_gauss.dat" using 1:($2*1e5) with lines lw 2 title "T(t) - kinetyczna x1e5", \
     "energy_gauss.dat" using 1:($3*1e5) with lines lw 2 title "U(t) - potencjalna x1e5", \
     "energy_gauss.dat" using 1:($4*1e5) with lines lw 2 title "E(t) - całkowita x1e5"
