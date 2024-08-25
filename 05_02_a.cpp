#include <iostream>
#include <omp.h>

int main() {
    int sum = 0;

    #pragma omp parallel reduction(+:sum)
    {
        int tid = omp_get_thread_num();
        int square = tid * tid;
        sum += square;
        std::cout << "Thread ID " << tid << " square: " << square << std::endl;
    }

    std::cout << "Sum of squares: " << sum << std::endl;
    return 0;
}
