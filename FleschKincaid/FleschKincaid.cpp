/* * File: FleschKincaid.cpp */
/* * ---------------------- */
/* * Name: [TODO: enter name here] */
/* * Section: [TODO: enter section leader here] */
/* * This file is the starter project for the Flesch-Kincaid problem. */
/* * [TODO: rewrite the documentation] */
/* */

#include "./StanfordCPPLib/console.h"
#include "./StanfordCPPLib/simpio.h"
#include "./StanfordCPPLib/tokenscanner.h"
#include <cctype>
#include <fstream>
#include <iostream>
using namespace std;

// I dont think ',' should be considered as a punctuation to count sentences
const string punctuations = "!?.";
const string vowels = "aeiouy";
const string SENTINEL = "-1";
const float C0 = -15.59;
const float C1 = 0.39;
const float C2 = 11.8;

struct fileDataT {
  int sentences;
  int words;
  int syllables;
};

fileDataT analyzeFile(TokenScanner);
int countSyllables(string word);
void updateScannerOptions(TokenScanner &);
float calculateGrade(fileDataT);
void printData(fileDataT);

int main() {
  // we run in loop so user can enter file again and again
  while (true) {
    string message = "Enter file name (" + SENTINEL + " to exit): ";
    string filename = getLine(message);
    if (filename == SENTINEL) {
      break;
    }
    ifstream input(filename);
    if (!input) {
      cout << "Such file doesn't exist" << endl;
      continue;
    }

    TokenScanner scanner(input);
    updateScannerOptions(scanner);
    fileDataT data = analyzeFile(scanner);
    printData(data);
  }
  return 0;
}

void printData(fileDataT data) {
  cout << "WORDS: " << data.words << endl;
  cout << "SENTENCES: " << data.sentences << endl;
  cout << "SYLLABLES: " << data.syllables << endl;
  cout << "TOTAL GRADE: " << calculateGrade(data) << endl;
}

void updateScannerOptions(TokenScanner &scanner) {
  scanner.ignoreWhitespace();
  scanner.addWordCharacters("'");
}

float calculateGrade(fileDataT data) {
  return C0 + C1 * ((float)data.words / data.sentences) +
         C2 * ((float)data.syllables / data.words);
}

fileDataT analyzeFile(TokenScanner scanner) {
  int words = 0;
  int sentenceCounter = 0;
  int syllables = 0;
  while (scanner.hasMoreTokens()) {
    string token = scanner.nextToken();

    if ((isalpha(token[0]) && scanner.getTokenType(token) == WORD)) {
      syllables += countSyllables(token);
      words++;
      continue;
    }

    // If its some kind of punctuation, we can count it as a sentence
    if (ispunct(token[0]) && punctuations.find(token[0]) != string::npos) {
      if (token.length() == 1 || !isalnum(token[1])) {
        sentenceCounter++;
      }
    }
  }
  // Words and sentences should be minimum of 1 or division by zero will cause
  // error
  words = max(words, 1);
  sentenceCounter = max(sentenceCounter, 1);
  syllables = max(syllables, 1);

  fileDataT data;
  data.words = words;
  data.sentences = sentenceCounter;
  data.syllables = syllables;

  return data;
}

int countSyllables(string word) {
  int count = 0;
  for (int i = 0; i < word.length(); i++) {
    // We check if the character and its previous (if its exists) are vowels
    if (vowels.find(tolower(word[i])) != string::npos &&
        (i == 0 || vowels.find(tolower(word[i - 1])) == string::npos)) {
      count++;
    }
  }
  // If last element is 'e' we decrement
  // but second from last mustnt be vowel, for example words tree, bee have 1
  // syllable
  if (count > 1 && tolower(word[word.length() - 1]) == 'e' &&
      vowels.find(tolower(word[word.length() - 2])) == string::npos) {
    count--;
  }
  return max(count, 1);
}
