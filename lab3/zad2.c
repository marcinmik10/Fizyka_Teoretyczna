#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 6
#define NT 5000
#define PI 3.14159265358979323846

double q = 1.0, B = 1.0, m = 1.0;
double omega_c = 1.0; // = qB/m

void pochodne(double t, double *s, double *k) {
    k[0] = s[3] / m;
    k[1] = s[4] / (m * s[0] * s[0]) - q * B / (2 * m);
    k[2] = s[5] / m;
    k[3] = s[4] * s[4] / (m * pow(s[0], 3)) - (q * q * B * B * s[0]) / (4 * m);
    k[4] = 0.0;
    k[5] = 0.0;
}
// Metoda RK4 dla układu równań różniczkowych
void rk4_vec(double t, double dt, int n, double *s, void (*f)(double, double *, double *)) {
    double k1[M], k2[M], k3[M], k4[M], w[M];
    int i;

    f(t, s, k1);
    for (i = 0; i < n; i++) w[i] = s[i] + dt / 2 * k1[i];
    f(t + dt / 2, w, k2);
    for (i = 0; i < n; i++) w[i] = s[i] + dt / 2 * k2[i];
    f(t + dt / 2, w, k3);
    for (i = 0; i < n; i++) w[i] = s[i] + dt * k3[i];
    f(t + dt, w, k4);
    for (i = 0; i < n; i++) s[i] += dt / 6 * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
}
double energia_kinetyczna(double *s) {
    return 0.5 * (
        pow(s[3] / m, 2) +                          // (dr/dt)^2
        pow(s[4] / (m * s[0]), 2) +                // (r*dphi/dt)^2
        pow(s[5] / m, 2)                           // (dz/dt)^2
    ) * m;
}

double energia_potencjalna(double *s) {
    return 0.5 * m * pow(q * B * s[0] / (2 * m), 2);
}

void simulate_case(int case_num, double r0, double phi0, double z0, double pr0, double pphi0, double pz0) {
    char filename[64];
    sprintf(filename, "traj%d.dat", case_num);
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Błąd otwierania pliku");
        exit(1);
    }

    double s[M] = {r0, phi0, z0, pr0, pphi0, pz0};
    double t = 0.0;
    double T = 2 * PI / omega_c;
    double dt = 5 * T / NT;

    for (int i = 0; i < NT; i++) {
        double x = s[0] * cos(s[1]);
        double y = s[0] * sin(s[1]);
        double T_kin = energia_kinetyczna(s);
        double V_pot = energia_potencjalna(s);
        double E = T_kin + V_pot;

        fprintf(fp, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
            t, s[0], s[1], s[2], s[3], s[4], x, y, T_kin, V_pot, E);

        rk4_vec(t, dt, M, s, pochodne);
        t += dt;
    }

    fclose(fp);
}

int main() {
    omega_c = q * B / m;

    // przypadek 0
    double r0 = 1.5;
    double pphi0 = q * B * r0 * r0 / 2.0;
    simulate_case(0, r0, 1.25 * PI, 0, 0, pphi0, 0);

    // przypadek 1
    r0 = 1.0;
    pphi0 = -q * B * r0 * r0 / 2.0;
    simulate_case(1, r0, 0, 0, 0, pphi0, 0);

    // przypadek 2
    r0 = 2.0;
    pphi0 = -q * B * r0 * r0 / 2.0;
    simulate_case(2, r0, 0, 0, 0, pphi0, 0);

    // przypadek 3
    simulate_case(3, r0, 0, 0, 2, pphi0, 0);

    double pz0 = 1.0; // zamiast 0.0
    // przypadek 0
    r0 = 1.5;
    pphi0 = q * B * r0 * r0 / 2.0;
    simulate_case(4, r0, 1.25 * PI, 0, 0, pphi0, pz0);

    // przypadek 1
    r0 = 1.0;
    pphi0 = -q * B * r0 * r0 / 2.0;
    simulate_case(5, r0, 0, 0, 0, pphi0, pz0);

    // przypadek 2
    r0 = 2.0;
    pphi0 = -q * B * r0 * r0 / 2.0;
    simulate_case(6, r0, 0, 0, 0, pphi0, pz0);

    // przypadek 3
    simulate_case(7, r0, 0, 0, 2, pphi0, pz0);

    return 0;
}
