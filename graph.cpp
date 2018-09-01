#include <iostream>
#include <stack>
#include <queue>
#include <forward_list>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>
#define null NULL
using namespace std;
template <typename T>
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
class graph_node{
public:
	int data;
	//default added weight = 0
	int weight;
	graph_node* next;
	graph_node(int d,int w){
		data = d;
		weight = w;
		next = NULL;
	}
};
class graph{
	public:
		int v;
	graph_node **adj;
	graph(int V){
		v=V;
		adj = new graph_node*[v];

		for(int i=0;i<v;i++){
			adj[i]=new graph_node(i,0);
		}
	}
	//in both the functions the assumption is
	// adding edge is done to existing vertices
	void addEdge(int v,int u);
	void addEdge(int v,int u,int weight);


};

int countEdges(graph *g){
	int edges = 0;
	for(int i=0;i<g->v;i++){
		graph_node *temp = g->adj[i]->next;
		while(temp!=null){
			edges++;
			temp = temp -> next;
		}
	}
	return edges;
}
void graph::addEdge(int v,int u){
	graph_node* temp = adj[v];
	while(temp->next!=NULL)
	temp=temp->next;
	temp->next=new graph_node(u,0);
}
void graph::addEdge(int v,int u,int weight){
	graph_node* temp = adj[v];
	while(temp->next!=NULL)
	temp=temp->next;
	temp->next=new graph_node(u,weight);
}
void printGraph(graph *g){
	for(int i=0;i<g->v;i++){
		graph_node *temp = g->adj[i]->next;
		cout<<"[ "<<g->adj[i]->data<<" ] -> ";
		while(temp!=NULL){
			cout<<"( "<<temp->data<<" )--";
			temp=temp->next;
		}
		cout<<endl;
	}
}
void insert_graph(graph **g){
	int vertices;
	cin>>vertices;

	//vertices will be from 0 to vertices-1
	*g = new graph(vertices);
	int a,b;
	cin>>a>>b;

	while(a!=-1){
		(*g)->addEdge(a,b);
		cin>>a>>b;
	}

}
void insert_digraph(graph **g){
	int vertices;
	cin>>vertices;

	//vertices will be from 0 to vertices-1
	*g = new graph(vertices);
	int a,b;
	cin>>a>>b;

	while(a!=-1){
		(*g)->addEdge(a,b);
		(*g)->addEdge(b,a);
		cin>>a>>b;
	}
}
void insert_digraph_weighted(graph **g){
	int vertices;
	cin>>vertices;

	//vertices will be from 0 to vertices-1
	*g = new graph(vertices);
	int a,b,c;
	cin>>a>>b>>c;

	while(a!=-1){
		(*g)->addEdge(a,b,c);
		(*g)->addEdge(b,a,c);
		cin>>a>>b>>c;
	}
}
void print_digraph_weighted(graph *g){
	cout << endl;
	cout << "_________________________________________________________________"<<endl;;

	for(int i=0;i<g->v;i++){
		int u = i;
		graph_node *temp = g->adj[i]->next;
		while(temp!=NULL){
			int v = temp ->data;
			int w = temp ->weight;
			if(u<v)
			cout << u << " "<<v<<" "<<w<<endl;
			temp = temp -> next ;
		}
	}
	cout << "_________________________________________________________________"<<endl;
}
void insert_graph_weighted(graph **g){
	int vertices;
	cin>>vertices;

	//vertices will be from 0 to vertices-1
	*g = new graph(vertices);
	int a,b,c;
	cin>>a>>b>>c;

	while(a!=-1){
		(*g)->addEdge(a,b,c);
		cin>>a>>b>>c;
	}
}
//v is the starting vertex of the graph
void BFS(graph *g,int v){
	bool ifvisited[g->v];

	for(int i=0;i<g->v;i++)
		ifvisited[i]=false;
	queue <graph_node *> q;
	q.push(g->adj[v]);
	graph_node *current = NULL,*temp = NULL;
	while(!q.empty()){
		current = q.front();q.pop();
		if(ifvisited[current->data])
			continue;
		else
			ifvisited[current->data]=true;
		cout<<current->data<<" ";
		//below line is untested
		if(g->adj[current->data]->next!=NULL)
			temp = g->adj[current->data]->next;
		else
			continue;

		while(temp!=NULL){
			if(!ifvisited[temp->data])
				q.push(temp);
			temp=temp->next;
		}
	}
	cout<<endl;
}
void bfsCLRS(graph *g,int s){
	char color[g->v];
	int  distance[g->v];
	int parent[g->v];

	for(int i=0;i<g->v;i++){
		color[i] = 'W';
		distance[i] = 0;
		parent[i] = -1;
	}

	color[s] = 'G';
	distance[s] = 0;
	parent[s]=-1;

	queue <int> q;
	q.push(s);

	while(!q.empty()){
		int u = q.front();q.pop();
		graph_node *temp = g->adj[u];
		while(temp->next != null){
			int v = temp->next->data;
			if(color[v]=='W'){
				color[v] = 'G';
				distance[v] = distance[u]+1;
				parent[v] = u;
				q.push(v);

			}
			color[u] = 'B';
		}
	}

	for(int i=0;i<g->v;i++){
		cout <<" [ distance["<<i<<"] = "<<distance[i] << "";
	}
	cout <<endl;

}
//processes the visited nodes directly
//DS required
//addition and removal of elements from
//the front of the list
enum edgeType{
	tree,back,forwardCross,invalid
};
class Edge{
	public :
	int src;
	int dest;
	edgeType eT;
	Edge(int a,int b,edgeType e){
		src = a;dest = b;eT = e;
	}
	Edge(){}
};
void dfsCLRS_iterative1(graph *g,int s,int finishTime[],int startTime[],int color[],int &timeStamp){


	stack<int> st;
	color[s]='G';
	startTime[s]=timeStamp++;
	st.push(s);

	while (!st.empty()) {
		int u = st.top();
		if(color[u]=='G'){
			graph_node *temp = g->adj[u]->next;
			//add to the stack
			bool ifNone = true;
			while(temp!=null){

				if(color[temp->data]=='W'){
					st.push(temp->data);
					color[temp->data] = 'G';
					startTime[temp->data] = timeStamp++;
					ifNone = false;

				}
				temp = temp -> next;
			}
			if(ifNone == true){
				color[u]='B';
			}

		}else{
			if(color[st.top()]=='G')
			cout << "ERROR" << endl;
			//color = black
			finishTime[st.top()]=timeStamp++;
			cout << st.top() << " ";
			st.pop();
		}
	}

	color[s]='B';



}
//give wrong output for the type of edge
void dfsCLRS_iterative(graph *g){
	int finishTime[g->v];
	int startTime[g->v];
	int color[g->v];
	int timeStamp = 0;
	for(int i=0;i<g->v;i++){
		finishTime[i]=-1;
		startTime[i]=-1;
		color[i]='W';
	}
	int c_edge = countEdges(g);
	Edge *edges[c_edge];
	for(int i=0;i<c_edge;i++){
		edges[i] = NULL;
	}
	int edgeIndex = 0;
	for(int i=0;i<g->v;i++)
		if(color[i]=='W')
			dfsCLRS_iterative1(g,i,finishTime,startTime,color,timeStamp);

	cout << endl;
	for(int i=0;i<g->v;i++){
		cout <<"finishTime[" <<i<<"] = "<<finishTime[i] << " ";
	}
	cout << endl;

	cout << endl;
	for(int i=0;i<g->v;i++){
		cout <<"startTime[" <<i<<"] = "<<startTime[i] << " ";
	}
	cout << endl;



	for(int i=0;i<g->v;i++){
		int u = i;
		graph_node *temp = g->adj[i]->next;
		while(temp!=null){

			int v = temp->data;

			//tree edge
			if(startTime[u] < startTime[v] &&finishTime[v] < finishTime[u])
			edges[edgeIndex++]=new Edge(u,v,tree);
			//back edge
			else if(startTime[v] < startTime[u]&&finishTime[u] < finishTime[v])
			edges[edgeIndex++] = new Edge(u,v,back);

			else if(finishTime[v] < startTime[u])
			edges[edgeIndex++] = new Edge(u,v,forwardCross);
			temp = temp -> next;
		}
	}




	for(int i=0;i<edgeIndex;i++){

		cout << edges[i]->src << " "<<edges[i]->dest <<" ";
		switch (edges[i]->eT) {
			case 0:
			cout << "tree Edge";
			break;
			case 1:
			cout << "back Edge";
			break;
			case 2:
			cout << "forward or cross Edge";
			break;
			default:
			cout << "INVALID EDGE";
		}
		cout << endl;

	}
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
  int x_set = findSetCompress(x);
  int y_set = findSetCompress(y);

  if(x_set!=y_set){
    if(Rank[x_set] > Rank[y_set]){
      parent[y_set]=x_set;
      Rank[x_set]+=1;
    }else{
      parent[x_set]=y_set;
      Rank[y_set]+=1;
    }
  }
  return findSetCompress(x);
}

