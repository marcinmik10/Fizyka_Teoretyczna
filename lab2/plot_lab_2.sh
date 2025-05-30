set term pngcairo size 4000, 2700 enhanced font "Helvetica,30"
set output "trajektorie_wszystko.png"
set grid lw 1.5
set size square
my_lw = 3

set multiplot layout 3,2

# y(x)
set title "y(x) - trajektorie w płaszczyźnie xy"
set xlabel "x"
set ylabel "y"
plot "traj0.dat" u 7:8 w l lw my_lw t 'traj0', \
     "traj1.dat" u 7:8 w l lw my_lw t 'traj1', \
     "traj2.dat" u 7:8 w l lw my_lw t 'traj2', \
     "traj3.dat" u 7:8 w l lw my_lw t 'traj3'

# E(t)
set title "E(t) - energia całkowita"
set xlabel "t"
set ylabel "E"
plot "traj0.dat" u 1:11 w l lw my_lw t 'traj0', \
     "traj1.dat" u 1:11 w l lw my_lw t 'traj1', \
     "traj2.dat" u 1:11 w l lw my_lw t 'traj2', \
     "traj3.dat" u 1:11 w l lw my_lw t 'traj3'

# r(t)
set title "r(t)"
set xlabel "t"
set ylabel "r"
plot "traj0.dat" u 1:2 w l lw my_lw t 'traj0', \
     "traj1.dat" u 1:2 w l lw my_lw t 'traj1', \
     "traj2.dat" u 1:2 w l lw my_lw t 'traj2', \
     "traj3.dat" u 1:2 w l lw my_lw t 'traj3'

# fi(t)
set title "phi(t)"
set xlabel "t"
set ylabel "phi"
plot "traj0.dat" u 1:3 w l lw my_lw t 'traj0', \
     "traj1.dat" u 1:3 w l lw my_lw t 'traj1', \
     "traj2.dat" u 1:3 w l lw my_lw t 'traj2', \
     "traj3.dat" u 1:3 w l lw my_lw t 'traj3'

# pr(t)
set title "p_r(t)"
set xlabel "t"
set ylabel "p_r"
plot "traj0.dat" u 1:5 w l lw my_lw t 'traj0', \
     "traj1.dat" u 1:5 w l lw my_lw t 'traj1', \
     "traj2.dat" u 1:5 w l lw my_lw t 'traj2', \
     "traj3.dat" u 1:5 w l lw my_lw t 'traj3'

# pphi(t)
set title "p_phi(t)"
set xlabel "t"
set ylabel "p_phi"
plot "traj0.dat" u 1:6 w l lw my_lw t 'traj0', \
     "traj1.dat" u 1:6 w l lw my_lw t 'traj1', \
     "traj2.dat" u 1:6 w l lw my_lw t 'traj2', \
     "traj3.dat" u 1:6 w l lw my_lw t 'traj3'

unset multiplot
###################################################################
set term pngcairo size 4000, 2700 enhanced font "Helvetica,30"
set output "trajektorie_wszystko_pz.png"
set grid lw 1.5
set size square
my_lw = 3

set multiplot layout 3,2

# y(x)
set title "y(x) - trajektorie w płaszczyźnie xy"
set xlabel "x"
set ylabel "y"
plot "traj4.dat" u 7:8 w l lw my_lw t 'traj4', \
     "traj5.dat" u 7:8 w l lw my_lw t 'traj5', \
     "traj6.dat" u 7:8 w l lw my_lw t 'traj6', \
     "traj7.dat" u 7:8 w l lw my_lw t 'traj7'

# E(t)
set title "E(t) - energia całkowita"
set xlabel "t"
set ylabel "E"
plot "traj4.dat" u 1:11 w l lw my_lw t 'traj4', \
     "traj5.dat" u 1:11 w l lw my_lw t 'traj5', \
     "traj6.dat" u 1:11 w l lw my_lw t 'traj6', \
     "traj7.dat" u 1:11 w l lw my_lw t 'traj7'

# r(t)
set title "r(t)"
set xlabel "t"
set ylabel "r"
plot "traj4.dat" u 1:2 w l lw my_lw t 'traj4', \
     "traj5.dat" u 1:2 w l lw my_lw t 'traj5', \
     "traj6.dat" u 1:2 w l lw my_lw t 'traj6', \
     "traj7.dat" u 1:2 w l lw my_lw t 'traj7'

# fi(t)
set title "phi(t)"
set xlabel "t"
set ylabel "phi"
plot "traj4.dat" u 1:3 w l lw my_lw t 'traj4', \
     "traj5.dat" u 1:3 w l lw my_lw t 'traj5', \
     "traj6.dat" u 1:3 w l lw my_lw t 'traj6', \
     "traj7.dat" u 1:3 w l lw my_lw t 'traj7'

# pr(t)
set title "p_r(t)"
set xlabel "t"
set ylabel "p_r"
plot "traj4.dat" u 1:5 w l lw my_lw t 'traj4', \
     "traj5.dat" u 1:5 w l lw my_lw t 'traj5', \
     "traj6.dat" u 1:5 w l lw my_lw t 'traj6', \
     "traj7.dat" u 1:5 w l lw my_lw t 'traj7'

# pphi(t)
set title "p_phi(t)"
set xlabel "t"
set ylabel "p_phi"
plot "traj4.dat" u 1:6 w l lw my_lw t 'traj4', \
     "traj5.dat" u 1:6 w l lw my_lw t 'traj5', \
     "traj6.dat" u 1:6 w l lw my_lw t 'traj6', \
     "traj7.dat" u 1:6 w l lw my_lw t 'traj7'

unset multiplot
