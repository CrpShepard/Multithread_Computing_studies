#include <iostream>
#include <mpi.h>
#include <vector>
#include <ctime>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int k = size;  // количество процессов, которым нужно переслать данные
    std::vector<int> nums;  // вектор для хранения чисел в главном процессе

    if (rank == 0) {
        nums.resize(k + 2);
        std::srand(std::time(nullptr));
        for (int i = 0; i < k + 2; i++) {
            nums[i] = rand() % 91 + 10;
            std::cout << nums[i] << " ";
        }
        std::cout << '\n';
    }

    std::vector<int> sendcounts(size, 3);  // количество чисел для отправки
    std::vector<int> displs(size, 0);  // смещение для каждого процесса

    // заполняем sendcounts и displs для MPI_Scatterv
    for (int i = 0; i < k - 1; i++) {
        sendcounts[i + 1] = 3;
        displs[i + 1] = i + 1;
    }
    sendcounts[0] = 3;
    displs[0] = 0;
    sendcounts[size - 1] = 3;
    displs[size - 1] = k;

    std::vector<int> recvbuf(3);
    MPI_Scatterv(nums.data(), sendcounts.data(), displs.data(), MPI_INT, recvbuf.data(), 3, MPI_INT, 0, MPI_COMM_WORLD);

    std::cout << "rank  " << rank << ": ";
    for (auto num : recvbuf) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    MPI_Finalize();
    return 0;
}
