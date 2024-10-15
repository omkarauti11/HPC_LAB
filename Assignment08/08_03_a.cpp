#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int n = 10;
    int A[n];
    int local_sum = 0;

    // Initialize the array in process 0
    if (rank == 0) {
        for (int i = 0; i < n; ++i) {
            A[i] = i + 1;  // Example: A = {1, 2, 3, ..., 10}
        }
    }

    // Broadcast the array to both processes
    MPI_Bcast(A, n, MPI_INT, 0, MPI_COMM_WORLD);

    // Divide the work between the two processes
    int start = (rank == 0) ? 0 : n / 2;
    int end = (rank == 0) ? n / 2 : n;

    // Each process calculates its local sum
    for (int i = start; i < end; ++i) {
        local_sum += A[i];
    }

    cout << "Process " << rank << " local sum: " << local_sum << endl;

    // Reduce the local sums to get the global sum
    int global_sum = 0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Global sum: " << global_sum << endl;
    }

    MPI_Finalize();
    return 0;
}
