#include <iostream>
#include <omp.h>
#include <queue>
#include <cstdlib>
#include <ctime>

const int NUM_PRODUCERS = 2;
const int NUM_CONSUMERS = 2;
const int NUM_ITEMS = 100;

std::queue<int> buffer;
omp_lock_t buffer_lock;
bool buffer_not_full = true;
bool buffer_not_empty = false;
int count = 0;

void producer(int id, int buffer_size) {
    for (int i = 0; i < NUM_ITEMS / NUM_PRODUCERS; ++i) {
        int item = rand() % 100;
        omp_set_lock(&buffer_lock);
        
        // Wait if buffer is full
        while (buffer.size() == buffer_size) {
            buffer_not_full = false;
            omp_unset_lock(&buffer_lock);
            while (!buffer_not_full) { /* Busy wait */ }
            omp_set_lock(&buffer_lock);
        }
        
        buffer.push(item);
        count++;
        // std::cout << "Producer " << id << " produced " << item << std::endl;
        buffer_not_empty = true;

        omp_unset_lock(&buffer_lock);
    }
}

void consumer(int id, int buffer_size) {
    for (int i = 0; i < NUM_ITEMS / NUM_CONSUMERS; ++i) {
        int item;
        omp_set_lock(&buffer_lock);
        
        // Wait if buffer is empty
        while (buffer.empty()) {
            buffer_not_empty = false;
            omp_unset_lock(&buffer_lock);
            while (!buffer_not_empty) { /* Busy wait */ }
            omp_set_lock(&buffer_lock);
        }
        
        item = buffer.front();
        buffer.pop();
        count--;
        // std::cout << "Consumer " << id << " consumed " << item << std::endl;
        buffer_not_full = true;

        omp_unset_lock(&buffer_lock);
    }
}

void run_test(int buffer_size) {
    buffer = std::queue<int>(); // Reset buffer
    count = 0; // Reset item count
    buffer_not_full = true;
    buffer_not_empty = false;

    omp_init_lock(&buffer_lock);
    
    double start_time = omp_get_wtime();
    
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                for (int i = 0; i < NUM_PRODUCERS; ++i) {
                    #pragma omp parallel
                    producer(i, buffer_size);
                }
            }
            
            #pragma omp section
            {
                for (int i = 0; i < NUM_CONSUMERS; ++i) {
                    #pragma omp parallel
                    consumer(i, buffer_size);
                }
            }
        }
    }
    
    double end_time = omp_get_wtime();
    
    omp_destroy_lock(&buffer_lock);
    
    std::cout << "Buffer Size: " << buffer_size << std::endl;
    std::cout << "Time taken: " << (end_time - start_time) << " seconds" << std::endl;
}

int main() {
    srand(time(0));
    
    // Test different buffer sizes
    int buffer_sizes[] = {5, 10, 20, 50, 100};
    int num_tests = sizeof(buffer_sizes) / sizeof(buffer_sizes[0]);
    
    for (int i = 0; i < num_tests; ++i) {
        int buffer_size = buffer_sizes[i];
        run_test(buffer_size);
    }
    
    return 0;
}
