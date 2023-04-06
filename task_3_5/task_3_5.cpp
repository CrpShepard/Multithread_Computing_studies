#include <iostream>
#include <mpi.h>
#include <vector>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int r = rank;
    std::vector<int> local_data(r + 2);
    for (int i = 0; i < r + 2; i++) {
        local_data[i] = r * 100 + i;
    }

    std::vector<int> recvcounts(size);
    std::vector<int> displs(size);
    for (int i = 0; i < size; i++) {
        recvcounts[i] = i + 2;
        displs[i] = i * (i + 1) / 2;
    }

    int total_size = displs[size - 1] + size + 2;
    std::vector<int> global_data(total_size);

    MPI_Allgatherv(local_data.data(), r + 2, MPI_INT, global_data.data(), recvcounts.data(), displs.data(), MPI_INT, MPI_COMM_WORLD);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i + 2; j++) {
            std::cout << global_data[displs[i] + j] << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
