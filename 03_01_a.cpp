#include <iostream>
#include <vector>
#include <algorithm> // for sort
#include <omp.h>     // OpenMP header

int main() {
    // Example vectors
    std::vector<int> a = {1, 3, 5, 2, 4};
    std::vector<int> b = {7, 9, 2, 6, 8};

    // Sort vector a in ascending order
    std::sort(a.begin(), a.end());
    // Sort vector b in descending order
    std::sort(b.begin(), b.end(), std::greater<int>());

    // Initialize the minimum scalar product for sequential and parallel runs
    int min_scalar_product_seq = 0;
    int min_scalar_product_par = 0;

    // Measure time for the sequential computation
    double start_time_seq = omp_get_wtime();

    for (int i = 0; i < a.size(); ++i) {
        min_scalar_product_seq += a[i] * b[i];
    }

    double end_time_seq = omp_get_wtime();
    double time_seq_ms = (end_time_seq - start_time_seq) * 1000; // Convert to milliseconds

    std::cout << "Minimum Scalar Product (Sequential): " << min_scalar_product_seq << std::endl;
    std::cout << "Time taken (Sequential): " << time_seq_ms << " milliseconds" << std::endl;

    // Measure time for the parallel computation
    double start_time_par = omp_get_wtime();

    #pragma omp parallel for reduction(+:min_scalar_product_par)
    for (int i = 0; i < a.size(); ++i) {
        int thread_id = omp_get_thread_num(); // Get the ID of the current thread
        min_scalar_product_par += a[i] * b[i];
        std::cout << "Thread " << thread_id << " processed element " << i << ": a[" << i << "] * b[" << i << "] = " 
                  << a[i] << " * " << b[i] << " = " << a[i] * b[i] << std::endl;
    }

    double end_time_par = omp_get_wtime();
    double time_par_ms = (end_time_par - start_time_par) * 1000; // Convert to milliseconds

    std::cout << "Minimum Scalar Product (Parallel): " << min_scalar_product_par << std::endl;
    std::cout << "Time taken (Parallel): " << time_par_ms << " milliseconds" << std::endl;

    return 0;
}
