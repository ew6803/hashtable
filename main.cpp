//ASDFASDFASDFADS
// Start Monday

#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iomanip>

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

bool ADD(Node* hashTable[], int index, Student* s) {
  if (hashTable[index] == NULL) {
    Node* temp = new Node();
    temp -> data = s;
    hashTable[index] = temp;
    return true; 
  }
  Node* list = hashTable[index];
  Node* temp  = new Node();
  temp -> next = list;
  temp -> data = s;
  hashTable[index] = temp;
  list = temp;
  int count = 1;
  while (list != NULL) {
    list = list -> next;
    count++; 
  }
  if (count > 3) {
    return false; 
  }
  else {
    return true; 
  }
}

int HVALUE(int ID, int size) {
  int total = 0;
  while (ID != 0) {
      total = total + ID % 10;
      ID = ID / 10; 
  }
    int multiple = trunc(size/10);
    return ((total * multiple) % size); 
}

void REHASH(Node* newHash[], Node* oldHash[], int &size) {
  for (int i = 0; i < (size * 2); i++) {
    newHash[i] = NULL; 
  }
  int nSize = 2 * size;
  for (int i = 0; i < size; i++) {
    if (oldHash[i] != NULL) {
      Node* list = oldHash[i];
      while (list -> data != NULL) {
        if (list -> data != NULL) {
	  Student* temp = list -> data;
	  int index = HVALUE(temp -> ID, nSize);
	  ADD(newHash, index, temp);
	  list = list -> next; 
	}
      }
    }
  }
  size = nSize; 
}

void PRINT(Node* table[], int size) {
  cout << fixed;
  cout << setprecision(2);
  Node* list;
  for (int i = 0; i < size; i++) {
    if (table[i] != NULL) {
      list = table[i];
      while (list != NULL) {
        if (list -> data != NULL) {
	  cout << "First Name: " << list -> data -> fName << endl;
	  cout << "Last Name: " << list -> data -> lName << endl;
	  cout << "Student ID; " << list -> data -> ID << endl;
	  cout << "GPA: " << list -> data -> GPA << endl; 
	}
	list = list -> next; 
      }
    }
  }
}

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
	int index = hashValue(ID, size);
	bool valid = (ADD(hashTable, index, temp);
	if (valid == false) {
          Node** newHash = new Node*[size*2];
	  REHASH(newNash, hashTable, size);
	  hashTable = newHash; 
	}
      }
    }
    else if (strcmp(input, "GEN") == 0) {

    }
    else if (strcmp(input, "PRINT") == 0) {
      PRINT(hashTable, size); 
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
