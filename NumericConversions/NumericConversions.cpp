/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */
#include "./StanfordCPPLib/console.h"
#include "StanfordCPPLib/simpio.h"
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

string intToString(int n);
int stringToInt(string str);
bool isValidInt(string s);

int main() {
  int a = getInteger("Enter an integer to cast to string: ");
  cout << intToString(a) << endl;

  string b = getLine("Enter a string to cast to integer: ");
  cout << stringToInt(b) << endl;

  return 0;
}

int stringToInt(string s) {
  // Base case
  if (s == "") {
    return 0;
  }

  if (!isValidInt(s)) {
    cout << "Not a valid number" << endl;
    // We return -1 when error occures
    return -1;
  }

  // If its negative we return negative
  if (s[0] == '-') {
    return -stringToInt(s.substr(1));
  }

  return (s[s.length() - 1] - '0') +
         10 * stringToInt(s.substr(0, s.length() - 1));
}

string intToString(int n) {
  // Base case
  if (n == 0) {
    return "0";
  }

  // If its negative we add - sign in the beginning
  if (n < 0) {
    return "-" + intToString(-n);
  }

  if (n < 10) {
    return string() + char(n + '0');
  }

  return intToString(n / 10) + intToString(n % 10);
}

bool isValidInt(string s) {
  if (s == "") {
    return false;
  }
  // First we need to find the starting point, if its negative we start from
  // [1]th character, else from [0]th
  int start = (s[0] == '-') ? 1 : 0;
  for (int i = start; i < s.length(); i++) {
    if (!isdigit(s[i])) {
      return false;
    }
  }
  return true;
}
