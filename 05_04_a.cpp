#include <iostream>
#include <omp.h>

int main() {
    int total_sum = 0;
    const int N = 20;
    int partial_sum = 0;

    #pragma omp parallel private(partial_sum)
    {
        #pragma omp for
        for (int i = 1; i <= N; ++i) {
            partial_sum += i;
        }

        #pragma omp critical
        total_sum += partial_sum;
    }

    std::cout << "Total sum: " << total_sum << std::endl;
    return 0;
}
