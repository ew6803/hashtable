//ASDFASDFASDFADS
// Start Monday

#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

struct Student {
  char* fName;
  char* lName;
  int ID;
  float GPA; 
};

struct Node {
  Student* data = NULL;
  Node* next = NULL; 
};

int main () {
  char input[50];
  Node** hashTable = new Node*[100];
  vector <int> IDs;
  for (int i = 0; i < 100; i++) {
    hashTable[i] = NULL; 
  }
  int size = 100;
  bool keep = true;
  while (keep == true) {
    cout << "Welcome to hashtable, type 'ADD' to add a student, type 'DELETE' to delete a student, type 'PRINT' to print the students, type 'GENERATE' to generate random students, type 'EXIT' to quit. \n";
    cin.getline(input, 50);
    if (strcmp(input, "ADD") == 0) {
      int ID;
      float GPA;
      char* fName;
      char* lName;
      cout << "Firstname? \n";
      cin.getline(fName, 20);
      cout << "Lastname? \n";
      cin.getline(lName, 20);
      cout << "ID? \n";
      cin >> ID;
      cin.get();
      cout << "GPA? \n";
      cin >> GPA;
      cin.get();
      bool rp = false;
      for (vector<int>:: iterator it = IDs.begin(); it != IDs.end(); it) {
	if((*it) == ID) {
	  rp = true; 
	}
      }
      if (rp == false) {
	IDs.push_back(ID);
	Student* temp = new Student();
	temp -> fName = fName;
	temp -> lName = lName;
	temp -> ID = ID;
	temp -> GPA = GPA;
      }
    }
    else if (strcmp(input, "GEN") == 0) {

    }
    else if (strcmp(input, "PRINT") == 0) {

    }
    else if (strcmp(input, "DELETE") == 0) {

    }
    else if (strcmp(input, "EXIT") == 0) {
      exit(0); 
    }
    else {
      cout << "Valid Input Plz \n"; 
    }
    
  }
}
