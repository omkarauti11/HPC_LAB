#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    const int message_size = 1000;  // Fixed size
    std::vector<int> message(message_size);

    if (world_rank == 0) {
        // Initialize message in root process
        for (int i = 0; i < message_size; i++) {
            message[i] = i;
        }
    }

    double start_time = MPI_Wtime();
    // Broadcast the message from root (process 0) to all other processes
    MPI_Bcast(message.data(), message_size, MPI_INT, 0, MPI_COMM_WORLD);
    double end_time = MPI_Wtime();

    if (world_rank == 0) {
        std::cout << "Broadcast completed in " << end_time - start_time << " seconds with " << world_size << " processes.\n";
    }

    MPI_Finalize();
    return 0;
}