////////////////////////////////////////////////////
//using the color metrics as in CLRS
void connectedComponentsCLRSDfs(graph *g,int dfsArray[]){
	int color[g->v];
	for(int i=0;i<g->v;i++){
		dfsArray[i] = -1;
		color[i]='W';
	}
	int dfs_itr  = 0;

	for(int i = 0;i<g->v;i++){
		int s = i;

		if(color[s]=='W'){

			stack <int> st;
			st.push(s);
			color[s]='G';

			while(!st.empty()){
				int u = st.top();
				if(color[u]=='G'){

					graph_node *temp = g->adj[u]->next;
					bool ifNone = true;
					while(temp!=null){
						int v = temp->data;

						if(color[v]=='W'){
							color[v]='G';
							ifNone = false;
							st.push(v);
						}
						temp = temp->next;
					}
					if(ifNone == true){
						color[u]='B';
					}

				}else{
					//color = black
					dfsArray[dfs_itr++]=st.top();
					st.pop();
				}
			}

		}

	}

}
void DFS(graph *g , int dfsArray[]){
	bool ifAdded[g->v];
	for(int i=0;i<g->v;i++)
		ifAdded[i]=false;
	int dfs_itr = 0;
	for(int i=0;i<g->v;i++){
		if(ifAdded[i]==true)
		continue;

		ifAdded[i]=true;
		stack <int> st;st.push(i);

		while (!st.empty()){
			bool ifNone = true;
			int u = st.top();
			graph_node *temp = g->adj[u]->next;

			while(temp!=null){
				int v = temp->data;
				if(!ifAdded[v]){
					ifAdded[v]=true;
					ifNone = false;
					st.push(v);
				}
				temp = temp->next;
			}

			if(ifNone){
				dfsArray[dfs_itr++]=st.top();
				st.pop();
			}


		}
	}
}
void mergeSort(int arr[],int p,int r,int q,int reverseArr[]){
	//total elements
	int n = q-p+1,n1 = (r - p) +1,n2 = q - (r+1) + 1;
	int aux1[n1+1],j=0;
	int aux2[n2+1],k=0;
	int auxRev1[n1];
	int auxRev2[n2];

	for(int i=p;i<=r;i++){
		aux1[j++]=arr[i];
		auxRev1[j-1]=reverseArr[i];
	}

	for(int i=r+1;i<=q;i++){
		aux2[k++]=arr[i];
		auxRev2[k-1]=reverseArr[i];
	}


		aux1[n1]=INT_MAX;
		aux2[n2]=INT_MAX;

	j=0;k=0;


	for(int i=p;i<=q;i++){
		if(aux1[j] <= aux2[k]){
			arr[i] = aux1[j++];
			reverseArr[i]=auxRev1[j-1];
		}else{
			arr[i] = aux2[k++];
			reverseArr[i]=auxRev2[k-1];
		}
	}


}
void sort(int arr[],int p,int q,int reverseArr[]){
	if(p<q){
		int m = (p + q )/2;
		sort(arr,p,m,reverseArr);
		sort(arr,m+1,q,reverseArr);
		mergeSort(arr,p,m,q,reverseArr);
	}
}
//the array reverseArr contains the current position of
//all the elements in sorted levelOrder
//viz reverseArr[i]=j; where j is an element in arr
//and i is its index in sorted array arr
void sortedElements(int arr[],int n,int reverseArr[]){
	sort(arr,0,n-1,reverseArr);


	for(int i=0;i<n;i++)
		cout << "arr["<<i<<"]=" << arr[i] << " " << "reverseArr["<<i<<"]=" << reverseArr[i] << endl;
}
graph* connectedComponentsTranspose(graph *g){
	graph *transpose = new graph(g->v);
	for(int i=0;i<g->v;i++){
		int v = i;
		graph_node *temp = g->adj[i]->next;
		while(temp!=NULL){
			int u = temp->data;
			transpose->addEdge(u,v);
			temp = temp->next;
		}
	}
	return transpose;
}

