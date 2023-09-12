// Assignment 03, Part 4: Priority Lists
// Due: Tue Sep 5, 2023 11:59pm
//
// File:   assignment3part4.cpp
// Author: Kaylee Lewis
//
// Purpose:
// A priority list changes the definition of a list so that items are arranged in some numerical priority order.
// Build a new class that keeps an instance of your LIst class to store the list that keeps track of the priority
// value for each item (use a structure that is stored within the List instance).
// Modify the List class to include a insert method, that given a pointer to an insert point, inserts a new entry
// in a List right before the item pointed to by the pointer.
// Use this new function on the List class to insert as the way to insert items into the priority list at the correct
// location.
//
// https://www.geeksforgeeks.org/priority-queue-using-linked-list/
// https://en.cppreference.com/w/cpp/container/queue
// https://en.cppreference.com/w/cpp/container/priority_queue
// https://learn.microsoft.com/en-us/troubleshoot/developer/visualstudio/cpp/libraries/stl-priority-queue-class-custom-type
// https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1.insert?view=net-7.0


#include <iostream>
#include "Library.h"

int main( )
{
    List< int > datalist;

    datalist.push_front( 777, 10 );
    datalist.priorityInsert( 137, 1 );
    datalist.priorityInsert( 220, 5 );
    datalist.priorityInsert( 320, 2 );
    datalist.priorityInsert( 315, 3 );

    std::cout << "The highest-priority element is: " << datalist.front( ) << std::endl;

    datalist.pop_front( );

    std::cout << "The highest-priority element after pop is: " << datalist.front( ) << std::endl;

    return 0;
}
