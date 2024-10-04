#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        std::cerr << "This program requires exactly 2 processes.\n";
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int send_data = rank;
    int recv_data;

    if (rank == 0) {
        // Process 0 sends to Process 1 and waits for Process 1 to send
        MPI_Send(&send_data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv_data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else if (rank == 1) {
        // Process 1 sends to Process 0 and waits for Process 0 to send
        MPI_Send(&send_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    std::cout << "Process " << rank << " received data: " << recv_data << std::endl;

    MPI_Finalize();
    return 0;
}
