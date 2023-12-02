#include "day1.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cctype> // isdigit()

#define FILE_LOC "../day1-0.txt"

const std::vector<std::string> NUM_STRS = {"zero","one","two","three","four","five","six","seven","eight","nine"};
// internal functions
std::vector<std::string> getLinesFromFile();
int processLines(const std::vector<std::string>& lines, bool bEnhanced);
int getNumFromLine(const std::string& line);
int getNumFromLineEnhanced(const std::string& line);
bool isStringNum(const std::string& line, int idx, int& digit0);
bool isStringNumBackwards(const std::string& line, int idx, int& digit1);

// -- day1 functions --
int day1::getSum1() 
{
  // Gather the lines from the file
  std::vector<std::string> lines = getLinesFromFile();

  return processLines(lines, false);
}

int day1::getSum2() 
{
  // Gather the lines from the file
  std::vector<std::string> lines = getLinesFromFile();

  return processLines(lines, true);
}

// ---------------- INTERNAL FUNC DEFINITIONS -------------------------

// Read file in (prob will end up abstracting this if the other tests are like this)
std::vector<std::string> getLinesFromFile() 
{
  std::ifstream infile(FILE_LOC); // relative to binary
  std::stringstream buf;
  buf << infile.rdbuf();
  
  // split strings into return
  buf.seekg(0);
  std::vector<std::string> ret;
  std::string line;
  while(std::getline(buf, line, '\n')){
    ret.push_back(line);
  }

  return ret;
}

// Process each line (bEnhanced uses the strings that represent nums as well)
int processLines(const std::vector<std::string>& lines, bool bEnhanced)
{
  int sum = 0;
  for(std::string line : lines){
    if(bEnhanced) {
      sum += getNumFromLineEnhanced(line);
    } else {
      sum += getNumFromLine(line);
    }
  }
  return sum;
}

// Get the number from a line
int getNumFromLine(const std::string& line) 
{
  int digit0 = -1, digit1 = -1;
  const int LINE_LEN = line.length();

  for(int i = 0; i < LINE_LEN; i++) {
    const int lastIdx = LINE_LEN - 1 - i;
    // check digit0 & digit1
    bool found0 = (digit0 != -1);
    bool found1 = (digit1 != -1);

    if(!found0 && isdigit(line[i])) {
      digit0 = i;
    }
    if(!found1 && isdigit(line[lastIdx])) {
      digit1 = lastIdx;
    }

    found0 = (digit0 != -1);
    found1 = (digit1 != -1);

    // If we've found 0 and 1, no need for more looping
    if(found0 && found1) break;
  }

  int tensplace = (int)(line[digit0] - '0') * 10;
  int onesplace = (int)(line[digit1] - '0');
  return tensplace + onesplace;
}

int getNumFromLineEnhanced(const std::string& line)
{
  const int LINE_LENGTH = line.length();
  int digit0Idx = -1, digit1Idx = -1;
  int digit0 = -1, digit1 = -1;
  bool digit0Found = false, digit1Found = false;

  for(int i = 0; i < LINE_LENGTH; i++) {
    // Find first digit from the left
    if(!digit0Found && isdigit(line[i])) {
      digit0 = line[i];
      digit0Idx = i;
      digit0Found = true;
    } else if(!digit0Found){
      // If we didn't hit a digit, check if it's a string-num
      if(isStringNum(line, i, digit0)) {
        digit0 = digit0 + '0';
        digit0Idx = i;
        digit0Found = true;
      }
    } 

    // Find first digit from the right
    const int LASTIDX = LINE_LENGTH - 1 - i;
    if(!digit1Found && isdigit(line[LASTIDX])){
      digit1Idx = i;
      digit1 = line[LASTIDX];
      digit1Found = true;
    } else if(!digit1Found) {
      if(isStringNumBackwards(line, LASTIDX, digit1)) {
        digit1 = digit1 + '0';
        digit1Idx = i;
        digit1Found = true;
      }
    }
  }
  int tensplace = (int)(digit0 - '0') * 10;
  int onesplace = (int)(digit1 - '0');
  return tensplace + onesplace;
}

bool isStringNum(const std::string& line, int idx, int& digit0)
{
  for(int i = 0; i < NUM_STRS.size(); i++) {
    std::string sub = line.substr(idx, NUM_STRS[i].length());
    if(sub == NUM_STRS[i]){
      digit0 = i; 
      return true;
    }
  }
  return false;
}

bool isStringNumBackwards(const std::string& line, int idx, int& digit1){
  for(int i = 0; i < NUM_STRS.size(); i++) {
    int numstr_len = NUM_STRS[i].length();
    if(idx - numstr_len < 0) continue;

    std::string sub = line.substr(idx - NUM_STRS[i].length() + 1, NUM_STRS[i].length());
    if(sub == NUM_STRS[i]) {
      digit1 = i;
      return true;
    }
  }
  return false;
}
