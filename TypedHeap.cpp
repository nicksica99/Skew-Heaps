//File: TypedHeap.cpp
//Name: Nick Sica
//Email: nsica1@umbc.edu

#include "TypedHeap.h"
#include "SkewHeap.cpp"

using namespace std;

//insertToHeaps function
void TypedHeap::insertToHeaps(vector<string> vec) {
  //for loop that goes through the vector
  for(int i = 0; i < (int) vec.size(); i++) {
    
    int check = 0;
    //this cuts out whitespace, says in project doc
    //that there may be leading and trailing whitespace
    int first = vec[i].find_first_not_of(' ');
    int last = vec[i].find_last_not_of(' ');
    vec[i] = vec[i].substr(first, last-first+1);

    //digits gets the number of characters in the index
    int digits = (int) vec[i].size();
    cout << vec[i] << endl;
    //for loop that goes through the index and checks if everyone of them is a digit 
    for(int j = 0; j < (int) vec[i].size(); j++) {
      //if it is a digit then it increments check
      if(isdigit(vec[i][j]) == true) {
	check++;
      }
    }
    //if check is equal to digits which means that it is all digits it inserts
    //into the intHeap 
    if(digits == check) {
      
      intHeap.insert(stoi(vec[i]));
    }
    //else it inserts into the stringHeap 
    else {
      stringHeap.insert(vec[i]);
	}
  }
}

//combineHeaps function
void TypedHeap::combineHeaps() {
  //calls merge on totalHeap for both the intHeap and the StringHeap
  totalHeap.skewHeapMerge(intHeap);
  totalHeap.skewHeapMerge(stringHeap);


}
//PrintHeaps function
void TypedHeap::printHeaps() const {
  //dumps intHeap 
  cout << "IntHeap Holds: " << endl;
  intHeap.dump();
  //dumps stringheap 
  cout << endl << "StringHeap Holds: " << endl;
  stringHeap.dump();
  //dumps totalheap 
  cout << endl;
  cout << "TotalHeap Holds: " << endl;
  totalHeap.dump();
}

//changePriority function
void TypedHeap::changePriority(pri_fn pri) {
  cout << "change priority typed heaps" << endl;
  //sets the priorities and rebuilds all of the heaps based on the new priority. 
  intHeap.setPriFn(pri);
  stringHeap.setPriFn(pri);
  totalHeap.setPriFn(pri);
  

}






