#include <mpi.h>
#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int arraySize = 5;
    int array[arraySize] = { 0 };
    srand(rank + 1);
    for (int i = 0; i < arraySize; ++i) {
        array[i] = rand() % 100;
    }

    std::vector<int> recvbuf(size * arraySize);
    MPI_Gather(array, arraySize, MPI_INT, recvbuf.data(), arraySize, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::vector<int> sortedVec(size * arraySize);
        std::copy(recvbuf.begin(), recvbuf.end(), sortedVec.begin());
        std::sort(sortedVec.begin(), sortedVec.end());

        for (int i = 0; i < size; ++i) {
            std::cout << "rank " << i << ": ";
            for (int j = 0; j < arraySize; ++j) {
                std::cout << recvbuf[i * arraySize + j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "sorted: ";
        for (const auto& value : sortedVec) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
}
