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

#include <chrono>
#include <cmath>
#include <iostream>
#include <stack>

using namespace std;

void moveDisks(int, stack<int> &, stack<int> &, stack<int> &);
void printIt(int, char, char);
void MoveDisksHelper(stack<int> &, stack<int> &, char, char);

int main() 
{
  for (auto numdisks : {3, 5, 6, 10, 15, 20, 25, 30, 35}) 
{
    stack<int> source;
    stack<int> dest;
    stack<int> aux;

    auto start = std::chrono::steady_clock::now();
    moveDisks(numdisks, source, aux, dest);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;

    cout << "Moved " << numdisks << " pegs." << endl;
    cout << "Num disks: " << numdisks;
    cout << " Elapsed wall time (s): " << elapsed_seconds.count();
    cout << endl;
  }
  return 0;
}

void moveDisks(int num, stack<int> &fromPeg, stack<int> &tempPeg,
               stack<int> &toPeg) 
{
  char s = 'S', d = 'D', a = 'A';

  if (num % 2 == 0) 
  {  // Swap in num disks is even.
    char temp = d;
    d = a;
    a = temp;
  }

  int numberOfMoves = pow(2, num) - 1;

  for (int i = num; i >= 1; i--) 
  {
    fromPeg.push(i);
  }

  // now do moves:
  for (int i = 1; i <= numberOfMoves; i++) 
  {
    if (i % 3 == 0) 
    {
      MoveDisksHelper(tempPeg, toPeg, a, d);
    } else if (i % 3 == 2) 
    {
      MoveDisksHelper(fromPeg, tempPeg, s, a);
    } else if (i % 3 == 1) 
    {
      MoveDisksHelper(fromPeg, toPeg, s, d);
    }
  }
}

void MoveDisksHelper(stack<int> &source, stack<int> &dest, char s, char d) 
{
  int top1;
  int top2;
  if (source.empty()) 
  {
    top2 = dest.top();
    dest.pop();
    source.push(top2);
  //  printIt(top2, d, s);
  } else if (dest.empty()) 
  {
    top1 = source.top();
    source.pop();
    dest.push(top1);
  //  printIt(top1, s, d);
  } else if (source.top() > dest.top()) 
  {
    top1 = source.top();
    source.pop();
    top2 = dest.top();
    dest.pop();
    source.push(top1);
    source.push(top2);
   // printIt(top2, d, s);
  } else 
  {
    top2 = dest.top();
    dest.pop();
    top1 = source.top();
    source.pop();
    dest.push(top2);
    dest.push(top1);
   // printIt(top1, s, d);
  }
}

void printIt(int disk, char fromPeg, char toPeg) 
{
  // Do nothing for timing test, but otherwise
  std::cout << "Move disk " << disk << " from peg " << fromPeg << "to peg "
            << toPeg << std::endl;
}

//Moved 3 pegs.
//Num disks : 3 Elapsed wall time(s) : 4.57e-05
//
//Moved 35 pegs.
// Num disks : 35 Elapsed wall time(s) : 1.16e-05
// 
// The iterative version shows better performance due to its more direct
// control over the recursion stack.