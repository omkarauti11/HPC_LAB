#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_data = rank;
    int recv_data;
    int next = (rank + 1) % size;
    int prev = (rank - 1 + size) % size;

    // Exchange data with neighbors in a blocking fashion
    MPI_Send(&send_data, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    MPI_Recv(&recv_data, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    std::cout << "Process " << rank << " received data: " << recv_data << " from process " << prev << std::endl;

    MPI_Finalize();
    return 0;
}
