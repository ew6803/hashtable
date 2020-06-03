//ASDFASDFASDFADS
// Start Monday

#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

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

void DELETE(Node* hashTable[], int sID, int size) {
  int num = HVALUE(sID, size);
  Node* list = hashTable[num];
  Node* previous = NULL;
  if (list == NULL) {
    return; 
  }
  while (list != NULL) {
    if (list -> data -> ID == sID) {
      if (previous == NULL) {
	hashTable[num] = NULL;
      }
      else {
        previous -> next = list -> next; 
      }
      return; 
    }
    previous = list;
    list = list -> next; 
  }
  return; 
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
      char* fName = new char();
      char* lName = new char();
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
	int index = HVALUE(ID, size);
	bool valid = ADD(hashTable, index, temp);
	if (valid == false) {
          Node** newHash = new Node*[size*2];
	  REHASH(newHash, hashTable, size);
	  hashTable = newHash; 
	}
      }
    }
    else if (strcmp(input, "GENERATE") == 0) {
      vector<char*> fNames;
      vector<char*> lNames;
      ifstream inFile;
      char* temp;
      char* temp2;
      int number = 0;
      char fileInput[10000];
      char fileInput2[10000]; 
      char fileName[25];
      cout << "First File Name? \n"; 
      cin.getline(fileName, 25);
      inFile.open(fileName);
      inFile.getline(fileInput, 10000);
      temp = strtok(fileInput, " ");
      while (temp != NULL) {
	fNames.push_back(temp);
	temp = strtok(NULL, " "); 
      }
      inFile.close(); 
      char fileName2[25];
      cout << "Second File Name? \n"; 
      cin.getline(fileName2, 25);
      inFile.open(fileName2);
      inFile.getline(fileInput2, 10000); 
      temp2 = strtok(fileInput2, " ");
      while (temp2 != NULL) { 
        lNames.push_back(temp2);
	temp2 = strtok(NULL, " "); 
      }
      inFile.close(); 
      cout << "How many students? \n";
      cin >> number;
      for (int a = 0; a < number; a++) {
	char* firstName = new char();
	char* lastName = new char();
	int fIndex = 0;
	int lIndex = 0;
	float randGPA = 0;
	fIndex = rand() % fNames.size()+1;
	lIndex = rand() % lNames.size()+1;
	if (fIndex == 0) {
	  fIndex = 1;
	}
	firstName = fNames.at(fIndex - 1);
	lastName = lNames.at(lIndex - 1);
	randGPA = ((double) rand() / (RAND_MAX)) * 4;
        int lID = 0;
        for (vector<int>::iterator it = IDs.begin(); it != IDs.end(); ++it) {
	  if((*it) > lID) {
	    lID = (*it); 
	  }
	}
	IDs.push_back(lID + 1);
	Student* temp = new Student();
	temp -> fName = firstName;
	temp -> lName = lastName;
	temp -> GPA = randGPA;
	temp -> ID = lID + 1;
	int index = HVALUE(lID+1, size);
	bool valid = ADD(hashTable, index, temp);
	if (valid == false) {
	  Node** newHash = new Node*[size*2];
	  REHASH(newHash, hashTable, size);
	  hashTable = newHash; 
	}
      }
    }
    else if (strcmp(input, "PRINT") == 0) {
      PRINT(hashTable, size); 
    }
    else if (strcmp(input, "DELETE") == 0) {
      int sID;
      cout << "Enter Student's ID \n";
      cin >> sID;
      cin.get();
      IDs.push_back(sID);
      DELETE(hashTable, sID, size); 
    }
    else if (strcmp(input, "EXIT") == 0) {
      exit(0); 
    }
    else {
      cout << "Valid Input Plz \n"; 
    }
    
  }
}
