#include "day1.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype> // isdigit()

// internal functions
std::vector<std::string> getLinesFromFile();
int processLines(const std::vector<std::string>& lines);
int getNumFromLine(const std::string& line);

int day1::getSum() 
{
  // Gather the lines from the file
  std::vector<std::string> lines = getLinesFromFile();

  return processLines(lines);
}

// Read file in (prob will end up abstracting this if the other tests are like this)
std::vector<std::string> getLinesFromFile() 
{
  std::ifstream infile("../day1-0.txt"); // relative to binary
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

// Process each line 
int processLines(const std::vector<std::string>& lines)
{
  int sum = 0;
  for(std::string line : lines){
    sum += getNumFromLine(line);
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
