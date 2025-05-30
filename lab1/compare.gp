set xlabel "Czas t [s]"
set ylabel "Kąt wychylenia φ(t) [rad]"
set grid

plot "compare.dat" using 1:2 with lines title "Numeryczne", \
     "compare.dat" using 1:3 with lines title "Analityczne"
