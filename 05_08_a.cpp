#include <iostream>
#include <vector>

int main() {
    int N = 1000000;
    std::vector<int> array(N, 1);
    int sum = 0;

    for (int i = 0; i < N; ++i) {
        sum += array[i];
    }

    std::cout << "Sequential sum: " << sum << std::endl;
    return 0;
}
