// Assignment 06, Part 3: Testing the connection between binary search and binary search trees
// Due: Tue Oct 10, 2023 11:59pm
//
// File:   A6Part3.cpp
// Author: Kaylee Lewis

// Now use the binary search function from the first question plus the structure and the function
// that fills and sorts a vector of random integers from the second question to write a program that
// will compare the execution time of binary search vs. lookup times in a binary search tree.
// You program should generate one of the structures from the previous questions for arrays and trees with
// 1000, 2500, 5000, 10000,and 50,000 elements. After creating the array it should pick 100 numbers at random
// and search for each number first in the structure’s array and then search for the same number using the BST,
// keeping track of the times in each case (use the chrono library, as was done in the code from the Towers of Annoy...
// I mean "Towers of Hanoi"... assignment).
// Compute and report the average times for both types of search for each of the array/tree sizes.

//https://codereview.stackexchange.com/questions/70869/binary-search-tree-in-c
//https://cplusplus.com/forum/beginner/65928/


#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "Header.h"

template <typename T>
bool binarySearch(std::vector<T> &aSortedVector, T itemToBeFound)
{
    int left = 0;
    int right = aSortedVector.size() - 1;
    int mid;

    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (aSortedVector[mid] == itemToBeFound)
            return true;
        else if (aSortedVector[mid] < itemToBeFound)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}

struct BigStruct
{
    size_t size;
    std::vector<int> *vect;
    Tree<int> *tree;

    BigStruct(size_t s) : size(s), vect(new std::vector<int>()), tree(new Tree<int>()) {}
    ~BigStruct()
    {
        delete vect;
        delete tree;
    }
};

BigStruct* createBigStruct(size_t n)
{
    BigStruct *struc = new BigStruct(n);
    for (size_t i = 0; i < n; ++i)
    {
        int random_val = rand();
        struc->vect->push_back(random_val);
    }
    std::sort(struc->vect->begin(), struc->vect->end());
    for (size_t i = 0; i < n; ++i)
    {
        struc->tree->insert(struc->vect->at(i));
    }
    return struc;
}

int main()
{
    std::vector<size_t> sizes = {1000, 2500, 5000, 10000, 50000};

    for (auto size : sizes)
    {
        BigStruct *bs = createBigStruct(size);
        std::vector<int> randomNums;

        // Pick 100 numbers at random
        for (int i = 0; i < 100; ++i)
        {
            randomNums.push_back(bs->vect->at(rand() % size));
        }

        auto startBinSearch = std::chrono::high_resolution_clock::now();
        for (auto num : randomNums)
        {
            binarySearch(*bs->vect, num);
        }
        auto endBinSearch = std::chrono::high_resolution_clock::now();

        auto startTreeSearch = std::chrono::high_resolution_clock::now();
        for (auto num : randomNums)
        {
            bs->tree->member(num);
        }
        auto endTreeSearch = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> binaryTime = endBinSearch - startBinSearch;
        std::chrono::duration<double, std::milli> treeTime = endTreeSearch - startTreeSearch;

        std::cout << "For size: " << size << std::endl;
        std::cout << "Average binary search time (ms): " << binaryTime.count() / 100.0 << std::endl;
        std::cout << "Average BST lookup time (ms): " << treeTime.count() / 100.0 << std::endl;
        std::cout << "--------------------------" << std::endl;

        delete bs;
    }

    return 0;
}