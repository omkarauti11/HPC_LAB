#include <iostream>
#include <vector>
#include <omp.h>    // OpenMP header
#include <chrono>   // For measuring time

// Function to add two matrices
void add_matrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int num_threads) {
    int rows = A.size();
    int cols = A[0].size();

    #pragma omp parallel for num_threads(num_threads) collapse(2)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to initialize a matrix with random values
void initialize_matrix(std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 100;  // Random values between 0 and 99
        }
    }
}

// Function to measure time and perform matrix addition
void perform_test(int size, int num_threads) {
    std::vector<std::vector<int>> A(size, std::vector<int>(size));
    std::vector<std::vector<int>> B(size, std::vector<int>(size));
    std::vector<std::vector<int>> C(size, std::vector<int>(size, 0));

    initialize_matrix(A);
    initialize_matrix(B);

    auto start_time = std::chrono::high_resolution_clock::now();

    add_matrices(A, B, C, num_threads);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_ms = end_time - start_time;

    std::cout << "Matrix size: " << size << "x" << size << ", Threads: " << num_threads << ", Time: " << time_ms.count() << " milliseconds" << std::endl;
}

int main() {
    // Different matrix sizes to test
    std::vector<int> matrix_sizes = {250, 500};
    // Different numbers of threads to test
    std::vector<int> thread_counts = {1, 2, 4};

    for (int size : matrix_sizes) {
        for (int num_threads : thread_counts) {
            perform_test(size, num_threads);
        }
    }

    return 0;
}
