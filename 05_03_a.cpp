#include <iostream>
#include <omp.h>

int main() {
    int Aryabhatta = 10;

    #pragma omp parallel private(Aryabhatta)
    {
        int tid = omp_get_thread_num();
        int result = tid * Aryabhatta;
        std::cout << "Thread ID " << tid << " result: " << result << std::endl;
    }

    return 0;
}
