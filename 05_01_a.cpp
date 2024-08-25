#include <iostream>
#include <omp.h>

int main() {
    const char* family_members[] = {"Alice", "Bob", "Charlie", "Diana"};
    int num_threads = sizeof(family_members) / sizeof(family_members[0]);

    #pragma omp parallel num_threads(num_threads)
    {
        int tid = omp_get_thread_num();
        std::cout << "Thread ID " << tid << ": " << family_members[tid] << std::endl;
    }

    return 0;
}
