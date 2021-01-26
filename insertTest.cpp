#include <iostream>
#include "SkewHeap.h"


int PriorityCalc1(Node *);
int PriorityCalc2(Node *);

int main() {

  // Create a SkewHeap s1; insert some integers and a string; dump the
  // skew heap

  SkewHeap s1(PriorityCalc1);
  
  cout << "\nInserting 10..0 into skew heap:\n";

  for(int i = 10; i >= 0; i--){
    s1.insert(i);
    s1.inorder(); cout << endl;
  }
  //s1.removeTop();
  //s1.inorder(); cout << endl;

  //s1.removeTop();
  //s1.inorder(); cout << endl;


  SkewHeap s2(PriorityCalc2);
  for(int i = 50; i >= 40; i--){
    s2.insert(i);
    s2.inorder(); cout << endl;

  }
  s1.skewHeapMerge(s2);
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
