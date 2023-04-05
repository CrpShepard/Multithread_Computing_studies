#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data = rank;

    MPI_Status status;
    
    if (rank == 0) {
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        cout << "Rank " << rank << " Send data " << data << " from rank " << size - 1 << endl;
        MPI_Recv(&data, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);
    }
    else {
        MPI_Recv(&data, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        cout << "Rank " << rank << " received data " << data << " from rank " << rank - 1 << endl;
        MPI_Send(&data, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
