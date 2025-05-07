#include <iostream>
#include <vector>
#include <chrono>
#include "vektorius.h"

void test_push_back_performance(size_t sz) {
    using namespace std::chrono;

    std::vector<int> v1;
    auto start1 = high_resolution_clock::now();
    for (int i = 1; i <= sz; ++i) v1.push_back(i);
    auto end1 = high_resolution_clock::now();

    Vector<int> v2;
    auto start2 = high_resolution_clock::now();
    for (int i = 1; i <= sz; ++i) v2.push_back(i);
    auto end2 = high_resolution_clock::now();

    auto std_time = duration_cast<duration<double>>(end1 - start1).count();  
    auto my_time = duration_cast<duration<double>>(end2 - start2).count(); 

    std::cout << "Elementų: " << sz << " | std::vector: " << std_time << " sek. | Vector: " << my_time << " sek.\n";
}

int main() {
    size_t sizes[] = {10000, 100000, 1000000, 10000000, 100000000};
    for (auto sz : sizes)
        test_push_back_performance(sz);
    return 0;
}
