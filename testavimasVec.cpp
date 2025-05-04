
#include "Vektorius.h"
#include <cassert>
#include <iostream>

void test_default_constructor() {
    Vector<int> vec;
    assert(vec.size() == 0);
    assert(vec.capacity() == 0);
    std::cout << "Construktoriaus patikra gera.\n";
}

void test_push_back_and_resize() {
    Vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    assert(vec.size() == 3);
    assert(vec[0] == 10);
    assert(vec[1] == 20);
    assert(vec[2] == 30);
    std::cout << "Push back ir dydzio patikra gerai.\n";
}

void test_clear() {
    Vector<int> vec;
    vec.push_back(100);
    vec.push_back(200);
    vec.clear();
    assert(vec.size() == 0);
    std::cout << "Clear testas good.\n";
}

void test_copy_and_assignment() {
    Vector<int> vec1;
    vec1.push_back(42);
    vec1.push_back(84);

    Vector<int> vec2 = vec1;
    assert(vec2.size() == 2);
    assert(vec2[0] == 42);
    assert(vec2[1] == 84);

    Vector<int> vec3;
    vec3 = vec1; // Assignment operator
    assert(vec3.size() == 2);
    assert(vec3[0] == 42);
    assert(vec3[1] == 84);

    std::cout << "Kopijavimo ir priskirimo operatoriai gerai!\n";
}

int main() {
    test_default_constructor();
    test_push_back_and_resize();
    test_operator_and_at();
    test_resize_and_reserve();
    test_clear();
    test_copy_and_assignment();

    std::cout << "All tests passed successfully.\n";
    return 0;
}