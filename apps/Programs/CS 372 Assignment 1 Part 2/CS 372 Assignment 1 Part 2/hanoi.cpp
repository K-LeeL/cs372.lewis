// Assignment 01 - Part 02: Timing the Towers of Hanoi
// Due : Wed Aug 23,2023 11 : 59pm
//
// File:   hanoi.cpp
// Author: Kaylee Lewis
// 
// Purpose:
// Understand difference in the timings between the recursive and 
// iterative versions of the algorithm
//
// Modify the main() functions in both versions of the Tower of Hanoi 
// to compute how long it takes for 5, 10, 15, 20, 25, 30, and 35 disks.

//https://www.tutorialspoint.com/data_structures_algorithms/tower_of_hanoi.htm

#include <chrono>
#include <iostream>

using namespace std;

void moveDisks(int, int, int, int);
void printIt(int, int, int);

int main() 
{
  const int FROMPEG = 1;
  const int TOPEG = 3;
  const int TEMPPEG = 2;
  // const int NUMDISKS = 3;

  for (auto numdisks : {3, 5, 10, 15, 20, 25, 30, 31, 32, 33, 35}) 
  {
    cout << "Numdisks: " << numdisks << endl;

    auto start = std::chrono::steady_clock::now();
    moveDisks(numdisks, FROMPEG, TOPEG, TEMPPEG);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elasped_seconds = end - start;
   
   cout << "Moved " << numdisks << " pegs"
        << " from peg " << FROMPEG << " to peg " << TOPEG << endl;
   cout << "Num disk: " << numdisks;
    cout << " Elapsed wall time (s): " << elasped_seconds.count();
    cout << endl;
  }
}

void moveDisks(int num, int fromPeg, int toPeg, int tempPeg) 
{
  if (num > 0) 
  {
    moveDisks(num - 1, fromPeg, tempPeg, toPeg);
   // printIt(num, fromPeg, toPeg);
    moveDisks(num - 1, tempPeg, toPeg, fromPeg);
  }
}

void printIt(int disk, int fromPeg, int toPeg) 
{
  // Do nothing for timing test, but otherwise
  cout << "Move disk " << disk << " from pef " << fromPeg << " to peg " << toPeg
       << endl;
}

// Numdisks: 3
// Moved 3 pegs from peg 1 to peg 3 
// Num disk : 3 Elapsed wall time(s) : 4e-07
//
// Numdisks: 35
// Moved 35 pegs from peg 1 to peg 3 
// Num disk : 35 Elapsed wall time(s) : 277.109
//
// The recursive solution can become noticeably slower due to the exponential
// growth in the number of function calls and operations