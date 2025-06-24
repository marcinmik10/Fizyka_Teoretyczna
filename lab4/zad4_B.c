#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define F 0.01
#define N 50          // liczba atomów - 1 (mamy N+1 atomów)
#define M (2*(N+1))   // liczba zmiennych w układzie (pozycje i prędkości)
#define NSTEPS 5000   // liczba kroków czasowych
#define DT 0.02       // krok czasowy
#define DELTA 0.1     // odległość równowagowa
#define ALPHA 1.0     // stała sprężystości
#define MASS 1.0      // masa atomu
#define SIGMA (3*DELTA)

// Funkcja licząca pochodne ds/dt = velocity oraz d(velocity)/dt = acceleration
void pochodne(double t, double *s, double *dsdt, double alpha, double omega_n) {
    int i;

    // prędkości - pochodne wychyleń
    for (i = 0; i <= N; i++) {
        dsdt[i] = s[N+1 + i];
    }

    // przyspieszenia - pochodne prędkości
    // Brzegowe: si[0] = si[N] = 0 (warunki brzegowe)
    dsdt[N+1 + 0] = 0.0;
    dsdt[N+1 + N] = 0.0;

    for (i = 1; i < N; i++) {
        double wymuszenie = 0.0;
        if (i == 1) {
            wymuszenie = F * sin(omega_n * t);  // wymuszenie tylko na atom nr 1
        }
        dsdt[N+1 + i] = (alpha / MASS) * (s[i-1] - 2 * s[i] + s[i+1]) + wymuszenie / MASS;
    }
}

// RK4 krok
void rk4_step(double *s, double t, double dt, double *s_out, double alpha, double omega_n) {
    double k1[M], k2[M], k3[M], k4[M], temp[M];
    int i;

    pochodne(t, s, k1, alpha, omega_n);
    for (i = 0; i < M; i++) temp[i] = s[i] + 0.5 * dt * k1[i];
    pochodne(t + 0.5 * dt, temp, k2, alpha, omega_n);
    for (i = 0; i < M; i++) temp[i] = s[i] + 0.5 * dt * k2[i];
    pochodne(t + 0.5 * dt, temp, k3, alpha, omega_n);
    for (i = 0; i < M; i++) temp[i] = s[i] + dt * k3[i];
    pochodne(t + dt, temp, k4, alpha, omega_n);

    for (i = 0; i < M; i++)
        s_out[i] = s[i] + (dt / 6.0) * (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
}

// Funkcje do energii
double energia_potencjalna(double *s, double alpha) {
    double U = 0.0;
    for (int i = 0; i < N; i++) {
        double diff = s[i+1] - s[i];
        U += 0.5 * alpha * diff * diff;
    }
    return U;
}

double energia_kinetyczna(double *s) {
    double T = 0.0;
    for (int i = 0; i <= N; i++) {
        double v = s[N+1 + i];
        T += 0.5 * MASS * v * v;
    }
    return T;
}

int main() {
    double n_values[] = {0.9, 1.0, 1.1, 1.5, 2.0, 5.0};
    int num_n = sizeof(n_values) / sizeof(n_values[0]);

    for (int ni = 0; ni < num_n; ni++) {
        double n = n_values[ni];

        // Oblicz omega_n wg wzoru (11)
        double omega_n = 2.0 * sqrt(ALPHA / MASS) * sin(n * M_PI / (2.0 * (N + 1)));

        // Czas symulacji i liczba kroków
        double tmax = 20.0 * 2.0 * M_PI / omega_n;
        int nt = (int)(tmax / DT);

        double s[M] = {0.0};
        double s_new[M];

        // Warunki początkowe:
        // s_i = 0 (położenia równowagi)
        // prędkości = 0
        for (int i = 0; i <= N; i++) {
            s[i] = 0.0;
            s[N+1 + i] = 0.0;
        }

        char filename[64];
        snprintf(filename, sizeof(filename), "x_%.1f.dat", n);
        char energyfile[64];
        snprintf(energyfile, sizeof(energyfile), "energy_%.1f.dat", n);

        FILE *f = fopen(filename, "w");
        FILE *fe = fopen(energyfile, "w");
        if (!f || !fe) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        for (int t_step = 0; t_step <= nt; t_step++) {
            double t = t_step * DT;

            // zapis wychyleń atomów (np. pierwszych kilku, lub wszystkich)
            for (int i = 0; i <= N; i++) {
                fprintf(f, "%g\t%g\t%g\n", i * DELTA, t, s[i]);
            }
            fprintf(f, "\n");

            // liczenie energii
            double U = energia_potencjalna(s, ALPHA);
            double T = energia_kinetyczna(s);
            double E = U + T;
            fprintf(fe, "%g\t%g\t%g\t%g\n", t, U, T, E);

            rk4_step(s, t, DT, s_new, ALPHA, omega_n);

            for (int i = 0; i < M; i++)
                s[i] = s_new[i];
        }

        fclose(f);
        fclose(fe);
        printf("Wygenerowano pliki: %s, %s\n", filename, energyfile);
    }

    return 0;
}