void connectedComponents(graph *g){
int dfsArray[g->v];
for(int i=0;i<g->v;i++)
dfsArray[i]=-1;


DFS(g,dfsArray);
graph *transpose = connectedComponentsTranspose(g);
//initalise vertices as the connectedComponents
//initally all the vertices are trivially consider them as connectedComponents
cout << endl;
//printGraph(transpose);
makeset(transpose->v);
//need a list of graph_node in increasing order
//graph_node as linked list node


//visit in increasing order
bool ifAdded[g->v];
for(int i=0;i<g->v;i++)
	ifAdded[i]=false;


	for(int i=g->v-1;i>=0;i--){
		int u = dfsArray[i];
		if(ifAdded[u])
		continue;

		stack <int>st;st.push(u);
		ifAdded[u]=true;

		while(!st.empty()){
			int x = st.top();
			graph_node *temp = transpose->adj[x]->next;
			bool none = true;
			while(temp!=NULL){
				int y = temp -> data;
				if(!ifAdded[y]){
					ifAdded[y]=true;
					none = false;
					st.push(y);

					if(findSetCompress(x)!=findSetCompress(y))
								UnionRank(x,y	);
				}
				temp = temp ->next;
			}
			if(none){
				st.pop();
			}
		}
	}



for(int i=0;i<g->v;i++)
	cout << "parent["<<i<<"]=" << parent[i] << endl;

}
void GenericMST(graph *g){
	makeset(g->v);
}
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
	void print(){
		cout << src << " ---> "<<dest << " |"<<weight<<" |";
	}
};
class lessThanEDGE{
  public :
  inline bool operator()(EDGE *edge1,EDGE *edge2){
    return (edge1->weight < edge2->weight);
  }
};

