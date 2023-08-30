//
// File:   stlvectest.cpp
// Author: Your Glorious Instructor
// Purpose:
// Determine beavior and performance of capacity increate in STL vector.
//
#include "vector.hpp"
#include <chrono>
#include <iostream>

const int PrintInterval = 10;

class VecTester {
private:
   vector<int> testVector =  vector<int>();
    
    void fillVector(size_t cap) {
        for (int i = 0 ; i < cap; ++i) { testVector[i] = i; }
    }
public:
    void tester() {
        size_t currentCap = testVector.capacity();
        std::cout << "Starting capacity: " << currentCap << std::endl;
        for (int i = 0; i <= 500; i++) {
            if ((i % PrintInterval) == 0) {
                std::cout << "Current cap: " << currentCap << std::endl;
            }
            auto start = std::chrono::steady_clock::now();
            testVector.push_back(i);
            auto end = std::chrono::steady_clock::now();
            currentCap = testVector.capacity();
            std::chrono::duration<double> elaspedSeconds = end - start;
            if ((i % PrintInterval) == 0) {
                std::cout << "For increase capacity to "
                << currentCap
                << " took "
                << elaspedSeconds.count() << " seconds"
                << std::endl;
            }
                
        }
    }
};

int main() {
    VecTester testingObject;
    std::cout << "Starting test: " << std::endl;
    testingObject.tester();
    return 0;
}
