#include <iostream>
#include "TypedHeap.h"

// Prototypes for two priority functions
int PriorityCalc1(Node *);
int PriorityCalc2(Node *);

int main() {

  TypedHeap t1(PriorityCalc1);

  vector<string> vec;
  vec.push_back("1234");
  vec.push_back("Hello world");
  vec.push_back("ooga boog");
  vec.push_back("5678");
  
  t1.insertToHeaps(vec);


  t1.printHeaps();

  t1.combineHeaps();

  t1.printHeaps();

  t1.changePriority(PriorityCalc2);

  t1.printHeaps();

  
}


int PriorityCalc1(Node *node){
  int sum = 0;
  if(node->tagged_union == ISINT){
    return node->data_int;
  }
  else{
    int size = node->data_string.size();
    for(int i = 0; i < size; i++){
      sum = sum + node->data_string[i];
    }
  }
  return sum;
}

int PriorityCalc2(Node *node){
  int sum = 0;
  if(node->tagged_union == ISINT){
    return (-1 * (node->data_int));
  }
  else{
    int size = node->data_string.size();
    for(int i = 0; i < size; i++){
      sum = sum + node->data_string[i];
    }
  }
  return (-1 *sum);
}
