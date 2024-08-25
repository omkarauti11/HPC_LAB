#include <iostream>
#include <vector>
#include <omp.h>

void matrix_multiply_static(const std::vector<std::vector<int>>& A,
                            const std::vector<std::vector<int>>& B,
                            std::vector<std::vector<int>>& C) {
    int n = A.size();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_multiply_dynamic(const std::vector<std::vector<int>>& A,
                             const std::vector<std::vector<int>>& B,
                             std::vector<std::vector<int>>& C) {
    int n = A.size();
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int n = 100; // Adjust size as needed
    std::vector<std::vector<int>> A(n, std::vector<int>(n, 1));
    std::vector<std::vector<int>> B(n, std::vector<int>(n, 1));
    std::vector<std::vector<int>> C(n, std::vector<int>(n));

    double start_time = omp_get_wtime();
    matrix_multiply_static(A, B, C);
    double end_time = omp_get_wtime();
    std::cout << "Static scheduling time: " << (end_time - start_time) << " seconds" << std::endl;

    start_time = omp_get_wtime();
    matrix_multiply_dynamic(A, B, C);
    end_time = omp_get_wtime();
    std::cout << "Dynamic scheduling time: " << (end_time - start_time) << " seconds" << std::endl;

    return 0;
}