void MSTKruskal(graph *g){
	makeset(g->v);

	vector <EDGE*> edges;
	vector <EDGE*> MSTEdgeSET;
	for(int i=0;i<g->v;i++){
		int u = i;
		graph_node *temp = g->adj[i]->next;
		while(temp!=NULL){
			int v = temp->data;
			int w = temp->weight;
			if(u<v)
			edges.push_back(new EDGE(u,v,w));
			temp = temp -> next;
		}
	}

	sort(edges.begin(),edges.end(),lessThanEDGE());

	for(vector<EDGE*>::iterator it = edges.begin(); it !=edges.end();++it){
		if(findSetCompress((*it)->src)!=findSetCompress((*it)->dest)){
				UnionRank((*it)->src,(*it)->dest);
				MSTEdgeSET.push_back(new EDGE((*it)->src,(*it)->dest,(*it)->weight));
			}
	}

	for(vector <EDGE*>::iterator it = MSTEdgeSET.begin() ;it!=MSTEdgeSET.end();++it)
      cout << (*it) -> src << " "<<(*it) -> dest << " weight="<<(*it) -> weight << endl;
	//create the MST



}
void MSTPrims(graph *g){
		//since we are finding minimum spanning tree
		//it is a fact that this graph will be connected

		//stuck at the commented
		//once the key value is decreased for a vertex
		//the index of the vertex in the minHeap is not known

		int key[g->v];bool inHeap[g->v];
		key[0] = 0;
		inHeap[0]=true;
		for(int i=1;i<g->v;i++){
			key[i]=INT_MAX;
			inHeap[i]=true;
		}
		vector<EDGE*> mstEdges;
		int prev = -1;


		MinHeap<int> minHeap;
		for(int i=0;i<g->v;i++){
			minHeap.insertKey(key[i],new int(i));
		}

		while(minHeap.getSize()!=0){
			pair<int,int*> *p = minHeap.extractMin();
			int u = *(p->second);

			if(prev!=-1)
				mstEdges.push_back(new EDGE(prev,u,key[u]));
			prev = u;
			inHeap[u]=false;

			graph_node * temp = g->adj[u]->next;
			while(temp!=null){
				int v = temp->data;
				int edgeWeight = temp->weight;
				if(edgeWeight < key[v]&&inHeap[v]){
					key[v] = edgeWeight;
				//	minHeap.decreaseKey()
				}

			}
		}
		cout <<"----------------- MST Edges in order they were visted by prims ----------------"<<endl;
		for(vector<EDGE*>::iterator it = mstEdges.begin();it!=mstEdges.end();it++){
			(*it) -> print();
			cout << endl;
		}

		cout << " ------------- xxxxxxxxxxxxxxxxxxxxxxxxxxxx ----------------------------------"<<endl;
}
//ifAdded = if added in the list
void DFS_postorder(graph *g,int v){
	bool ifAdded[g->v]  ;
	for(int i=0;i<g->v;i++)
		ifAdded[i] = false;

	stack <graph_node *> st;
	st.push(g->adj[v]);ifAdded[g->adj[v]->data] = true;

	while(!st.empty()){
		graph_node * current = st.top();

		graph_node *temp = g->adj[current->data]->next;
		bool allVisited = true;
		while(temp != null)
			if(!ifAdded[temp->data]){
				st.push(temp);
				ifAdded[temp -> data] = true;
				temp = temp -> next;
				allVisited = false;
			}else
				temp = temp -> next;

		if(allVisited ){
			cout << current -> data << " ";st.pop();
		}

	}
	cout << endl;
}
//processes the last visited nodes
//first
void DFS_preorder(graph *g,int v){
	bool ifAdded[g->v]  ;
	for(int i=0;i<g->v;i++)
		ifAdded[i] = false;

	stack <graph_node *> st;
	st.push(g->adj[v]);ifAdded[g->adj[v]->data] = true;

	while(!st.empty()){
		graph_node * current = st.top();st.pop();
		cout << current -> data << " ";

		graph_node *temp = current->next;

		while(temp != null)
			if(!ifAdded[temp->data]){
				st.push(temp);
				ifAdded[temp -> data] = true;
				temp = temp -> next;
			}else
				temp = temp -> next;



	}
	cout << endl;
}

