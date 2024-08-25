#include <iostream>
#include <omp.h>

int main() {
    #pragma omp parallel num_threads(2)
    {
        int tid = omp_get_thread_num();
        if (tid == 0) {
            std::cout << "Thread ID " << tid << ": 2" << std::endl;
        } else if (tid == 1) {
            std::cout << "Thread ID " << tid << ": 4" << std::endl;
        }
    }
    return 0;
}
