#include <iostream>
#include <cmath>
#include <chrono>

int main() {
    // Define the number of floating-point operations
    long long numOperations = 1e8; // 100 million operations

    // Sequential execution
    auto start = std::chrono::high_resolution_clock::now();

    double result = 0.0;
    for (long long i = 0; i < numOperations; ++i) {
        result += std::sin(i * 0.1); // Example floating-point operation
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    double sequential_time_ms = elapsed.count();
    double sequential_time_s = sequential_time_ms / 1000.0; // Convert milliseconds to seconds
    double sequential_flops = numOperations / sequential_time_s; // FLOPS = operations / time (in seconds)
    double sequential_gflops = sequential_flops / 1e9; // Convert to GFLOPS

    std::cout << "Sequential Execution:" << std::endl;
    std::cout << "Elapsed Time: " << sequential_time_ms << " milliseconds" << std::endl;
    std::cout << "Estimated FLOPS: " << sequential_flops << " FLOPS" << std::endl;
    std::cout << "Estimated GFLOPS: " << sequential_gflops << " GFLOPS" << std::endl;

    return 0;
}
