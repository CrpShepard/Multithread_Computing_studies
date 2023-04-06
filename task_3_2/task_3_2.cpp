#include <iostream>
#include <mpi.h>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    const int n = 4;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    vector<int> data(rank + 2, rank);
    int counts[n], displs[n];
    int total_count = 0;
    for (int i = 0; i < size; i++) {
        counts[i] = i + 2;
        displs[i] = total_count;
        total_count += counts[i];
    }
    vector<int> recvbuf(total_count);

    MPI_Gatherv(data.data(), rank + 2, MPI_INT,
        recvbuf.data(), counts, displs, MPI_INT,
        0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "полученные числа: ";
        for (int i = 0; i < total_count; i++) {
            cout << recvbuf[i] << " ";
        }
        cout << std::endl;
    }

    MPI_Finalize();
}
