#include <iostream>
#include <omp.h>

int main() {
    // Start time
    double start_time = omp_get_wtime();
    #pragma omp parallel num_threads(2)
    {
        int tid = omp_get_thread_num();
        if (tid == 0) {
            std::cout << "Thread ID " << tid << ": 2" << std::endl;
        } else if (tid == 1) {
            std::cout << "Thread ID " << tid << ": 4" << std::endl;
        }
    }

        // End time
    double end_time = omp_get_wtime();

    // Calculate total execution time
    double total_time = end_time - start_time;

    std::cout << "Total execution time: " << total_time << " seconds" << std::endl;

    return 0;
}
