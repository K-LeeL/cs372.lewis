// Assignment 04, Part 3: In-fix to Post-fix and Pre-fix
// Due: Tue Sep 12, 2023 11:59pm
//
// File:   assignment4part3.cpp
// Author: Kaylee Lewis

// Purpose: 
//   In lecture, we did a case study that illustrated how to use a pair of stacks to implement a simple calculator that is capable of evaluating a fully parenthesized expression.  
// Use that code as a guide to implement a program that accepts a fully parenthesized expression as input and outputs the expression in both prefix and postfix notation. 
//You may use the `Stack` class from the previous question or the STL's `stack` class in your solution.  
// (HINT: Most of the work is done for you already, look closely at how the simple calculator does manipulation of the stacks.)
//

// needs error handling in case someone doesnt type in the expressions correctly

#include <cctype>   
#include <cstring>  
#include <iostream>
#include <stack>  

using namespace std;

double readAndEvaluate(istream &ins);
void evaluateStackTops(stack<double> &numbers, stack<char> &ops);

int main()
{
  cout << "Type a fully parenthsized expression" << endl;
  double answer = readAndEvaluate(cin);
  cout << "That evaluates to " << answer << endl;
  return 0;
}

double readAndEvaluate(istream &ins) {
  const char DECIMAL = '.';
  const char RIGHTPAREN = ')';
  stack<double> numbers;
  stack<char> operations;
  double number;
  char symbol;
  while (ins && ins.peek() != '\n') {
    if (isdigit(ins.peek()) || (ins.peek() == DECIMAL)) {
      ins >> number;
      numbers.push(number);
    } else if (strchr("+-*/", ins.peek()) != NULL) {
      ins >> symbol;
      operations.push(symbol);
    } else if (ins.peek() == RIGHTPAREN) {
      ins.ignore();
      evaluateStackTops(numbers, operations);
    } else {
      ins.ignore();
    }
  }
  return numbers.top();
}
void evaluateStackTops(stack<double> &numbers, stack<char> &operations) 
{
  double op1, op2;
  op2 = numbers.top();
  numbers.pop();
  op1 = numbers.top();
  numbers.pop();
  switch (operations.top()) {
    case '+':
      numbers.push(op1 + op2);
      break;
    case '-':
      numbers.push(op1 - op2);
      break;
    case '*':
      numbers.push(op1 * op2);
      break;
    case '/':
      numbers.push(op1 / op2);
      break;
  }
  operations.pop();
}
