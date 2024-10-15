#include <iostream>
#include <vector>

int main() {
    int N = 1000000;
    std::vector<int> array(N, 1);
    int sum = 0;
    
    // Start time
    double start_time = omp_get_wtime();

    for (int i = 0; i < N; ++i) {
        sum += array[i];
    }

    std::cout << "Sequential sum: " << sum << std::endl;

    // End time
    double end_time = omp_get_wtime();

    // Calculate total execution time
    double total_time = end_time - start_time;

    std::cout << "Total execution time: " << total_time << " seconds" << std::endl;

    return 0;
}
