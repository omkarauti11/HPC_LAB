#include <mpi.h>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
    
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Varying message size
    const int message_size = (world_rank + 1) * 1000;  // Message size varies with rank
    vector<int> message(message_size, world_rank);

    vector<int> result(message_size, 0);

    double start_time = MPI_Wtime();
    // Perform reduction: sum the values across all processes
    MPI_Reduce(message.data(), result.data(), message_size, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    double end_time = MPI_Wtime();

    if (world_rank == 0) {
        cout << "Reduction completed in " << end_time - start_time << " seconds with message size " << message_size << ".\n";
    }

    MPI_Finalize();
    return 0;
}
