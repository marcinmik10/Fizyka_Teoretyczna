set term pngcairo size 2000, 1500 enhanced font "Helvetica,30"
set size ratio -1
set ticslevel 0
set grid

# trajektoria 3D: traj0
set output "traj4_3D.png"
set title "Trajektoria 3D - przypadek 0"
splot "traj4.dat" u 7:8:4 with lines linewidth 3 linecolor rgb "blue" title "traj0"

# trajektoria 3D: traj1
set output "traj5_3D.png"
set title "Trajektoria 3D - przypadek 1"
splot "traj5.dat" u 7:8:4 with lines linewidth 3 linecolor rgb "red" title "traj1"

# trajektoria 3D: traj2
set output "traj6_3D.png"
set title "Trajektoria 3D - przypadek 2"
splot "traj6.dat" u 7:8:4 with lines linewidth 3 linecolor rgb "green" title "traj2"

# trajektoria 3D: traj3
set output "traj7_3D.png"
set title "Trajektoria 3D - przypadek 3"
splot "traj7.dat" u 7:8:4 with lines linewidth 3 linecolor rgb "orange" title "traj3"
