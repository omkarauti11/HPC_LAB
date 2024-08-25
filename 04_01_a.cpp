#include <iostream>
#include <omp.h>

// Function to compute Fibonacci number using recursion
int fibonacci(int n) {
    if (n <= 1)
        return n;
    
    int x, y;
    
    // Parallelize the recursive calls
    #pragma omp parallel sections
    {
        #pragma omp section
        x = fibonacci(n - 1);
        
        #pragma omp section
        y = fibonacci(n - 2);
    }

    return x + y;
}

int main() {
    int n = 10;// Example input
    
    // Set the number of threads
    omp_set_num_threads(2);
    
    double start_time = omp_get_wtime(); // Start time measurement
    int result = fibonacci(n);
    double end_time = omp_get_wtime(); // End time measurement
    
    std::cout << "Fibonacci of " << n << " is " << result << std::endl;
    std::cout << "Time taken: " << (end_time - start_time) << " seconds" << std::endl;

    return 0;
}
