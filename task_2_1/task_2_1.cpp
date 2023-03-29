#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char** args) {
	int rank, size;
	int a = 0;

	MPI_Status status;
	MPI_Init(&argc, &args);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		a = 10;
		MPI_Send(&a, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else {
		cout << rank << " " << a << '\n';
		MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, & status);
		cout << rank << " " << a << '\n';
	}

	MPI_Finalize();
}