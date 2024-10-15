#include <iostream>
#include <omp.h>

int main() {
    int sum = 0;
    // Start time
    double start_time = omp_get_wtime();
    
    #pragma omp parallel reduction(+:sum)
    {
        int tid = omp_get_thread_num();
        int square = tid * tid;
        sum += square;
        std::cout << "Thread ID " << tid << " square: " << square << std::endl;
    }

    std::cout << "Sum of squares: " << sum << std::endl;

        // End time
    double end_time = omp_get_wtime();

    // Calculate total execution time
    double total_time = end_time - start_time;

    std::cout << "Total execution time: " << total_time << " seconds" << std::endl;

    return 0;
}