//TOPOLOGICAL SORT
//Implementation of KHAN'S ALGORITHM
void toposort_khans(graph *g,forward_list <int> *f){


	int in_count[g->v];
	for(int i=0;i<g->v;i++)
		in_count[i]=0;
	for(int i=0;i<g->v;i++){
		graph_node *temp;
		if(g->adj[i]->next != NULL)
			temp = g->adj[i]->next;
		else
			continue;

		while(temp!=NULL){
			in_count[temp->data]++;
			temp=temp->next;
		}
	}

	queue <graph_node *> count_0_set;

	for(int i=0;i<g->v;i++){
		if(in_count[i]==0)
			count_0_set.push(g->adj[i]);
	}
	graph_node *current = NULL,*temp = NULL;
	forward_list <int> ::iterator it;

	while(!count_0_set.empty()){
		current = count_0_set.front();count_0_set.pop();

		if(f->empty()){
			f->push_front(current->data);
			it = f->begin();
		}
		else
			it = f->emplace_after(it,current->data);

		if(g->adj[current->data]->next!=NULL)
			temp = g->adj[current->data]->next;
		else
			continue;

		while(temp!=NULL){
			in_count[temp->data]--;
			if(in_count[temp->data]==0)
				count_0_set.push(temp);
			temp = temp->next;
		}

	}

	for(int i=0;i<g->v;i++){
		if(in_count[i]!=0){
			cout<<"The graph is not a DAG"<<endl;
			return;
		}
	}
}
void toposort_dfs_no_markings_helper(graph *g,forward_list <int> *f,bool visited[],bool added[],int vertex){
	if(visited[vertex]&&added[vertex])
		return;

	if(visited[vertex]&&!added[vertex]){
		cout<<"The graph is not DAG";
		exit(0);
	}

	visited[vertex] = true;
	graph_node *temp = g->adj[vertex];

	while(temp->next!=NULL){
		toposort_dfs_no_markings_helper(g,f,visited,added,temp->next->data);
		temp=temp->next;
	}

	added[vertex]=true;
	f->push_front(g->adj[vertex]->data);
	return;
}
//helper function of toposort_dfs
void toposort_dfs_no_markings(graph *g){
	forward_list<int> *f = new forward_list<int>();
	bool visited[g->v],added[g->v];
	for(int i=0;i<g->v;i++){
		visited[i]=false;added[i]=false;
	}
	for(int i=0;i<g->v;i++){
		if(!visited[i]&&!added[i])
			toposort_dfs_no_markings_helper(g,f,visited,added,i);
	}
	for(auto it=f->begin();it!=f->end();it++)
		cout<<*it<<" ";
	cout<<endl;

}
void visit_recursive(graph *g,forward_list <graph_node *> *f,char mark[],int vertex){
	if(mark[vertex]=='p')
		return;

	if(mark[vertex]=='t'){
		cout<<"The graph is not DAG";
		exit(0);
	}

	mark[vertex] = 't';
	graph_node *temp = g->adj[vertex];

	while(temp->next!=NULL){
		visit_recursive(g,f,mark,temp->next->data);
		temp=temp->next;
	}

	mark[vertex]='p';
	f->push_front(g->adj[vertex]);
	return;
}
void visit_iterative(graph *g,forward_list<graph_node *> *f,char mark[],int vertex){

	 graph_node * temp = NULL,*current = NULL;
	 stack <graph_node *> st;
	 forward_list <graph_node *> ::iterator it;
	 st.push(g->adj[vertex]);
	 mark[vertex]='t';



	 while(!st.empty()){
	 	cout<<" h "<<endl;
	 	current = st.top();st.pop();
	 	if(current->data == vertex){
	 		f->push_front(current);
	 		it = f->begin();
	 		mark[current->data]='p';
	 	}else{
	 		it = f->emplace_after(it,current);
	 		mark[current->data]='p';
	 	}

	 	temp = g->adj[current->data];
	 	while(temp->next!=NULL){
	 		if(mark[temp->next->data]=='t'){
	 			cout<<"The graph is not a DAG";
	 			exit(0);
	 		}
	 		else if (mark[temp->next->data]=='p'){
	 			temp = temp->next;
	 			continue;
	 		}
	 		st.push(temp->next);

	 		mark[temp->next->data]='t';
	 		temp=temp->next;

	 	}
	 }
}
void toposort_dfs(graph *g,forward_list <graph_node *> *f){
	//unmarked nodes
	//node can be unmarked, temporary and permanent
	//using a character array for storing this information

	char mark[g->v];
	for(int i=0;i<g->v;i++)
		mark[i] = 'u';

	for(int i=0;i<g->v;i++){
		if(mark[i]=='u')
			visit_iterative(g,f,mark,i);
		else
			continue;

	}


}

