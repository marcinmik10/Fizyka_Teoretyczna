#################################################################
###    Wykresy energii

#set term postscript color enhanced solid font 'Helvetica, 30'
# set term png color enhanced solid font 'Helvetica, 30'
#set size square


#################################################################
reset

set term pngcairo size 1200, 1700 enhanced font "Helvetica, 45"


#set term postscript color enhanced solid font 'Helvetica, 20'
# set term png color enhanced solid font 'Helvetica, 20'
set size 0.9,1.0
#set size square
#set size ratio 3

set nokey

set view map
set palette defined (-1 'blue',0 'white', 1 'red')
set xlabel 'x'
set ylabel 't'


set out 'x_gauss.png'
set title 'gauss'
splot 'x_gauss.dat' u 1:2:3 w pm3d

set title 'n=0.9'
set out 'x_0.9.png'
splot 'x_0.9.dat' u 1:2:3 w pm3d

set cbrange[-0.5:0.5]
set title 'n=1.0'
set out 'x_1.0.png'
splot 'x_1.0.dat' u 1:2:3 w pm3d
set cbrange[*:*]


set title 'n=1.1'
set out 'x_1.1.png'
splot 'x_1.1.dat' u 1:2:3 w pm3d


set title 'n=1.5'
set out 'x_1.5.png'
splot 'x_1.5.dat' u 1:2:3 w pm3d


set cbrange[-0.25:0.25]
set title 'n=2.0'
set out 'x_2.0.png'
splot 'x_2.0.dat' u 1:2:3 w pm3d
set cbrange[*:*]


set title 'n=5.0'
set out 'x_5.0.png'
splot 'x_5.0.dat' u 1:2:3 w pm3d
#################################################################
#################################################################
###    Wykresy energii

set term pngcairo size 2000, 1500 enhanced font "Helvetica, 45"
set xlabel "czas t"
set ylabel "energia"
set key top right

set title "Energia: n = 0.9"
set out 'energy_0.9.png'
plot 'energy_0.9.dat' u 1:2 w l lw 3 lc rgb "blue" title 'T', \
     '' u 1:3 w l lw 3 lc rgb "red" title 'U', \
     '' u 1:4 w l lw 3 lc rgb "black" title 'E'

set title "Energia: n = 1.0"
set out 'energy_1.0.png'
plot 'energy_1.0.dat' u 1:2 w l lw 3 lc rgb "blue" title 'T', \
     '' u 1:3 w l lw 3 lc rgb "red" title 'U', \
     '' u 1:4 w l lw 3 lc rgb "black" title 'E'

set title "Energia: n = 1.1"
set out 'energy_1.1.png'
plot 'energy_1.1.dat' u 1:2 w l lw 3 lc rgb "blue" title 'T', \
     '' u 1:3 w l lw 3 lc rgb "red" title 'U', \
     '' u 1:4 w l lw 3 lc rgb "black" title 'E'

set title "Energia: n = 1.5"
set out 'energy_1.5.png'
plot 'energy_1.5.dat' u 1:2 w l lw 3 lc rgb "blue" title 'T', \
     '' u 1:3 w l lw 3 lc rgb "red" title 'U', \
     '' u 1:4 w l lw 3 lc rgb "black" title 'E'

set title "Energia: n = 2.0"
set out 'energy_2.0.png'
plot 'energy_2.0.dat' u 1:2 w l lw 3 lc rgb "blue" title 'T', \
     '' u 1:3 w l lw 3 lc rgb "red" title 'U', \
     '' u 1:4 w l lw 3 lc rgb "black" title 'E'

set title "Energia: n = 5.0"
set out 'energy_5.0.png'
plot 'energy_5.0.dat' u 1:2 w l lw 3 lc rgb "blue" title 'T', \
     '' u 1:3 w l lw 3 lc rgb "red" title 'U', \
     '' u 1:4 w l lw 3 lc rgb "black" title 'E'