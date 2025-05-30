set title "Okres wahadła T[\phi_{max}]"
set xlabel "Wychylenie maksymalne (rad)"
set ylabel "Okres (s)"
set grid
set key left top
set term pngcairo size 800,600 enhanced font 'Arial,12'
set output 'periods_plot.png'

plot "periods.dat" using 1:2 with linespoints lt rgb "blue" lw 2 pt 7 ps 1.2 title "Okres"
