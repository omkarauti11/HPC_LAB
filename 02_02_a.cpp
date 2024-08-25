#include <iostream>
#include <omp.h>
#include <cmath>
#include <ctime>

double calculatePiSequential(int num_steps) {
    double step = 1.0 / num_steps;
    double pi = 0.0;
    for (int i = 0; i < num_steps; ++i) {
        double x = (i + 0.5) * step;
        pi += 4.0 / (1.0 + x * x);
    }
    return step * pi;
}

double calculatePiParallel(int num_steps) {
    double step = 1.0 / num_steps;
    double pi = 0.0;

    #pragma omp parallel
    {
        double local_pi = 0.0;
        #pragma omp for
        for (int i = 0; i < num_steps; ++i) {
            double x = (i + 0.5) * step;
            local_pi += 4.0 / (1.0 + x * x);
        }

        #pragma omp atomic
        pi += local_pi;
    }

    return step * pi;
}

int main() {
    int num_steps = 100000000; // Number of steps for Pi calculation

    // Sequential execution
    double start_time = clock();
    double pi_seq = calculatePiSequential(num_steps);
    double end_time = clock();
    std::cout << "Sequential calculated value of Pi: " << pi_seq << std::endl;
    std::cout << "Sequential Time taken for Pi calculation: " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << std::endl;

    // Parallel execution
    start_time = omp_get_wtime();
    double pi_par = calculatePiParallel(num_steps);
    end_time = omp_get_wtime();
    std::cout << "Parallel calculated value of Pi: " << pi_par << std::endl;
    std::cout << "Parallel Time taken for Pi calculation: " << (end_time - start_time) << " seconds" << std::endl;

    return 0;
}
