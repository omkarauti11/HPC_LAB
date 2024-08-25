#include <iostream>
#include <vector>
#include <omp.h>    // OpenMP header
#include <chrono>   // For measuring time

// Function to perform scalar addition of a 1D vector
void scalar_addition(std::vector<int>& vec, int scalar, int num_threads, const std::string& schedule_type, int chunk_size) {
    int size = vec.size();

    // Parallel region with specified schedule type and chunk size
    if (schedule_type == "static") {
        #pragma omp parallel for num_threads(num_threads) schedule(static, chunk_size)
        for (int i = 0; i < size; ++i) {
            vec[i] += scalar;
        }
    } else if (schedule_type == "dynamic") {
        #pragma omp parallel for num_threads(num_threads) schedule(dynamic, chunk_size)
        for (int i = 0; i < size; ++i) {
            vec[i] += scalar;
        }
    }
}

// Function to measure time and perform scalar addition
void perform_test(int size, int num_threads, const std::string& schedule_type, int chunk_size) {
    std::vector<int> vec(size, 0);
    int scalar = 5;

    // Measure the start time
    auto start_time = std::chrono::high_resolution_clock::now();

    // Perform scalar addition
    scalar_addition(vec, scalar, num_threads, schedule_type, chunk_size);

    // Measure the end time
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_ms = end_time - start_time;

    // Print the results
    std::cout << "Vector size: " << size << ", Threads: " << num_threads 
              << ", Schedule: " << schedule_type << ", Chunk size: " << chunk_size 
              << ", Time: " << time_ms.count() << " milliseconds" << std::endl;
}

int main() {
    // Vector size
    int size = 200;
    // Different numbers of threads to test
    std::vector<int> thread_counts = {1, 2, 4, 8};
    // Chunk sizes for testing
    std::vector<int> chunk_sizes = {1, 10, 50};

    // Perform tests with static scheduling
    for (int num_threads : thread_counts) {
        for (int chunk_size : chunk_sizes) {
            perform_test(size, num_threads, "static", chunk_size);
        }
    }

    // Perform tests with dynamic scheduling
    for (int num_threads : thread_counts) {
        for (int chunk_size : chunk_sizes) {
            perform_test(size, num_threads, "dynamic", chunk_size);
        }
    }

    return 0;
}
