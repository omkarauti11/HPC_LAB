#include <mpi.h>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 4;  // Matrix size (nxn) and Vector size
    vector<int> matrix, vector(n), local_result(n / size);
    vector<int> result(n);

    if (rank == 0) {
        matrix = {
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
        };

        vector = {1, 1, 1, 1};  // Vector to multiply
    }

    // Broadcast the vector to all processes
    MPI_Bcast(vector.data(), n, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter matrix rows among processes
    vector<int> local_matrix(n * (n / size));
    MPI_Scatter(matrix.data(), n * (n / size), MPI_INT, local_matrix.data(), n * (n / size), MPI_INT, 0, MPI_COMM_WORLD);

    // Local matrix-vector multiplication
    for (int i = 0; i < n / size; ++i) {
        local_result[i] = 0;
        for (int j = 0; j < n; ++j) {
            local_result[i] += local_matrix[i * n + j] * vector[j];
        }
    }

    // Gather the results
    MPI_Gather(local_result.data(), n / size, MPI_INT, result.data(), n / size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Resultant vector:" << endl;
        for (int i = 0; i < n; ++i) {
            cout << result[i] << " ";
        }
        cout << endl;
    }

    MPI_Finalize();
    return 0;
}
