// File: SkewHeap.cpp
// Name: Nick Sica
// Email: nsica1@umbc.edu

#include "SkewHeap.h"
using namespace std;

//SkewHeap constructor 
SkewHeap::SkewHeap(pri_fn pri) {
  //sets data values 
  priority = pri;
  m_heap = nullptr;
}

//SkewHeap copy constructor 
SkewHeap::SkewHeap( const SkewHeap& rhs) {
  //creates a temporary node and copies priority
  Node *temp = rhs.m_heap;
  priority = rhs.priority;
  //if rhs is empty 
  if(rhs.m_heap == nullptr) {
    
    m_heap = nullptr;
  }
  //calls copyHelper 
  else {
    m_heap = copyHelper(temp);
  }
 
}
//copyHelper function to copy the data over 
Node* SkewHeap::copyHelper(Node *root) {
  //if empty then return
  if(root == nullptr) {
    return nullptr;
  }
  //if the node is an integer
  if(root->tagged_union == ISINT) {
    //creates a new node and recursively goes through the heap to get the left and right
    //children 
    Node *temp = new Node(root->data_int);
    temp->left = copyHelper(root->left);
    temp->right = copyHelper(root->right);
    return temp;
  }
  //the node is a string it creates a new string node and goes through the heap
  //to get the left and right children 
  Node *temp = new Node(root->data_string);
  temp->left = copyHelper(root->left);
  temp->right = copyHelper(root->right);
  return temp;
}
  


//destructor 
SkewHeap::~SkewHeap() {
  //calls destructor helper 
  Clear(m_heap);
  m_heap = nullptr;

}
//Clear function
void SkewHeap::Clear(Node *node) {
  //recursively goes through the heap and deletes the nodes 
  if(node) {
    
    Clear(node->left);
    Clear(node->right);
    delete node;
  }
}
//Assignment operator 
const SkewHeap& SkewHeap::operator= ( const SkewHeap& rhs) {
  //deletes the current treap 
  if(this != &rhs) {
    Clear(m_heap);
    m_heap = nullptr;

    //sets the treaps equal 
    Node *temp = rhs.m_heap;
    priority = rhs.priority;
    m_heap = copyHelper(temp);
  }
  return *this;
}
//get priority function //returns the priority function pointer
pri_fn SkewHeap::getPriFn() const {
  return priority;
}
//sets priority function
void SkewHeap::setPriFn( pri_fn pri) {
  //sets priority
  priority = pri;
  //creates a new heap with the new priority
  SkewHeap temp = SkewHeap(priority);
  while(m_heap != nullptr) {
    //inserts into the new heap 
    if(m_heap->tagged_union == ISINT) {
      temp.insert(m_heap->data_int);
    }
    else {
      temp.insert(m_heap->data_string);
    }
    //removes the top so it will go through the tree
    removeTop();
  }
  //sets the current heap equal to the updated heap 
  *this = temp;
  
}
//empty function //checks if the heap is empty 
bool SkewHeap::empty() const {
  return m_heap == nullptr;
}
//insert function (integers)
void SkewHeap::insert(int data) {
  //creates a new heap
  //adds data to the heap 
  SkewHeap temp = SkewHeap(getPriFn());
  Node *dataNode = new Node(data);
  temp.m_heap = dataNode;

  //merges the current heap and the temp heap 
  skewHeapMerge(temp);
  
}
//insert function (strings)
void SkewHeap::insert( string data) {
  //creates a new heap and adds data to it 
  SkewHeap temp = SkewHeap(getPriFn());
  Node *dataNode = new Node(data);
  temp.m_heap = dataNode;

  //merges the current heap and the temp heap together 
  skewHeapMerge(temp);
}
//front //returns m_heap 
Node* SkewHeap::front() const {
  return m_heap;

}
//RemoveTop function
void SkewHeap::removeTop() {
  if(empty()) {
    return;
  }
  //gets the left and right sub heaps
  Node *left, *right;
  left = m_heap->left;
  right = m_heap->right;

  //deletes the top node
  delete m_heap;
  m_heap = nullptr;
  //merges the two heaps together 
  m_heap = mergeHelper(left, right);
  
}
//SkewHeapMerge 
void SkewHeap::skewHeapMerge( SkewHeap &sh) {
  //if two sepearate priorties it throws an error 
  if(sh.getPriFn() != this->getPriFn()) {
    throw std::domain_error("Error:Different priority functions");
  }
  //if other heap is empty 
  else if(sh.m_heap == nullptr) {
    return;
    
  }
  else {
    //calls mergeHelper function 
    m_heap = mergeHelper(m_heap, sh.m_heap);
  }
  //other heap is empty so i set the m_heap to null 
  sh.m_heap = nullptr;
}

//MergeHelper //Based of the pseudocode in the project document
Node *SkewHeap::mergeHelper(Node *heap1, Node* heap2) {
  //if heap1 is null then returns heap2 (nodes)
  if(heap1 == nullptr) {
    return heap2;
  }
  //heap2 is null then return heap1
  else if(heap2 == nullptr) {
    return heap1;
  }
  else {
        
    //gets priorities using the function pointers and comparing them
    //swapping values if necessary 
    if(priority(heap1) < priority(heap2))
      {
	swap(heap1, heap2);
      }
    //swap left and right and recursively calls mergeHelper again
    swap(heap1->left, heap1->right);
    heap1->left = mergeHelper(heap2, heap1->left);
    }
  //return heap1
  return heap1;

}


//inorder Function
void SkewHeap::inorder() const {
  //if empty then return
  if(empty()) {
    return;
  }
  //calls inorderHelp function which recursively goes through the heap 
  inorderHelp(m_heap);
  return;

}

//InorderHelp function 
void SkewHeap::inorderHelp(Node *node) const {
  //if empty then return
  if(node == nullptr) {
    return;
  }
  //goes through the left subheap first as far as possible 
  cout << "(";
  inorderHelp(node->left);
  //prints the node's data 
  if(node->tagged_union == ISINT) {
    cout << node->data_int;
  }
  else if(node->tagged_union == ISSTRING) {
    cout << node->data_string;
  }
  //then proceeds to go to the right as far as possible 
  inorderHelp(node->right);
  cout << ")";
  //returns so it will finish the recursive calls
  return;
}
//dump function
void SkewHeap::dump() const {
  //create a temp heap and sets it equal so they are the same  
  SkewHeap temp = SkewHeap(priority);
  temp = *this;
  //if empty just return 
  if(temp.m_heap == nullptr) {
    return;
  }
  //will print out data and calls removeTop() until there is no more data left to print
  while(temp.m_heap != nullptr) {
    if(temp.m_heap->tagged_union == ISINT) {
      cout << "DATA IS: " << temp.m_heap->data_int  << "      " << "Priority: " << priority(temp.m_heap) << endl;
    }
    else {
      cout << "DATA IS: " << temp.m_heap->data_string  << "      " << "Priority: " << priority(temp.m_heap) << endl;
    }
    //removeTop() this is how you get it to print the right way. 
  temp.removeTop();
  }
}
