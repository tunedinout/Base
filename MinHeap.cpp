#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>
using namespace std;

//generic MinHeap
template <class T>
class MinHeap{
	private :

  //first key will be the priority
  //second will be pointer to the object associate with it
  vector<pair<int,T*>*> v;


  public :

  int getSize(){
    return (int)v.size();
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
  int getMin(){
    if(v.size()==0){
      cout << "ERROR : No Elements in the MinHeap";
      exit(0);
    }
    return v[0]->first;
  }


  //sinks down erroneous value
  //iterative version
  void minHeapify(int i){
    int p = i,l,r;
    int least = 0;
    while(p<v.size()){
      l = left(p);r = right(p);

      if(l < v.size()&&v[l]->first < v[p]->first)
      least = l;
      else
      least = p;

      if(r < v.size()&& v[least]->first > v[r]->first)
      least = r;

      //exchange
      if(least!=p){
        pair<int,T*> * temp = new pair<int,T*> (v[p]->first,v[p]->second);
        v[p] = v[least];
        v[least] = temp;

        p = least;
      }else
      break;

    }

  }
  //remove and return the min priority with the object
  pair<int,T*>* extractMin(){
    pair<int,T*> *p;
    p = v[0];

    int size = v.size();
    pair<int,T*> *lastElement = v[size-1];
    v[0]=lastElement;
    v.resize(size-1);


    minHeapify(0);
    return p;
  }

  //increase to key && key > priority[i]
  // after this func call priority[i] = key
  //where key was bigger than priority[i]
  void decreaseKey(int i,int key){
    if(key > v[i]->first){
      cout <<"ERROR new key is greater than existing key." << endl;
      return;
    }

    //on decreasing the key the heap property for holds for its subtree
    //but not for it parents

    //it must be moved up to its right place
    v[i]->first = key;
    while(i >0 && v[i]->first < v[parent(i)]->first){
      //exchange with parents
      pair<int,T*> *temp = v[i];
      v[i] = v[parent(i)];
      v[parent(i)] = temp;
      i = parent(i);
    }
  }


  void insertKey(int key,T *t){
    v.push_back(new pair<int,T*>(INT_MAX,t));

    decreaseKey(v.size()-1,key);
  }

  void printHeapArray(){
    cout <<"Print MinHeap by priority and data------------------------"<<endl;
    //iteration require the typename
    // for( vector<pair<int,T*>>::iterator it = v.begin();it != v.end();++it){
    //   cout <<(*it)->first<<" "<<(*it)->second->print()<<endl;
    // }

    for(int i=0;i<v.size();i++)
    cout << v[i]->first<< " "<<(v[i]->second) ->print()<<endl;
    cout <<" ----------   xxxxxxxxxxxxxxxxxxxxxxxxxxxx -----------------"<<endl;
  }

  void print(){

      for(int i=0;i<v.size();i++){
        cout << v[i]->first <<" : ";

        if(left(i)  < v.size() )
          cout << v[left(i)]->first <<" ";

        if(right(i) < v.size())
          cout << v[right(i)]->second ;
        cout <<endl;
      }
  }
  pair<int,T*>* getData(int i){

    pair<int,T*>* temp = v[i];
    return temp;
  }
};
class Edge{
  public :
  int src;
  int dest;
  int weight;

  Edge(int a,int b,int c){
    src = a;dest = b; weight = c;
  }
  Edge(){}

    void print(){
    cout << src<<" ---> " << dest << " | "<<weight;
  }
};


int main(int argc, char const *argv[]) {
  MinHeap<Edge> minHeap;
  int size ;
  cin >> size;
  for(int i=0;i<size;i++){
    int src ,dest , weight;
    cin >> src >> dest >> weight;

    minHeap.insertKey(weight,new Edge(src,dest,weight));
  }

  int s = minHeap.getSize();
  for(int i=0;i<s;i++){
    pair <int,Edge*> *p = minHeap.extractMin();
    p->second->print();cout << endl;
  }


  return 0;
}
