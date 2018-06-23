#include <iostream>
#include <cstdio>
#include <cstdlib>
#define null NULL
using namespace std;

struct Edge{
  public :
  int src,dest;
};
struct Graph{
  public :
  int v,e;
  //array of edges
  Edge *edge;
};
Graph* create_graph(){
  int v,e;
  cin >> v >> e;
  Graph *graph = new Graph();
  graph -> v = v;
  graph -> e = e;

  //graph -> edge = new Edge[e];
  graph->edge = (Edge *)malloc(graph->e*sizeof(Edge));
  int a,b;
  int i = 0;
  while(i!=e){
    cin >> a >> b;
    //already initialised as empty edge types
    graph->edge[i].src = a;
    graph->edge[i].dest = b;
    i++;
  }
  return graph;
}
void printGraph(Graph *graph){
  cout << " ----------------------------- " << endl;
  for(int i = 0;i<graph->e;i++){
    cout << graph->edge[i].src << " "<< graph->edge[i].dest << endl;
  }
  cout << " ----------------------------- " << endl;
}
// --------------------------       /// -----------------
int parent[1000];
int Rank[1000];
void makeset(int n){
  for(int i=0;i<n;i++){
    parent[i]=-1;
    Rank[i]=0;
  }
}
int findSet(int x){
  if(parent[x]==-1)
  return x;
  else
   return findSet(parent[x]);
}
int findSetCompress(int x){
  if(parent[x]==-1)
  return x;
  else{
    parent[x] = findSetCompress(parent[x]);
    return parent[x];
  }
}
int Union(int x,int y){
  int x_set = findSet(x);
  int y_set = findSet(y);
  if(x_set!=y_set)
  parent[x_set] = y_set;
  return parent[x_set];
}
int UnionRank(int x,int y){
  int x_set = findSet(x);
  int y_set = findSet(y);

  if(x_set!=y_set){
    if(Rank[x_set] > Rank[y_set]){
      parent[y_set]=x_set;
      Rank[x_set]+=1;
    }else{
      parent[x_set]=y_set;
      Rank[y_set]+=1;
    }
  }
  return parent[x_set];
}
class node{
  public :
  int data;
  node* next ;
  node(int a){
    data = a;
    next = null;
  }

};
void insert(node **head,int data){
  if(*head == null){
    *head = new node(data);
  }else{
    node* temp = *head;
    while(temp->next != null){
      temp = temp -> next;
    }
    temp->next = new node(data);
  }
}
void printNode(node *head){
  node *temp = head;
  while(temp!=null){
    cout << temp->data << "----> ";
    temp = temp -> next ;
  }

  cout << endl;
}
//print all the sets
//prints the current state of the sets
//returns the tree representation of the current state
//of disjoint set
void printAllSets(int n){
  node **node_array = new node*[n];
  for(int i=0;i<n;i++){
    node_array[i] = new node(i);
  }
  for(int i=0;i<n;i++){
    if(parent[i]!=-1){
      int i_set = findSet(parent[i]);
      insert(&node_array[i_set],i);
    }
  }

  for(int i=0;i<n;i++)
      printNode(node_array[i]);
}
int main(int argc, char const *argv[]) {
  Graph *graph = create_graph();
  printGraph(graph);

  makeset(graph -> v);
  for(int i=0;i<graph->e;i++){
    UnionRank(graph->edge[i].src,graph->edge[i].dest);
  }
  printAllSets(graph->v);

  return 0;
}
