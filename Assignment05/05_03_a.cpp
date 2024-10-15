#include <iostream>
#include <omp.h>

int main() {
    int Aryabhatta = 10;
    // Start time
    double start_time = omp_get_wtime();
    #pragma omp parallel private(Aryabhatta)
    {
        int tid = omp_get_thread_num();
        int result = tid * Aryabhatta;
        std::cout << "Thread ID " << tid << " result: " << result << std::endl;
    }

        // End time
    double end_time = omp_get_wtime();

    // Calculate total execution time
    double total_time = end_time - start_time;

    std::cout << "Total execution time: " << total_time << " seconds" << std::endl;

    return 0;
}
