// CS 372 Mid-term Exam: Programming Questions - Question 3
// Due: Tue Sep 19, 2023 10:00pm
//
// File:   MidtermQ3.cpp
// Author: Kaylee Lewis

// Question 3: People like to be lazy.   To the point at times where we try to write our code to be lazy as well.   
// For example, there is the concept of doing a "lazy deletion" from a linked list.   For "lazy deletion", we delay deleting the items from the list until some storage condition is met.   The deletion process just needs to mark an item as deleted and then delete anything marked as deleted when needed.   

// Modify the linked list class from our lectures to support lazy deletion.
// Keep track of the deleted status as an extra field in your node class and keep a count of deleted and not -deleted nodes as private state in your modifed linked list.
// Delete all deleted items from the list when the number of deleted items equals the number of non - deleted items
// (do this by traversing the list, deleting items as normal, and remember to keep the pointers straight).
// Modify all other methods in the class to correctly ignore deleted items.

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
