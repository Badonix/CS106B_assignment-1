/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include "./StanfordCPPLib/console.h"
#include "./StanfordCPPLib/random.h"
#include <iostream>
using namespace std;

const int TARGET = 3;
bool flip();
int main() {
  bool heads = randomChance(0.5);
  int totalCount = 0;
  int consecutiveHeadCount = 0;

  while (consecutiveHeadCount != TARGET) {
    bool isHead = flip();
    // If its not head we restart consecutive counter
    isHead ? consecutiveHeadCount++ : consecutiveHeadCount = 0;
    totalCount++;
  }
  cout << "It took " << totalCount << " flips to get " << TARGET
       << " consecutive heads." << endl;
  return 0;
}
bool flip() {
  bool isHead = randomChance(0.5);
  cout << (isHead ? "heads" : "tails") << endl;
  return isHead;
}