//
bool checkIfGraphHasLoops(graph *g){
	bool ifVisited[g->v];
	for(int i=0;i<g->v;i++)
		ifVisited[i]=false;
	for(int i=0;i<g->v;i++){
		if(ifVisited[i]==true)
			return true;
		stack <graph_node *> ds;
		ds.push(g->adj[i]);

		while(!ds.empty()){
			graph_node * current = ds.top();ds.pop();
			if(ifVisited[current->data]==true)
				return true;
			else
				ifVisited[current->data]=true;

			graph_node *temp = current -> next;
			while(temp!=null){
				ds.push(temp);
				temp = temp -> next ;
			}
		}
	}

	return false;
}
bool checkIfGraphHasLoops_tsort(graph *g){
	int visitedNodes = 0;
	queue <graph_node *> q;
	int inEdges[g->v];
	for(int i=0;i<g->v;i++){
		inEdges[i]=0;
	}

	for(int i=0;i<g->v;i++){
		graph_node *temp = g->adj[i]->next;
		while(temp!=null){
			inEdges[temp->data]++;
			temp = temp -> next;
		}
	}

	for(int i=0;i<g->v;i++)
		if(inEdges[i]==0)
			q.push(g->adj[i]);

	while(!q.empty()){
		graph_node *current = q.front();q.pop();

		//cout << current -> data << " ";
		visitedNodes++;
		graph_node *temp = g->adj[current->data]->next;
		while(temp!=null){
			inEdges[temp->data]--;
			if(inEdges[temp->data]==0)
				q.push(temp);
			temp = temp -> next;

		}
	}

	if(visitedNodes < g->v )
	return true;
	else
		return false;

}
void toposort_dfs1(graph *g){

	//check if the graph has loops
	if(checkIfGraphHasLoops(g)){
		cout << "The graph is cyclic " << endl;
		return;
	}

	int visitedNodes = 0;
	queue <graph_node *> q;
	int inEdges[g->v];
	for(int i=0;i<g->v;i++){
		inEdges[i]=0;
	}

	for(int i=0;i<g->v;i++){
		graph_node *temp = g->adj[i]->next;
		while(temp!=null){
			inEdges[temp->data]++;
			temp = temp -> next;
		}
	}

	for(int i=0;i<g->v;i++)
		if(inEdges[i]==0)
			q.push(g->adj[i]);

	while(!q.empty()){
		graph_node *current = q.front();q.pop();

		cout << current -> data << " ";
		visitedNodes++;
		graph_node *temp = g->adj[current->data]->next;
		while(temp!=null){
			inEdges[temp->data]--;
			if(inEdges[temp->data]==0)
				q.push(temp);
			temp = temp -> next;

		}
	}

	if(visitedNodes < g->v )
		cout << " ERROR : The graph has loops" << endl;
	return;

}

class tp_node{
public:
	int value;
	forward_list <tp_node*> *list;
	bool visited;
	tp_node(int v){
		value = v;
		visited = false;
		list = new forward_list<tp_node*>();
	}
};

