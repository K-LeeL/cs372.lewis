// Assignment 04, Part 1: Hot Potato!
// Due: Tue Sep 12, 2023 11:59pm
//
// File:   assignment4part1.cpp
// Author: Kaylee Lewis
//
// Purpose: Josepheus program

// https://www.interviewbit.com/blog/josephus-problem/

#include <iostream>
#include <vector>

#include "Header.h"

int main() {
  int players, moves;

  // Loop for getting the number of people
  while (true) {
    std::cout << "Enter the number of people playing the game: ";
    std::cin >> players;
    if (players > 1) {
      break;
    }
    std::cerr << "Need to have more than one person to play the game. Please "
                 "enter a number greater than 1."
              << std::endl;
  }

  // Loop for getting the number of passes
  while (true) {
    std::cout << "Enter the number of times the potato is passed: ";
    std::cin >> moves;
    if (moves >= 1) {
      break;
    }
    std::cerr << "The potato has to be passed at least once. Please enter a "
                 "number greater than 0."
              << std::endl;
  }

  if (moves == 1) {
    std::cout << "Player 1 starts with the potato and passes it one person away."
              << std::endl;
  } else {
    std::cout << "Player 1 starts with the potato and passes it " << moves
              << " people away." << std::endl;
  }

    CircularList<int> hotPotato;

  int listSize = 0; 

  for (int i = 1; i <= players; ++i) {
    hotPotato.push_back(i);
    listSize++;
  }

  typename CircularList<int>::Node *current = hotPotato.head->next;
  std::vector<int> eliminatedPlayers;
  int lastRemainingPlayer = -1;

  while (listSize > 1) {
    for (int i = 0; i <= moves -1; ++i) {
      current = current->next;
      if (current == hotPotato.tail) {
        current = hotPotato.head->next;
      }
    }

    typename CircularList<int>::Node *eliminated = current;
    current = current->next;
    eliminated->prev->next = eliminated->next;
    eliminated->next->prev = eliminated->prev;

    if (eliminated == hotPotato.head) {
      hotPotato.head = hotPotato.head->next;
    }
    if (eliminated == hotPotato.tail) {
      hotPotato.tail = hotPotato.tail->prev;
    }

    eliminatedPlayers.push_back(eliminated->data);
    std::cout << "Player " << eliminated->data << " is out." << std::endl;

     listSize--;

    delete eliminated;
    eliminated = nullptr;
  }

  // Update the winner
  if (listSize == 1) {
    lastRemainingPlayer = hotPotato.front();
  }

  if (lastRemainingPlayer != -1) {
    std::cout << "The winner is player " << lastRemainingPlayer << std::endl;
  } else {
    std::cerr << "Error: No winner found." << std::endl;
  }
  // Print the list of eliminated players
  std::cout << "Eliminated players: ";
  for (size_t i = 0; i < eliminatedPlayers.size(); ++i) {
    std::cout << "Player " << eliminatedPlayers[i];
    if (i < eliminatedPlayers.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;

  return 0;
}
