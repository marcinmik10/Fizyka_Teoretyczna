reset
set terminal pngcairo size 1200,800 enhanced font 'Arial,12'

# Wspólne ustawienia
set xlabel "ρ [cm]"
set ylabel "z [cm]"
set zlabel "V(ρ, z) [V]"

# Zakładamy, że dane są w pliku potential.dat: kolumny 1: ρ, 2: z, 3: V
set datafile separator whitespace

############################
# 1. Mapa 2D potencjału V(ρ,z)
############################
set output "mapa_2D.png"
set title "Mapa 2D potencjału V(ρ,z)"
unset surface
set view map
set pm3d interpolate 2,2
set palette rgb 33,13,10
splot "potential.dat" using 1:2:3 with pm3d notitle

############################
# 2. Mapa 3D (izometryczna)
############################
set output "mapa_3D.png"
set title "Mapa 3D potencjału V(ρ,z)"
set view 60,30
set pm3d
splot "potential.dat" using 1:2:3 with pm3d notitle

############################
# 3. Przekrój wzdłuż osi symetrii ρ=0 → V(0, z)
############################
# Tworzymy pomocniczy plik z przekrojem
set output
set print "V_rho0.dat"
do for [j=0:150] {
    print 0, j*0.1, system(sprintf("awk '$1==0.0 && $2==%.1f {print $3}' potential.dat", j*0.1))
}
unset print

set output "przekroj_rho0.png"
set title "Przekrój V(0, z) + parabola"
set xlabel "z [cm]"
set ylabel "V [V]"
set grid
f1(z) = a*z**2 + b*z + c
fit f1(x) "V_rho0.dat" using 2:3 via a, b, c
plot "V_rho0.dat" using 2:3 with points pt 7 lc rgb "blue" title "V(0,z)", \
     f1(x) with lines lw 2 lc rgb "red" title "Parabola"

############################
# 4. Przekrój wzdłuż z = (j1+j2)/2 * dz = (60+90)/2 * 0.1 = 7.5 cm
# czyli dla z = 7.5 → fix tolerancję porównania
############################
set print "V_zp.dat"
do for [i=0:30] {
    print i*0.1, 7.5, system(sprintf("awk '$2==7.5 && $1==%.1f {print $3}' potential.dat", i*0.1))
}
unset print

set output "przekroj_zp.png"
set title "Przekrój V(ρ, z=7.5) + parabola"
set xlabel "ρ [cm]"
set ylabel "V [V]"
set grid
f2(rho) = A*rho**2 + B*rho + C
fit f2(x) "V_zp.dat" using 1:3 via A, B, C
plot "V_zp.dat" using 1:3 with points pt 7 lc rgb "blue" title "V(ρ, 7.5)", \
     f2(x) with lines lw 2 lc rgb "red" title "Parabola"
