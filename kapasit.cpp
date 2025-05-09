#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>  // dėl setprecision
#include "vektorius.h"  // Tavo sukurta Vector klasė

const int N = 100000000;

void testStdVector() {
    std::vector<int> vec;
    int reallocCount = 0;

    for (int i = 0; i < N; ++i) {
        if (vec.size() == vec.capacity()) {
            ++reallocCount;
        }
        vec.push_back(i);
    }

    std::cout << "std::vector perskirstymai: " << reallocCount << "\n";
}

void testCustomVector() {
    Vector<int> vec;
    int reallocCount = 0;

    for (int i = 0; i < N; ++i) {
        if (vec.size() == vec.capacity()) {
            ++reallocCount;
        }
        vec.push_back(i);
    }

    std::cout << "Tavo Vector perskirstymai: " << reallocCount << "\n";
}

int main() {
    using namespace std::chrono;

    std::cout << "Testuojama su " << N << " elementų:\n\n";

    auto start = high_resolution_clock::now();
    testStdVector();
    auto end = high_resolution_clock::now();
    duration<double> stdDuration = end - start;
    std::cout << std::fixed << std::setprecision(3)
              << "std::vector trukmė: " << stdDuration.count() << " s\n\n";

    start = high_resolution_clock::now();
    testCustomVector();
    end = high_resolution_clock::now();
    duration<double> customDuration = end - start;
    std::cout << std::fixed << std::setprecision(3)
              << "Tavo Vector trukmė: " << customDuration.count() << " s\n";

    return 0;
}
