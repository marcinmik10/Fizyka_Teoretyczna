set term pngcairo size 4000, 2700 enhanced font "Helvetica,30"
set output "trajektorie.png"
set size square
set multiplot layout 2,2
set grid lw 1.5
my_lw = 3

# Trajektorie (r*cos(phi), r*sin(phi)) – rzut na płaszczyznę XY
set title "Przypadek 0: bezruch"
plot "traj0.dat" u ($2*cos($3)):( $2*sin($3)) w l lw my_lw t 'traj0'

set title "Przypadek 1: okrąg wokół (0,0), r=1"
plot "traj1.dat" u ($2*cos($3)):( $2*sin($3)) w l lw my_lw t 'traj1'

set title "Przypadek 2: okrąg wokół (0,0), r=2"
plot "traj2.dat" u ($2*cos($3)):( $2*sin($3)) w l lw my_lw t 'traj2'

set title "Przypadek 3: dowolna orbita"
plot "traj3.dat" u ($2*cos($3)):( $2*sin($3)) w l lw my_lw t 'traj3'

unset multiplot
