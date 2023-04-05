#define _CRT_SECURE_NO_WARNINGS
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

int main(int argc, char** argv) {
    int rank, size, i, n;
    double pi, dx, x, sum, local_sum;
    char filename[100];
    FILE* fp;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank);

    n = rand() % 991 + 10;

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    dx = 1.0 / n;
    x = dx * (rank * n + 0.5);

    local_sum = 0.0;
    for (i = 0; i < n; i++) {
        local_sum += f(x);
        x += dx;
    }
    local_sum *= dx;

    sprintf(filename, "local_sum_%d.txt", rank);
    fp = fopen(filename, "w");
    fprintf(fp, "%.16f\n", local_sum);
    fclose(fp);

    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        pi = sum;
        printf("pi = %.16f\n", pi);
    }

    MPI_Finalize();
}