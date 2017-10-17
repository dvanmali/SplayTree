// main.cpp
// Dylan Vanmali
// CS130A Spring 2017 Prof. Suri

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "SplayTree.cpp"
using namespace std;

int main(int argc, char* argv[]) {
  string         line;
  SplayTree<int> *s = new SplayTree<int>;
  int            lineNum = 0;
  int            operations = 0;

  while( getline( cin, line ) ) {
    //cout << line << endl;
    
    if (lineNum == 0) {
      operations = atoi(line.c_str());
    }
    else {
      if (line.find("insert ") == 0) {
	s->insert(atoi(line.substr(7).c_str()));
      }
      else if (line.find("delete ") == 0) {
	s->deleteValue(atoi(line.substr(7).c_str()));
      }
      else if (line.find("find ") == 0) {
	s->find(atoi(line.substr(5).c_str()));
      }
      else if (line.find("print") == 0) {
	cout << *s;
      }
    }
    lineNum++;
  }
  return 0;
}
