#include <iostream>
#include <cstdio>
#include <cstdlib>
#define null NULL
using namespace std;
//generic heap 
class Heap{
  private :
  int MAX_SIZE;
  int heap_size;
  int *arr;
  public :
  Heap(int maxSize,int heapSize){
    MAX_SIZE = maxSize;
    heap_size = 0;
    arr = new int[maxSize];
  }
  int getMaxSize(){
    return MAX_SIZE;
  }
  int getSize(){
    return heap_size;
  }
  int parent(int i){
    return (i-1)/2;
  }
  int left(int i){
    return 2*i + 1;
  }
  int right(int i){
    return 2*i + 2;
  }
  int getMax(){
    return arr[0];
  }
  //sinks down erroneous value
  void maxHeapify(int i){

    int l = left(i),r = right(i);
    int largest = 0;
    if(l < heap_size && arr[l] > arr[i])
    largest = l;
    else
    largest = i;

    if(r < heap_size && arr[r] > arr[largest])
    largest = r;


    if(largest != i){
      int temp = arr[largest];
      arr[largest] = arr[i];
      arr[i] = temp;

      maxHeapify(largest);
    }
  }
  int extractMax(){
    int max = arr[0];
    arr[0] = arr[heap_size-1];
    heap_size--;
    maxHeapify(0);
    return max;
  }

  //increase to key && key > arr[i]
  // after this func call arr[i] = key
  //where key was bigger than arr[i]
  void increaseKey(int i,int key){
    if(key < arr[i]){
      cout <<"ERROR new key is smaller than current value" <<endl;
    }

    arr[i] = key;
    // here a call to max heapify can not be made maxHeapify
    //as maxHeapify assumes that the parent's left and right child
    //is greater
    //here the A[i]'s parent could be smaller
    //so to correct the tree we will go up and fix it

    while (i >=0 && arr[parent(i)] < arr[i]){
      int temp = arr[parent(i)];
      arr[parent(i)] = arr[i];
      arr[i] = temp;
      i = parent(i);
    }
    //it can be shown that above sync-up heapify is logarithmic
  }


  void insertKey(int key){
    heap_size++;
    arr[heap_size-1]=INT_MIN;
    increaseKey(heap_size-1,key);
  }

  void print(){
    for(int i=0;i<heap_size;i++){
      cout << arr[i] << ": ";
      if(left(i)<heap_size)
        cout<<arr[left(i)] << " ";


      if(right(i)<heap_size)
        cout << arr[right(i)];

      cout << endl;
    }
  }

};
int main(int argc, char const *argv[]) {
  Heap *heap = new Heap(100,0);
  int size;
  cin >> size;
  for(int i=0;i<size;i++){
    int a;
    cin >>  a;
    heap->insertKey(a);
  }
  heap->print();
  int max = heap -> extractMax();
  heap->print();
  return 0;
}
