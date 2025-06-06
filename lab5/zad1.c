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
    for (int i = 1; i < N; i++) {
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
        for (int j = 1; j < M; j++) {
            for (int i = 1; i < N; i++) {
                double rhoi = i * D_RHO;

                double term_rho2 = (V[i + 1][j] + V[i - 1][j]) / (D_RHO * D_RHO);
                double term_rho = (V[i + 1][j] - V[i - 1][j]) / (2.0 * D_RHO * rhoi);
                double term_z2 = (V[i][j + 1] + V[i][j - 1]) / (D_Z * D_Z);

                V[i][j] = (term_rho2 + term_rho + term_z2) /
                          (2.0 / (D_RHO * D_RHO) + 2.0 / (D_Z * D_Z));
            }
        }

        apply_boundary_conditions(); // Odśwież warunki brzegowe po każdej iteracji
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

void zapiszPrzekroje(double** V, int n, int m, int j1, int j2, double delta) {
    // Otwieramy plik dla przekroju V(0,z) (osi symetrii)
    std::ofstream file_rho0("V_rho0.dat");
    file_rho0 << std::fixed << std::setprecision(6);
    int i_rho0 = 0; // i=0 - oś symetrii

    for (int j = 0; j <= m; ++j) {
        double rho = i_rho0 * delta;
        double z = j * delta;
        double val = V[i_rho0][j];
        file_rho0 << rho << " " << z << " " << val << "\n";
    }
    file_rho0.close();

    // Otwieramy plik dla przekroju V(rho, zp), gdzie zp = ((j1+j2)/2)*delta
    std::ofstream file_zp("V_zp.dat");
    file_zp << std::fixed << std::setprecision(6);

    int j_zp = (j1 + j2) / 2;  // indeks w osi z odpowiadający zp
    double zp = j_zp * delta;

    for (int i = 0; i <= n; ++i) {
        double rho = i * delta;
        double val = V[i][j_zp];
        file_zp << rho << " " << zp << " " << val << "\n";
    }
    file_zp.close();
}

int main() {
    initialize_grid();
    apply_boundary_conditions();
    relax();
    save_to_file("potential.dat");

    printf("Symulacja zakończona. Wyniki zapisano w pliku potential.dat\n");
    return 0;
}
