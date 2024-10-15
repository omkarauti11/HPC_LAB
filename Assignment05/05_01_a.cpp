#include <iostream>
#include <omp.h>

int main() {
    const char* family_members[] = {"Alice", "Bob", "Charlie", "Diana"};
    int num_threads = sizeof(family_members) / sizeof(family_members[0]);

    // Start time
    double start_time = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads)
    {
        int tid = omp_get_thread_num();
        std::cout << "Thread ID " << tid << ": " << family_members[tid] << std::endl;
    }

    // End time
    double end_time = omp_get_wtime();

    // Calculate total execution time
    double total_time = end_time - start_time;

    std::cout << "Total execution time: " << total_time << " seconds" << std::endl;

    return 0;
}
