#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int token;
    if (rank != 0) {
        MPI_Recv(&token, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD,
            MPI_STATUS_IGNORE);
        printf("Process %d received token %d from process %d\n", rank, token,
            rank - 1);
        token++;
    }
    else {
        token = 0;
    }
    MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD); // if rank == 0 send to rank 1 � ��
                                                                        // ����� ������ �����

    if (rank == 0) {
        MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, // �������� � �����
            MPI_STATUS_IGNORE);
        printf("Process %d received token %d from process %d\n", rank, token,
            size - 1);
    }

    MPI_Finalize();
}
