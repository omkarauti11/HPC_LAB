#include <iostream>
#include <omp.h>
#include <vector>
#include <cstdlib>
#include <ctime>

void vectorScalarAdditionSequential(const std::vector<double>& vec, double scalar, std::vector<double>& result) {
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = vec[i] + scalar;
    }
}

void vectorScalarAdditionParallel(const std::vector<double>& vec, double scalar, std::vector<double>& result) {
    #pragma omp parallel for
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = vec[i] + scalar;
    }
}

int main() {
    size_t n = 1000000; // Size of vector
    std::vector<double> vec(n, 1.0); // Vector with all elements initialized to 1.0
    double scalar = 2.0;
    std::vector<double> result(n);

    // Sequential execution
    double start_time = clock();
    vectorScalarAdditionSequential(vec, scalar, result);
    double end_time = clock();
    std::cout << "Sequential Time taken for vector scalar addition: " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << std::endl;

    // Parallel execution
    start_time = omp_get_wtime();
    vectorScalarAdditionParallel(vec, scalar, result);
    end_time = omp_get_wtime();
    std::cout << "Parallel Time taken for vector scalar addition: " << (end_time - start_time) << " seconds" << std::endl;

    return 0;
}
