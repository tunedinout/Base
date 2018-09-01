#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "MinHeap.hpp"
using namespace std;
void refer(int &t){
  t++;
  cout << " "<<t<<endl;
}
class node{
  public :
  int data ;
  node *next ;
  node(int data){
    this->data=data;
  }
};
node * func(int data){
  node *n = new node(data);
  n->next = new node(data+1);

  return n;
}
class Edge{
public:
  int dest;
  int src;
  int weight;
  Edge(int a,int b,int c){
    dest = b;src = a;weight = c;
  }
  //weightless EDGE
  Edge(int a,int b){
    dest = b;src = a;weight = 0;
  }

  void print(){
    cout << src <<" --->"<<dest<<" |"<<weight<<"| ";
  }
};
class lessThanEdge{
  public :
  inline bool operator()(Edge *edge1,Edge *edge2){
    return (edge1->weight < edge2->weight);
  }
};
int *arr;
void createArray(int size){
  int arr1[size];

  for (int i=0;i<size;i++)
  arr1[i] = -1;

  arr = arr1;
}
pair<int,Edge*>* bar(vector< pair<int,Edge*> > v){
  return &v[0];
}
int main(int argc, char const *argv[]) {
  //node *n = func(8);
  // cout << n->next->data << " ";
  //
  // vector <Edge*> edges;
  // edges.push_back(new Edge(0,1,8));
  // edges.push_back(new Edge(2,9,5));
  // edges.push_back(new Edge(1, 8,0));
  //
  // sort(edges.begin(),edges.end(),lessThanEdge());
  //
  // for(vector <Edge*>::iterator it = edges.begin() ;it!=edges.end();++it)
  //     cout << (*it) -> src << " "<<(*it) -> dest << " weight="<<(*it) -> weight << endl;
  // int size ;
  // cin >> size;
  // createArray(7);
  //
  // cout << arr[0] << endl;

  // vector<pair<int,Edge*>> v;
  // pair <int,Edge*> p;
  // p = make_pair(8,new Edge(5,6,7));
  // v.push_back(p);
  //
  //
  // cout <<v[0].first<<" "<<(v[0].second)->src << endl;
  //
  //
  // pair<int,Edge*>* p1 = bar(v);
  // cout << p1->first << endl;
  //
  // for(std::vector<pair<int,Edge*>>::iterator it = v.begin();it!=v.end();++it);
    MinHeap<Edge> minHeap;
    minHeap.insertKey(6,new Edge(4,5,5));


}
