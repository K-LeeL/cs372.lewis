// CS 372 Mid-term Exam: Programming Questions - Question 2
// Due: Tue Sep 19, 2023 10:00pm
//
// File:   MidtermQ2.cpp
// Author: Kaylee Lewis

// Question 2: Many students think C++ has weird syntax.   But other languages do much odder things.   
// For example, in the LISP programming language, all function calls must be surrounded with open and
// closed parenthesis characters.   
// In fact, one my favorite computer science "dad" jokes is that LISP is an acronym for "Lots of Insidious
// Silly Parentheses".
// But we have a way to help these people.   
// Using either the STL stack class or your own Stack class, write a small program that, given a string input
// by the user from the keyboard, will tell the user whether or not the string contains a matching number of
// parentheses.  
//
// HINT: Remember from lecture what it means for you to have equal number of opening and closing parenthesis if
// things match and what that would means if you push and pop characters onto the stack as you go through the string.

#include <iostream>
#include <stack>
#include <string>

void evaluateStack( std::stack< double > &numbers, std::stack< char > &operations );

double Evaluate( std::istream &ins )
{
    const char DECIMAL = '.';
    const char RIGHTPAREN = ')';
    std::stack< double > numbers;
    std::stack< char > operations;
    double number;
    char symbol;
    while( ins && ins.peek( ) != '\n' )
    {
        if( isdigit( ins.peek( ) ) || ( ins.peek( ) == DECIMAL ) )
        {
            ins >> number;
            numbers.push( number );
        } else if( strchr( "+-*/", ins.peek( ) ) != NULL )
        {
            ins >> symbol;
            operations.push( symbol );
        } else if( ins.peek( ) == RIGHTPAREN )
        {
            ins.ignore( );
            evaluateStack( numbers, operations );
        } else
        {
            ins.ignore( );
        }
    }
    return numbers.top( );
}

bool checkParentheses( const std::string &expr )
{
    std::stack< char > parentheses;
    for( char c : expr )
    {
        if( c == '(' )
        {
            parentheses.push( c );
        } else if( c == ')' )
        {
            if( parentheses.empty( ) )
            {
              return false;
            }
            parentheses.pop( );
        }
    }
    return parentheses.empty( );
}

void evaluateStack( std::stack< double > &numbers, std::stack< char > &operations )
{
    double op1, op2;
    op2 = numbers.top( );
    numbers.pop( );
    op1 = numbers.top( );
    numbers.pop( );
    switch( operations.top( ) )
    {
        case '+':
            numbers.push( op1 + op2 );
            break;
        case '-':
            numbers.push( op1 - op2 );
            break;
        case '*':
            numbers.push( op1 * op2 );
            break;
        case '/':
            numbers.push( op1 / op2 );
            break;
    }
    operations.pop( );
}

int main( )
{
    // std::cout << "Type a fully parenthsized expression" << std::endl;
    // double answer = Evaluate(std::cin);
    // std::cout << "That evaluates to " << answer << std::endl;

    std::string expression;
    std::cout << "Type an expression" << std::endl;
    std::getline( std::cin, expression );

    if( checkParentheses( expression ) )
    {
        std::cout << "The expression you entered contains a matching number of parentheses. " << std::endl;
    } else
    {
        std::cout << "The expression you entered does not contain a matching number of parentheses. " << std::endl;
    }

    return 0;
}
