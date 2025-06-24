##############################
##############################
# 1. Mapa wychyleń x(i,t)
##############################
set terminal pngcairo size 1000,800 enhanced font 'Arial,12'
set output "x_gauss_map.png"

set title "Wychylenia atomów w czasie (x(i,t))"
set xlabel "x"
set ylabel "t"
set cblabel "Wychylenie x_i - x_i,0"
set palette rgb 33,13,10
set view map
set size ratio 0.5  # <- ZMIANA: mniej ekstremalny stosunek osi
unset key

#splot "x_gauss.dat" using 2:1:3 with image
splot "x_gauss.dat" using 2:1:3 with image


##############################
##############################
# 2. Energia w czasie
##############################
set terminal pngcairo size 1000,600 enhanced font 'Arial,12'
set output "energy_plot.png"

set title "Energia kinetyczna, potencjalna i całkowita"
set xlabel "Czas t"
set ylabel "Energia"
set grid
set key top right
#set format y "%.1e"  # wykres bardziej czytelny przy małych wartościach

plot "energy_gauss.dat" using 1:2 with lines lw 2 title "T(t) - kinetyczna", \
     "energy_gauss.dat" using 1:3 with lines lw 2 title "U(t) - potencjalna", \
     "energy_gauss.dat" using 1:4 with lines lw 2 title "E(t) - całkowita"
