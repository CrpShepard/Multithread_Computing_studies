#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]) {
    int rank, size;
    double pi, sum, x, dx, local_sum = 0.0;
    int intervals = 100000;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    dx = 1.0 / intervals;

    for (int i = rank; i < intervals; i += size) {
        x = (i + 0.5) * dx;
        local_sum += 4.0 / (1.0 + x * x);
    }

    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        pi = sum * dx;
        cout << "„исло ѕи = " << pi << endl;
    }

    MPI_Finalize();
}
