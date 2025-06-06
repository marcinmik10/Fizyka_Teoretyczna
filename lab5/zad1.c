#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 30        // liczba punktów w kierunku ρ
#define M 150       // liczba punktów w kierunku z
#define J1 60       // granica lewego cylindra
#define J2 90       // granica prawego cylindra
#define ITMAX 5000  // liczba iteracji
#define V0 10.0     // potencjał na elektrodach
#define D_RHO 0.1
#define D_Z 0.1

double V[N + 1][M + 1]; // siatka potencjałów

void initialize_grid() {
    // Inicjalizacja wszystkich wartości potencjału do zera
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            V[i][j] = 0.0;
        }
    }
}

void apply_boundary_conditions() {
    // Obszar 1
    for (int j = 0; j <= J1; j++) {
        V[N][j] = V0;
    }

    // Obszar 2
    for (int j = J1 + 1; j <= J2; j++) {
        V[N][j] = 0.0;
    }

    // Obszar 3
    for (int j = J2 + 1; j <= M; j++) {
        V[N][j] = V0;
    }

    // Obszar 4
    for (int i = 1; i < N-1; i++) {
        V[i][M] = V[i][M - 1];
    }

    // Obszar 5
    for (int i = 1; i < N; i++) {
        V[i][0] = V[i][1];
    }

    // Obszar 6
    for (int j = 1; j < M; j++) {
        V[0][j] = V[1][j];
    }
}

void relax() {
    for (int iter = 0; iter < ITMAX; iter++) {
        for (int j = 1; j < M; j++) {//j=1
            for (int i = 1; i < N; i++) {//i=1
                double rhoi = i * D_RHO;

                double term_rho2 = (V[i + 1][j] + V[i - 1][j]) / (D_RHO * D_RHO);
                double term_rho = (V[i + 1][j] - V[i - 1][j]) / (2.0 * D_RHO * rhoi);
                double term_z2 = (V[i][j + 1] + V[i][j - 1]) / (D_Z * D_Z);

                V[i][j] = (term_rho2 + term_rho + term_z2) /(2.0 / (D_RHO * D_RHO) + 2.0 / (D_Z * D_Z));
                // apply_boundary_conditions(); // Odśwież warunki brzegowe po każdej iteracji

            }
        }
        // apply_boundary_conditions(); // Odśwież warunki brzegowe po każdej iteracji
    }
}

void save_to_file(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Błąd otwarcia pliku");
        exit(1);
    }

    for (int j = 0; j <= M; j++) {
        for (int i = 0; i <= N; i++) {
            fprintf(fp, "%lf %lf %lf\n", i * D_RHO, j * D_Z, V[i][j]);
        }
        fprintf(fp, "\n"); // pusta linia do oddzielenia warstw
    }

    fclose(fp);
}

void zapisz_przekroje() {
    FILE *f_rho0 = fopen("V_rho0.dat", "w");
    FILE *f_zp = fopen("V_zp.dat", "w");
    if (!f_rho0 || !f_zp) {
        printf("Blad otwarcia pliku do zapisu!\n");
        return;
    }
    double drho = D_RHO; // krok w kierunku ρ
    double dz = D_Z; // krok w kierunku z
    int n=N;
    int m=M;
    int j1 = J1; // granica lewego cylindra
    int j2 = J2; // granica prawego cylindra

    // 1) Zapis przekroju dla rho=0 (i=0) -> wszystkie j od 0 do m
    for (int j = 0; j <= m; j++) {
        double z = j * dz;
        double V_val = V[0][j];  // rho=0, index i=0
        fprintf(f_rho0, "%g %g %g\n", 0.0, z, V_val);
    }

    // 2) Zapis przekroju dla z = zp = ((j1+j2)/2)*dz = 7.5
    // Znajdujemy indeks j_p najbliższy 7.5
    double zp = ((j1 + j2) / 2.0) * dz;

    int j_p = (int) round(zp / dz);
    if (j_p > m) j_p = m;  // na wszelki wypadek

    for (int i = 0; i <= n; i++) {
        double rho = i * drho;
        double V_val = V[i][j_p];
        fprintf(f_zp, "%g %g %g\n", rho, zp, V_val);
    }

    fclose(f_rho0);
    fclose(f_zp);

    printf("Pliki V_rho0.dat i V_zp.dat zostaly zapisane.\n");
}


int main() {
    initialize_grid();
    apply_boundary_conditions();
    relax();
    save_to_file("potential.dat");
    zapisz_przekroje();
    printf("Symulacja zakończona. Wyniki zapisano w pliku potential.dat\n");
    return 0;
}
