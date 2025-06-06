#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 50
#define M (2*(N+1))
#define DT 0.02
#define NT 5000
#define DELTA 0.1
#define MASS 1.0
#define SIGMA (3*DELTA)

void pochodne(double t, double *s, double *dsdt, double alpha) {
    int i;
    for (i = 1; i < N; i++) dsdt[i] = s[N+1 + i];
    dsdt[0] = 0.0;
    dsdt[N] = 0.0;

    for (i = 1; i < N; i++)
        dsdt[N+1 + i] = (alpha / MASS) * (s[i-1] - 2*s[i] + s[i+1]);

    dsdt[N+1] = 0.0;
    dsdt[2*N+1] = 0.0;
}

void rk4_step(double *s, double t, double dt, double *s_out, double alpha) {
    double k1[M], k2[M], k3[M], k4[M], temp[M];
    int i;

    pochodne(t, s, k1, alpha);
    for (i = 0; i < M; i++) temp[i] = s[i] + 0.5 * dt * k1[i];
    pochodne(t + 0.5 * dt, temp, k2, alpha);
    for (i = 0; i < M; i++) temp[i] = s[i] + 0.5 * dt * k2[i];
    pochodne(t + 0.5 * dt, temp, k3, alpha);
    for (i = 0; i < M; i++) temp[i] = s[i] + dt * k3[i];
    pochodne(t + dt, temp, k4, alpha);

    for (i = 0; i < M; i++)
        s_out[i] = s[i] + (dt / 6.0) * (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
}

int main() {
    double n_values[] = {0.9, 1.0, 1.1, 1.5, 2.0, 5.0};
    int num_n = sizeof(n_values) / sizeof(n_values[0]);

    for (int ni = 0; ni < num_n; ni++) {
        double n = n_values[ni];
        double alpha = n / DELTA;

        double s[M] = {0.0};
        double s_new[M];
        char filename[64];
        snprintf(filename, sizeof(filename), "x_%.1f.dat", n);

        // Warunek początkowy: zaburzenie Gaussa
        for (int i = 0; i <= N; i++) {
            double x = i * DELTA;
            s[i] = exp(-(x - N*DELTA/2)*(x - N*DELTA/2) / (2*SIGMA*SIGMA));
            s[N+1+i] = 0.0; // prędkości początkowe
        }

        FILE *f = fopen(filename, "w");
        if (!f) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        for (int t_step = 0; t_step <= NT; t_step++) {
            double t = t_step * DT;
            for (int i = 0; i <= N; i++)
                fprintf(f, "%g\t%g\t%g\n", i*DELTA, t, s[i]);
            fprintf(f, "\n"); // separator do Gnuplota

            rk4_step(s, t, DT, s_new, alpha);
            for (int i = 0; i < M; i++) s[i] = s_new[i];
        }

        fclose(f);
        printf("Wygenerowano: %s\n", filename);
    }

    return 0;
}
