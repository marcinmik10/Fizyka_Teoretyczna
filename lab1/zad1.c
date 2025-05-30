#include <stdio.h>
#include <stdlib.h>
#include <math.h>

# define g 9.81
# define R 1.0
# define m 1.0
# define M 1000
void pochodne(double t, double *s, double *k) {
    k[0] = s[1];
    k[1] = -g / R * sin(s[0]);
}
void rk4_vec(double t, double dt, int n, double *s, void (*f)(double, double *, double *)) {
    static double k1[M], k2[M], k3[M], k4[M], w[M];
    int i;

    for (i = 0; i < n; i++) w[i] = s[i];
    f(t, w, k1);

    for (i = 0; i < n; i++) w[i] = s[i] + dt / 2 * k1[i];
    f(t + dt / 2, w, k2);

    for (i = 0; i < n; i++) w[i] = s[i] + dt / 2 * k2[i];
    f(t + dt / 2, w, k3);

    for (i = 0; i < n; i++) w[i] = s[i] + dt * k3[i];
    f(t + dt, w, k4);

    for (i = 0; i < n; i++) s[i] = s[i] + dt / 6 * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
}
double kinetic_energy(double w) {
    return 0.5 * R * R * m * w * w;
}
double potential_energy(double phi) {
    return -m * g * R * cos(phi);
}

#define PI 3.141592653589793

void compare_with_analytic(double phi0_deg, double dt, int N) {
    double *phi_num = (double *)malloc((N + 1) * sizeof(double));
    double *phi_analytic = (double *)malloc((N + 1) * sizeof(double));
    double *t_array = (double *)malloc((N + 1) * sizeof(double));
    double *s = (double *)malloc(2 * sizeof(double));
    
    double phi0_rad = phi0_deg * PI / 180.0;
    double omega = sqrt(g / R);
    double t = 0.0;

    // Warunki początkowe
    s[0] = phi0_rad;
    s[1] = 0.0;

    FILE *fp = fopen("compare.dat", "w");
    if (!fp) {
        perror("Nie można otworzyć pliku compare.dat");
        free(phi_num);
        free(phi_analytic);
        free(t_array);
        free(s);
        return;
    }

    // Początkowe wartości
    phi_num[0] = s[0];
    phi_analytic[0] = phi0_rad * cos(omega * t);
    t_array[0] = t;
    fprintf(fp, "%lf\t%lf\t%lf\n", t, phi_num[0], phi_analytic[0]);

    // Symulacja numeryczna i analityczna
    for (int i = 1; i <= N; i++) {
        rk4_vec(t, dt, 2, s, pochodne);
        t += dt;

        phi_num[i] = s[0];
        phi_analytic[i] = phi0_rad * cos(omega * t);
        t_array[i] = t;

        fprintf(fp, "%lf\t%lf\t%lf\n", t, phi_num[i], phi_analytic[i]);
    }

    fclose(fp);
    free(phi_num);
    free(phi_analytic);
    free(t_array);
    free(s);
}

int main (){
    double t , dt , tmax , * s ;
    int i , n , N ;
    FILE *fp;
    // inicjalizacja parametrów :
    n =2; // ilość zmiennych w układzie RRZ1
    dt =0.01;
    N=1000;
    tmax =N*dt;
    // N =( int ) tmax / dt ; // ilość kroków czasowych
    t =0.0;

    void (* f )( double , double * , double *); // wskaźnik do funkcji 
    f = pochodne ; // przypisujemy wskaźnik do funkcji

    s =( double *) malloc( n*sizeof(double)); // tablica rozwiązań
    // warunki początkowe :
    // s[0] = M_PI*4/180; //1
    // s[0] = M_PI/4; //2
    // s[0] = M_PI/2; //3
    // s[0] = M_PI*135/180; //4
    s[0] = M_PI*175/180; //5

    s[1] = 0.0;       
    // Otwórz plik do zapisu
    fp = fopen("wp.dat", "w");
    if (fp == NULL) {
        perror("Nie można otworzyć pliku");
        return 1;
    }
    // Zapis stanu początkowego
    double T= kinetic_energy(s[1]);
    double V= potential_energy(s[0]);
    double E=T+V;
    fprintf(fp, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", t, s[0], s[1], T, V, E);

    // symulacja w czasie :
    for (i = 1; i <= N; i++) {
        rk4_vec(t, dt, n, s, pochodne);
        t += dt;
        T= kinetic_energy(s[1]);
        V= potential_energy(s[0]);
        E=T+V;
        fprintf(fp, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", t, s[0], s[1], T, V, E);
    }
    
    fclose(fp);
    free(s);
///////////////////////////////////
// tmax = 100.0; // zamiast 20.0

double *ss;

ss = (double *)malloc(n * sizeof(double));

    double prev_phi, phi0;
    FILE *f2 = fopen("periods.dat", "w");

    if (f2 == NULL) {
        perror("Nie można otworzyć pliku do zapisu");
        return 1;
    }

    for (phi0 = M_PI * 5 / 180; phi0 <= M_PI * 175 / 180; phi0 += M_PI * 5 / 180) {
        ss[0] = phi0;  // maksymalne wychylenie (amplituda)
        ss[1] = 0.0;   // prędkość początkowa

        t = 0.0;
        int crossings = 0;
        double t_period_start = -1.0, t_period = -1.0;
        prev_phi = ss[0];

        for (i = 0; i < N; i++) {
            rk4_vec(t, dt, n, ss, pochodne);
            t += dt;

            // Szukamy przejścia przez phi = phi0 z tą samą prędkością (czyli pełny okres)
            if (prev_phi < 0 && s[0] >= 0 && s[1] > 0){
            if (t_period_start < 0) {
                    t_period_start = t;
                } else {
                    t_period = t - t_period_start;
                    break;
                }
            }
            prev_phi = ss[0];
        }

        if (t_period > 0)
            fprintf(f2, "%lf\t%lf\n", phi0, t_period);
    }

    fclose(f2);
    free(ss);

    compare_with_analytic(40.0, dt, N); // φ0 = 40°, krok czasowy i liczba kroków jak w głównej symulacji


    return 0;
}