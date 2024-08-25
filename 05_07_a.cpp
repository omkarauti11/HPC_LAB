#include <iostream>
#include <omp.h>

int main() {
    const int N = 1000;
    int array[N];
    int total_sum = 0;

    for (int i = 0; i < N; ++i) {
        array[i] = 1;
    }

    #pragma omp parallel
    {
        int local_sum = 0;
        #pragma omp for
        for (int i = 0; i < N; ++i) {
            local_sum += array[i];
        }

        #pragma omp critical
        total_sum += local_sum;
    }

    std::cout << "Total sum: " << total_sum << std::endl;
    return 0;
}
