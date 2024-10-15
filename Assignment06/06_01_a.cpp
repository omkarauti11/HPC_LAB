#include <iostream>
#include <omp.h>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function for Matrix-Matrix Multiplication (sequential)
void matrixMatrixMultiplicationSeq(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function for Matrix-Matrix Multiplication (parallel)
void matrixMatrixMultiplicationParallel(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int N) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int N = 100;  // Size of the matrix

    // Initialize matrices
    vector<vector<int>> A(N, vector<int>(N, 1));
    vector<vector<int>> B(N, vector<int>(N, 1));
    vector<vector<int>> C(N, vector<int>(N, 0));

    // Matrix-Matrix Multiplication - Sequential
    auto start = high_resolution_clock::now();
    matrixMatrixMultiplicationSeq(A, B, C, N);
    auto end = high_resolution_clock::now();
    auto durationSeqMatMat = duration_cast<milliseconds>(end - start);
    cout << "Matrix-Matrix Multiplication (Sequential) Time: " << durationSeqMatMat.count() << " ms" << endl;

    // Matrix-Matrix Multiplication - Parallel
    start = high_resolution_clock::now();
    matrixMatrixMultiplicationParallel(A, B, C, N);
    end = high_resolution_clock::now();
    auto durationParMatMat = duration_cast<milliseconds>(end - start);
    cout << "Matrix-Matrix Multiplication (Parallel) Time: " << durationParMatMat.count() << " ms" << endl;

    return 0;
}
