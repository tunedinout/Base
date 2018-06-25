#ifndef HEAP_H
#define HEAP_H

//generic heap
template <class T>
class heap{
	private :
  int MAX_SIZE;
  int heap_size;
  int *priority;
  int *mapping_index;
  T **data;
  public :
  Heap(int maxSize,int heapSize);
  int getMaxSize();
  int getSize();
  int parent(int i);
  int left(int i);
  int right(int i);
  int getMax();
  
  
  //sinks down erroneous value
  void maxHeapify(int i);
  int extractMax();

  //increase to key && key > priority[i]
  // after this func call priority[i] = key
  //where key was bigger than priority[i]
  void increaseKey(int i,int key);


  void insertKey(int key,T *t);

  void print();
  
  void printHeapArray();
  T* getData(int i);
};








#endif