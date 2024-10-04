#include <mpi.h>
#include <iostream>

int main(int argc, char *argv[]) {
    int rank, size;
    
    // Initialize MPI environment
    MPI_Init(&argc, &argv);
    
    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Check if the number of processes is 5
    if (size != 5) {
        if (rank == 0) {
            std::cerr << "This program requires exactly 5 processes.\n";
        }
        MPI_Finalize();
        return 1;
    }

    // Display rank and communicator group information
    std::cout << "Process rank: " << rank << ", Communicator size: " << size << std::endl;
    
    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}
