#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 50          // liczba atomów - 1 (mamy N+1 atomów)
#define M (2*(N+1))   // liczba zmiennych w układzie (pozycje i prędkości)
#define NSTEPS 5000   // liczba kroków czasowych
#define DT 0.02       // krok czasowy
#define DELTA 0.1     // odległość równowagowa
#define ALPHA 1.0     // stała sprężystości
#define MASS 1.0      // masa atomu
#define SIGMA (3*DELTA)

void pochodne(double t, double *s, double *dsdt) {
    // s[0..N]     - pozycje xi
    // s[N+1..2N+1] - prędkości v_i = x_i'
    // dsdt - pochodne s˙i, s˙N+1+i wg instrukcji

    int i;

    // pochodne pozycji to prędkości
    for(i = 0; i <= N; i++) {
        dsdt[i] = s[N+1 + i];  // s˙i = sN+1+i
    }

    // pochodne prędkości wg równania ruchu, wewnętrzne atomy i=1..N-1
    for(i = 1; i < N; i++) {
        dsdt[N+1 + i] = (ALPHA / MASS) * (s[i-1] - 2*s[i] + s[i+1]);
    }


    // warunki brzegowe - atomy na końcach nieruchome
    dsdt[0] = 0.0;
    dsdt[N] = 0.0;
    dsdt[N+1] = 0.0;
    dsdt[M-1] = 0.0;  // czyli dsdt[2N+1]
}

// RK4 dla wektora zmiennych (rozmiar n)
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
    for (i = 0; i < n; i++) s[i] += dt / 6 * (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
}

// Energia kinetyczna T = sum_i m/2 * v_i^2
double energia_kinetyczna(double *s) {
    double T = 0.0;
    int i;
    for(i = 0; i <= N; i++) {
        double vi = s[N+1 + i];
        T += 0.5 * MASS * vi * vi;
    }
    return T;
}

// Energia potencjalna U = sum_i alpha/2 * ( (x_{i-1} - x_i + DELTA)^2 )
double energia_potencjalna(double *s) {
    double U = 0.0;
    int i;
    for(i = 1; i <= N; i++) {
        double diff = (s[i-1] - s[i] + DELTA);
        U += 0.5 * ALPHA * diff * diff;
    }
    return U;
}

int main() {
    double s[M];   // wektor stanu: pozycje + prędkości
    double t = 0.0;
    int i, step;

    // Wyjściowy plik do zapisu wychyleń w funkcji czasu (do wykresów 2D)
    FILE *f = fopen("x_gauss.dat", "w");
    if (!f) {
        perror("Nie można otworzyć pliku");
        return 1;
    }
    FILE *f_e = fopen("energy_gauss.dat", "w");
    if (!f_e) {
        perror("Nie można otworzyć pliku");
        return 1;
    }

    // Warunki początkowe:
    // xi,0 = DELTA * i (położenia równowagi)
    // Wychylenie: ∆/3 * exp(-(xi,0 - xmax/2)^2/(2*SIGMA^2))
    double xmax = DELTA * N;
    for(i = 0; i <= N; i++) {
        double x0 = DELTA * i;
        double perturb = (DELTA/3.0) * exp(- ( (x0 - xmax/2.0)*(x0 - xmax/2.0) )/(2*SIGMA*SIGMA));
        s[i] = x0 + perturb;    // pozycje
        s[N+1 + i] = 0.0;       // prędkości zerowe
    }

    // Petla czasowa
    for(step = 0; step <= NSTEPS; step++) {
        // Zapis danych do pliku:
        // Format: t i (atom) wychylenie = s[i] - xi,0
        for(i = 0; i <= N; i++) {
            double x0 = DELTA * i;
            fprintf(f, "%g %d %g\n", t, i, s[i] - x0);
        }
        fprintf(f, "\n"); // oddzielenie ramek czasowych pustą linią

        // Można też zapisywać energie do osobnych plików lub ekran - tutaj np. do stdout co 100 kroków
    
        double T = energia_kinetyczna(s);
        double U = energia_potencjalna(s);
        double E = T + U;
        fprintf(f_e,"%.2f %.5f %.5f %.5f\n", t, T, U, E);


        // RK4 krok
        rk4_vec(t, DT, M, s, pochodne);
        t += DT;
    }

    fclose(f);
    fclose(f_e);

    // printf("Symulacja zakonczona. Dane zapisane w 'x_gauss.dat'\n");
    // printf("Mozna rysowac mapa wychyleń w funkcji czasu wg podanego wczesniej skryptu Gnuplota.\n");

    return 0;
}