//function to generate all possible toposort
void toposort_all(graph *g){
	//to check if the graph is DAG or not
	toposort_khans(g,new forward_list<int>());
	int in_count[g->v];
	for(int i=0;i<g->v;i++){
		in_count[i]=0;
	}
	for(int i=0;i<g->v;i++){
		graph_node *temp;
		if(g->adj[i]->next != NULL)
			temp = g->adj[i]->next;
		else
			continue;

		while(temp!=NULL){
			in_count[temp->data]++;
			temp=temp->next;
		}
	}

	bool visited[g->v];
	for(int i=0;i<g->v;i++)
		visited[i]=false;
	tp_node* path_array[g->v];
	int end = 0;
	tp_node* root = new tp_node(-1);
	tp_node *current = root;

	for(int i=0;i<g->v;i++){
		if(in_count[i]==0&&visited[i]==false){
			current->list->push_front(new tp_node(i));
		}
	}

	while(end!=-1){
		if(current->list->empty()){
			if(end == g->v){
				for(int i=0;i<end;i++)
					cout<<path_array[i]->value<<" ";
				cout<<endl;
				//last node will have an empty list
			}
			end--;
			if(end>0)
				current = path_array[end-1];
			else
				current = root;
		}else{
			tp_node *c = current->list->front();
			if(c->visited == false){
				c->visited = true;
				visited[c->value] = true;
				graph_node *temp = g->adj[c->value];
				while(temp->next!=NULL){
					in_count[temp->next->data]--;
					temp = temp->next;
				}
				path_array[end]=c;
				end++;
				current = c;
				for(int i=0;i<g->v;i++){
					if(in_count[i]==0&&visited[i]==false){
						current->list->push_front(new tp_node(i));
					}
				}
			}else{
				current->list->pop_front();
				visited[c->value]=false;
				graph_node *temp = g->adj[c->value];
				while(temp->next!=NULL){
					in_count[temp->next->data]++;
					temp = temp->next;
				}
				//do not change current as it may have other chldren
			}
		}
	}
}
//in the above function in the while loop
//every time the whole set of graph vertices is iterated over
//an ideal algo should only visit those nodes that have incount=0and visited=false
//In this function above issue is covered
//but an extrea boolean array is used
//as when back tracking and remove an element from current->list
//we add to the visitable_nodes list
//but while removing elements
//already present vertex's incount is increased
//if removed vertex has this vertex as adjacent nodes,
// and sometime later this incount might come to zero.
//when that happens the algo tries to add the vertex again
//the boolean array (added_to_visitable_nodes)helps to prevent this
//i.e if it is already in the list of visitable nodes
//we donot added it.

void toposort_all_efficient(graph *g){
	//to check if the graph is DAG or not
	toposort_khans(g,new forward_list<int>());
	int in_count[g->v];
	for(int i=0;i<g->v;i++){
		in_count[i]=0;
	}
	for(int i=0;i<g->v;i++){
		graph_node *temp;
		if(g->adj[i]->next != NULL)
			temp = g->adj[i]->next;
		else
			continue;

		while(temp!=NULL){
			in_count[temp->data]++;
			temp=temp->next;
		}
	}

	bool visited[g->v];bool added_to_visitable_nodes[g->v];
	for(int i=0;i<g->v;i++){
		visited[i]=false;
		added_to_visitable_nodes[i]=false;
	}
	tp_node* path_array[g->v];
	int end = 0;
	tp_node* root = new tp_node(-1);
	tp_node *current = root;
	forward_list<int> visitable_nodes;
	for(int i =0;i<g->v;i++)
		if(in_count[i]==0&&visited[i]==false){
			visitable_nodes.push_front(i);
			added_to_visitable_nodes[i]=true;
		}
	for(auto it=visitable_nodes.begin();it!=visitable_nodes.end();it++)
		current->list->push_front(new tp_node(*it));


	while(end!=-1){
		if(current->list->empty()){
			if(end == g->v){
				for(int i=0;i<end;i++)
					cout<<path_array[i]->value<<" ";
				cout<<endl;
				//last node will have an empty list
				/*visitable_nodes.push_front(path_array[end-1]->value);
				visited[path_array[end-1]->value]=false;*/
			}
			end--;
			//push path_array[end] in the visitable nodes

			if(end>0)
				current = path_array[end-1];
			else
				current = root;
		}else{
			tp_node *c = current->list->front();
			if(c->visited == false){
				c->visited = true;
				visited[c->value] = true;
				graph_node *temp = g->adj[c->value];
				while(temp->next!=NULL){
					in_count[temp->next->data]--;
					if(in_count[temp->next->data]==0&&added_to_visitable_nodes[temp->next->data]==false){
						visitable_nodes.push_front(temp->next->data);
						added_to_visitable_nodes[temp->next->data]=true;
					}
					temp = temp->next;
				}
				path_array[end]=c;
				end++;
				current = c;

				for(auto it=visitable_nodes.begin(),it_prev=visitable_nodes.begin();it!=visitable_nodes.end();){
					if(visited[*it]==false&&in_count[*it]==0){
						current->list->push_front(new tp_node(*it));
						it_prev = it;
						it++;
					}else{
						//remove this element from this list
						added_to_visitable_nodes[*it]=false;
						if(it == visitable_nodes.begin()){
							//pop front and set it to the next element
							visitable_nodes.pop_front();
							it = visitable_nodes.begin();
							it_prev = it;
						}else{
							auto it1=it;it1++;
							visitable_nodes.erase_after(it_prev,it1);
							it = it1;
							//it_prev will not change
						}
					}
				}


			}else{
				current->list->pop_front();
				visited[c->value]=false;
				visitable_nodes.push_front(c->value);
				added_to_visitable_nodes[c->value]=true;
				graph_node *temp = g->adj[c->value];
				while(temp->next!=NULL){
					in_count[temp->next->data]++;
					temp = temp->next;
				}
				//do not change current as it may have other chldren
			}
		}
	}
}

