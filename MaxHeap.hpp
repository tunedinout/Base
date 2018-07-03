#ifndef __MAXHEAP_H_INCLUDED
#define __MAXHEAP_H_INCLUDED


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>
using namespace std;

//generic MaxHeap
template <class T>
class MaxHeap{
	private :

  //first key will be the priority
  //second will be pointer to the object associate with it
  vector<pair<int,T*>*> v;


  public :

  int getSize();
  int parent(int i);
  int left(int i);
  int right(int i);
  int getMin();


  //sinks down erroneous value
  //iterative version
  void maxHeapify(int i);
  //remove and return the max priority with the object
  pair<int,T*>* extractMax();

  //increase to key && key > priority[i]
  // after this func call priority[i] = key
  //where key was bigger than priority[i]
  void increaseKey(int i,int key);


  void insertKey(int key,T *t);

  void printHeapArray();

  void print();
  pair<int,T*>* getData(int i);
};
#endif
