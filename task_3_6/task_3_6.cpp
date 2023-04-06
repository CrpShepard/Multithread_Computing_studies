#include <iostream>
#include <cstdlib>
#include <mpi.h>

using namespace std;

void my_avg(const void* in, void* inout, int* len, MPI_Datatype* datatype) {
    double* x = (double*)in;
    double* y = (double*)inout;
    int n = *len;

    for (int i = 0; i < n; i++) {
        y[i] = (x[i] + y[i]) / 2.0;
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 5;
    double data[N];
    for (int i = 0; i < N; i++) {
        data[i] = rank + i * 0.1;
    }

    double result[N];
    MPI_Op my_op;
    MPI_Op_create((MPI_User_function*)my_avg, true, &my_op);

    MPI_Reduce(&data, &result, N, MPI_DOUBLE, my_op, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Result: ";
        for (int i = 0; i < N; i++) {
            cout << result[i] << " ";
        }
        cout << endl;
    }

    MPI_Op_free(&my_op);
    MPI_Finalize();
    return 0;
}
