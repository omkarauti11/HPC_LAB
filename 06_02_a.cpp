#include <iostream>
#include <omp.h>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function for Matrix-Vector Multiplication (sequential)
void matrixVectorMultiplicationSeq(vector<vector<int>>& A, vector<int>& B, vector<int>& C, int N) {
    for (int i = 0; i < N; ++i) {
        C[i] = 0;
        for (int j = 0; j < N; ++j) {
            C[i] += A[i][j] * B[j];
        }
    }
}

// Function for Matrix-Vector Multiplication (parallel)
void matrixVectorMultiplicationParallel(vector<vector<int>>& A, vector<int>& B, vector<int>& C, int N) {
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        C[i] = 0;
        for (int j = 0; j < N; ++j) {
            C[i] += A[i][j] * B[j];
        }
    }
}

int main() {
    int N = 500;  // Size of the matrix and vector

    // Initialize matrix and vector
    vector<vector<int>> A(N, vector<int>(N, 1));
    vector<int> B(N, 1);
    vector<int> result(N, 0);

    // Matrix-Vector Multiplication - Sequential
    auto start = high_resolution_clock::now();
    matrixVectorMultiplicationSeq(A, B, result, N);
    auto end = high_resolution_clock::now();
    auto durationSeqMatVec = duration_cast<milliseconds>(end - start);
    cout << "Matrix-Vector Multiplication (Sequential) Time: " << durationSeqMatVec.count() << " ms" << endl;

    // Matrix-Vector Multiplication - Parallel
    start = high_resolution_clock::now();
    matrixVectorMultiplicationParallel(A, B, result, N);
    end = high_resolution_clock::now();
    auto durationParMatVec = duration_cast<milliseconds>(end - start);
    cout << "Matrix-Vector Multiplication (Parallel) Time: " << durationParMatVec.count() << " ms" << endl;

    return 0;
}