void find_longest_path_source_to_vertex(graph *g,int source){
	forward_list<int> *f = new forward_list<int>();
	toposort_khans(g,f);
	int dist[g->v];
	for(int i=0;i<g->v;i++){
		if(i==source)
			dist[source]=0;
		else
			dist[i]=INT_MIN;
	}
	for(auto it = f->begin();it!=f->end();it++){
		int c = *it;
		graph_node *temp = g->adj[c];
		while(temp->next != NULL){
			if(temp->next->weight + dist[c] > dist[temp->next->data])
				dist[temp->next->data] = temp->next->weight + dist[c];
			temp=temp->next;
		}

	}

	for(int i=0;i<g->v;i++)
		cout<<"dist[ "<<i<<" ] = "<<dist[i]<<endl;


}
//returns mother vertex of a graph
//mother vertex is the vertex which has a path
// to every other vertex
//helper function that does dfs on a vertex
// and marks the vertices visited
// and increases count every time mark is made
//uses if added condition on visited array
void dfs_visit(graph *g,int source,bool visited[],int *count){
	queue<int> q;
	q.push(source);

	while(q.empty() == false){
		int current = q.front();q.pop();

		graph_node *temp = g->adj[current];
		while(temp->next!=NULL){
			if(visited[temp->next->data]==true||temp->next->data == source){
				temp=temp->next;
				continue;
			}
			q.push(temp->next->data);
			visited[temp->next->data]=true;
			*count = *count+1;
			temp=temp->next;
		}
	}
}
int mother_vertex(graph *g){
	int count = 0;
	bool visited[g->v];
	for(int i=0;i<g->v;i++)
		visited[i]=false;
	for(int i=0;i<g->v;i++){
		if(visited[i]==true)
			continue;

		dfs_visit(g,i,visited,&count);
		if(count == g->v-1)
			return i;
		visited[i]=true;
		count++;
	}
	return 0;
}
int mother_vertex_better(graph *g){
	int time[g->v];
	for(int i=0;i<g->v;i++){
		time[i]=0;
	}
	int s = 0;
	queue<int> q;

	while(!q.empty()){

	}
	return 0;
}
//the reachability 2-d matrix is returned
//the function prints the reachablility matrix
//similar to algorithm on geeksforgeeks
void dfs_util(graph *g,bool **rc,int s,int v){
	rc[s][v]=true;

	graph_node *temp = g->adj[v]->next;

	while(temp!=NULL){
		if(rc[s][temp->data]==false)
			dfs_util(g,rc,s,temp->data);
		temp=temp->next;
	}
}
bool ** transitive_closure(graph *g){
	bool **rc = new bool*[g->v];
	for(int i=0;i<g->v;i++){
		rc[i]=new bool[g->v];
		memset(rc[i],false,(g->v)*(sizeof(bool)));
	}
	for(int i=0;i<g->v;i++)
	dfs_util(g,rc,i,i);

	for(int i=0;i<g->v;i++){
		for(int j=0;j<g->v;j++){
			cout<<rc[i][j]<<" ";
		}
		cout<<endl;
	}
	return rc;

}
int main(int argc, char const *argv[])
{
	graph *g;
	insert_digraph_weighted(&g);


	print_digraph_weighted(g);


	//connectedComponents(g);
	MSTPrims(g);



	//toposort_dfs_no_markings(g);
	//toposort_dfs1(g);
	//dfsCLRS_iterative(g);
	//cout << endl << endl;
	//DFS_postorder(g,0);
	//toposort_all(g);*/

	// int n;
	// cin >> n;
	// int arr[n];
	// int rev[n];
	//
	// for(int i=0;i<n;i++){
	// 	int a ;
	// 	cin >> a;
	// 	arr[i]=a;
	// 	rev[i]=i;
	// }
	// sortedElements(arr,n,rev);



	return 0;
}
