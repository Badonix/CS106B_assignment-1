/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include "./StanfordCPPLib/console.h"
#include "StanfordCPPLib/simpio.h"
#include <cmath>
#include <iostream>
using namespace std;

int getPascalsItem(int a, int b);
int main() {
  int n, k;
  while (true) {
    n = getInteger("Enter n: ");
    k = getInteger("Enter k: ");
    if (n >= 0 && k >= 0) {
      if (n < k) {
        cout << "n must be >= k" << endl;
        continue;
      }
      break;
    }
    cout << (n < 0 ? "Please enter positive n" : "Please enter positive k")
         << endl;
  }
  int answ = getPascalsItem(n, k);
  cout << answ << endl;
  return 0;
}

// Straightforward
int getPascalsItem(int n, int k) {
  if (k == 0 || k == n) {
    return 1;
  }
  return getPascalsItem(n - 1, k - 1) + getPascalsItem(n - 1, k);
}
