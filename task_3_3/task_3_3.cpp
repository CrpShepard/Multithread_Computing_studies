#include <iostream>
#include <mpi.h>
#include <vector>
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv) {
    int rank, size;
    //const int K = 4;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int K = size;
    const int NUM_PER_PROCESS = 3;
    std::vector<int> data(K * NUM_PER_PROCESS);
    std::vector<int> recv_data(NUM_PER_PROCESS);

    if (rank == 0) {
        // Generate random data
        std::srand(std::time(nullptr));
        std::cout << "Original data: ";
        for (int i = 0; i < K * NUM_PER_PROCESS; i++) {
            data[i] = std::rand() % 100;
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // Scatter data
    MPI_Scatter(data.data(), NUM_PER_PROCESS, MPI_INT,
        recv_data.data(), NUM_PER_PROCESS, MPI_INT,
        0, MPI_COMM_WORLD);

    // Print received data
    std::cout << "Process " << rank << " received: ";
    for (int i = 0; i < NUM_PER_PROCESS; i++) {
        std::cout << recv_data[i] << " ";
    }
    std::cout << std::endl;

    MPI_Finalize();
    return 0;
}
