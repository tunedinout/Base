#include <iostream>
#include <cstdio>
#include <cstdlib>
#define null NULL
using namespace std;
//generic heap
template<class T>
class Heap{
  private :
  int MAX_SIZE;
  int heap_size;
  int *priority;
  int *mapping_index;
  T **data;
  public :
  Heap(int maxSize,int heapSize){
    MAX_SIZE = maxSize;
    heap_size = 0;
    priority = new int[maxSize];

    data = new T*[maxSize];
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
    return priority[0];
  }


  //sinks down erroneous value
  void maxHeapify(int i){

    int l = left(i),r = right(i);
    int largest = 0;
    if(l < heap_size && priority[l] > priority[i])
    largest = l;
    else
    largest = i;

    if(r < heap_size && priority[r] > priority[largest])
    largest = r;


    if(largest != i){
      int temp = priority[largest];
      priority[largest] = priority[i];
      priority[i] = temp;

      T *t = data[i];
      data[i] = data[largest];
      data[largest] = t;

      maxHeapify(largest);
    }
  }
  int extractMax(){
    int max = priority[0];
    priority[0] = priority[heap_size-1];
    data[0] = data[heap_size-1];


    heap_size--;
    maxHeapify(0);
    return max;
  }

  //increase to key && key > priority[i]
  // after this func call priority[i] = key
  //where key was bigger than priority[i]
  void increaseKey(int i,int key){
    if(key < priority[i]){
      cout <<"ERROR new key is smaller than current value" <<endl;
    }

    priority[i] = key;
    // here a call to max heapify can not be made maxHeapify
    //as maxHeapify assumes that the parent's left and right child
    //is greater
    //here the A[i]'s parent could be smaller
    //so to correct the tree we will go up and fix it

    while (i >=0 && priority[parent(i)] < priority[i]){
      int temp = priority[parent(i)];
      priority[parent(i)] = priority[i];
      priority[i] = temp;



      T *t = data[i];
      data[i] = data[parent(i)];
      data[parent(i)] = t;
      i = parent(i);
    }
    //it can be shown that above sync-up heapify is logarithmic
  }


  void insertKey(int key,T *t){
    heap_size++;
    priority[heap_size-1]=INT_MIN;
    data[heap_size-1] = t;
    increaseKey(heap_size-1,key);
  }

  void print(){
    for(int i=0;i<heap_size;i++){
      cout << priority[i] << ": ";
      if(left(i)<heap_size)
        cout<<priority[left(i)] << " ";


      if(right(i)<heap_size)
        cout << priority[right(i)];

      cout << endl;
    }
  }

  void printHeapArray(){
    cout << " ------ Priority array ------------------- "<<endl;
        for(int i=0;i<heap_size;i++){
          cout <<"priority["<<i<<"] ="<<priority[i]<<endl;
        }

        cout <<"  ------------------------------------------ "<<endl;
  }
  T* getData(int i){
    T *x  = data[i];
    x->print();
    cout << endl;
    return x;
  }
};

class EDGE{
public:
  int dest;
  int src;
  int weight;
  EDGE(int a,int b,int c){
    dest = b;src = a;weight = c;
  }
  //weightless EDGE
  EDGE(int a,int b){
    dest = b;src = a;weight = 0;
  }
  EDGE(){

  }
  void print(){
    cout <<src <<"-----> " <<dest<<" | "<<weight<<" |";
  }
};


int main(int argc, char const *argv[]) {
  Heap <EDGE>* pq = new Heap<EDGE>(100,0);

  EDGE *edge ;
  int src,dest,weight;
  int edgeNo ;
  cin >> edgeNo;
  for(int i=0;i<edgeNo;i++){

    cin >> src >> dest >> weight;
    edge = new EDGE(src,dest,weight);
    pq->insertKey(weight,edge);
  }
  pq->print();

  pq->printHeapArray();
  int s_heap = pq->getSize();
  for(int i=0;i<s_heap;i++){
    edge = pq->getData(0);
    cout << " The max edge is " ;
    edge->print();
    cout << endl;
    pq->extractMax();

    /*pq->print();

    pq->printHeapArray();*/
  }





  /*Heap *heap = new Heap(100,0);
  int size;
  cin >> size;
  for(int i=0;i<size;i++){
    int a;
    cin >>  a;
    heap->insertKey(a);
  }
  heap->print();
  int max = heap -> extractMax();
  heap->print();*/
  return 0;



}
