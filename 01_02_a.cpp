#include <iostream>
#include <omp.h>
#include <chrono>

int main() {
    const int numIterations = 1000;

    // Sequential execution
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i) {
        // Print "Hello, World" for each iteration (can be commented out for performance measurement)
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> sequential_duration = end_time - start_time;
    std::cout << "Sequential Time taken: " << sequential_duration.count() << " milliseconds" << std::endl;

    // Parallel execution
    start_time = std::chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < numIterations; ++i) {
            // Print "Hello, World" for each iteration (can be commented out for performance measurement)
        }
    }

    end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> parallel_duration = end_time - start_time;
    std::cout << "Parallel Time taken: " << parallel_duration.count() << " milliseconds" << std::endl;

    return 0;
}
