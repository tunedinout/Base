#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#define null NULL
using namespace std;
///contains algorithms specific to BST only
class BSTNode{
public:
	int data;
	BSTNode *left;
	BSTNode *right;
	BSTNode (int a){
		data = a;
		left = NULL;
		right = NULL;
	}
};

void insert(BSTNode **root,BSTNode *current,int key){
	if(*root == NULL){
		*root = new BSTNode(key);
		return;
	}


	if(key<current->data){
		if(current->left!=NULL)
			insert(root,current->left,key);
		else{
			current->left = new BSTNode(key);
			return;
		}

	}
	else if(key>current->data){
		if(current->right!=NULL){
			insert(root,current->right,key);
			return;
		}
		else{
			current->right = new BSTNode(key);
			return;
		}
	}
}
void print(BSTNode *root){
	if(root == NULL)
		return;
	else{
		cout<<root->data<<" : ";
		if(root->left!=NULL)
			cout<<root->left->data<<" ";
		else
			cout<<"N ";

		if(root->right!=NULL)
			cout<<root->right->data<<" ";
		else
			cout<<"N ";

		cout<<endl;

		print(root->left);
		print(root->right);
	}
}
void BSTInsert(BSTNode **root){
	int a;
	cout<<"-1 stops input"<<endl;
	cin>>a;
	while(a!=-1){
		insert(root,*root,a);
		cin>>a;
	}
}
void exact_tree_input(BSTNode **root){
	stack<BSTNode*> st;
	cout<<"For NULL child enter -1"<<endl;

	int k;
	cin>>k;
	if(k==-1)
		return;

	*root = new BSTNode(k);
	st.push(*root);
	while(!st.empty()){
		BSTNode * node = st.top();st.pop();

		cout<<"Enter the left child of " << node->data<<endl;;
		int k;
		cin>>k;
		if(k==-1)
			node->left = NULL;
		else
			node->left = new BSTNode(k);
		cout<<"Enter the right child of "<<node->data<<endl;
		cin>>k;
		if(k==-1)
			node->right=NULL;
		else
			node->right=new BSTNode(k);

		if(node->left!=NULL)
			st.push(node->left);
		if(node->right!=NULL)
			st.push(node->right);

	}
}
BSTNode* search(BSTNode *root,int key){
	if(root == NULL || root->data == key)
		return root;

	if(key<root->data)
	return search(root->left,key);

	else if(key>root->data)
	return search(root->right,key);


}
//returns pointer to minimum value
BSTNode * min_value_bst(BSTNode *root){
	BSTNode *current = root;
	while(current->left!=NULL)
		current = current->left;
	return current;

}

void inorder_suc_key(BSTNode *root,int k){
	BSTNode *current = root;
	BSTNode *closest_left_ancestor=NULL;
	while(current!=NULL){
		if(k<current->data){
			closest_left_ancestor=current;
			current=current->left;
		}else if(k>current->data){
			current=current->right;
		}
		else
			break;
	}
	if(current==NULL)
		cout<<"The node was not found"<<endl;
	else{
		if(current->right!=NULL){
			current=current->right;
			while(current->left!=NULL)
				current=current->left;
			cout<<"The inorder successor is "<<current->data<<endl;
		}else{
			if(closest_left_ancestor==NULL)
				cout<<"This is the last node in the inorder traversal"<<endl;
			else
				cout<<"The inorder successor is "<<closest_left_ancestor->data<<endl;
		}
	}
}
//   ******** check if given tree is BST is implemented in binary Tree File

//find the inorder predecessor
void inorder_pred_key(BSTNode *root,int k){
	BSTNode *current = root;
	BSTNode *closest_right_ancestor = NULL;

	//search for the node in BST
	while(current!=NULL){
		if(k<current->data){
			current=current->left;
		}
		else if(k>current->data){
			closest_right_ancestor=current;
			current=current->right;
		}
		else
			break;
	}

	if(current == NULL){
		cout<<"The node was not found"<<endl;
	}else{
		if(current->left!=NULL){
			//find the rightmost  node in the left subtree
			current=current->left;
			while(current->right!=NULL)
				current=current->right;
			cout<<"The inoder predecessor is "<<current->data<<endl;
		}else{
			if(closest_right_ancestor == NULL)
				cout<<"This is the first node in the inorder traversal"<<endl;
			else
				cout<<"The inorder predecessor is "<<closest_right_ancestor->data<<endl;
		}
	}
}
//ASSUM:
//both the keys must be there
//if it is not so
//the lca is the lca of the nearest matches of the key
//either immediately smaller or immediately larger
BSTNode * lca_bst(BSTNode *root,int key1,int key2){
	BSTNode *current = root;
	while(current!=NULL){
		if(key1<=current->data&key2<=current->data)
			current = current->left;
		else if(key1>=current->data&key2>=current->data)
			current=current->right;
		else
			return current;
	}

	return NULL;
}
//function to print elements in a given range in a BST
//complexity is length of the range[a-b] + time taken to find the nearest
//match of a

void print_range(BSTNode *root,int a,int b){
	BSTNode *current = root;
	stack <BSTNode *> st;
	st.push(root);
	while(!st.empty()){

		if(current!=NULL){
			if(current->data < a){
				st.pop();
				if(current->right!=NULL)
				st.push(current->right);
				current=current->right;
				continue;
			}

			if(current->left!=NULL)
				st.push(current->left);
			current=current->left;
		}else{
			current=st.top();st.pop();
			if(current->data > b)
				break;
			cout<<current->data<<" ";
			if(current->right!=NULL)
				st.push(current->right);
			current=current->right;
		}
	}
	cout<<endl;
}
//find k-th smallest element from a BST
void k_smallest(BSTNode *root,int k){
	BSTNode *current = root;
	stack<BSTNode *> st;
	int count = 0;
	st.push(root);
	while(!st.empty()){
		if(current!=NULL){
			if(current->left!=NULL){
				st.push(current->left);
			}
			current=current->left;
		}else{
			current=st.top();st.pop();
			count++;
			if(count == k){
				cout<<"Kth"<<"("<<k<<")"<<" smallest value "<<current->data<<endl;
				return;
			}
			if(current->right!=NULL)
				st.push(current->right);
			current=current->right;
		}

	}
	cout<<"K is greater than number of nodes in the tree"<<endl;
}
//given the two arrays used for
//creating a binary search tree
//return true if both of them
//lead to the construction of the
//same binary search tree
//NOTE:Without actually constructing the BST
//helper function fills the level order array
//with the level order traversal constructed from an
//array used to construct bst
//levelOrder=level order array
void level_order_from_arr_of_bst(int arr[],int size,int levelOrder[]){
	int subtree_start[size];
	int subtree_end[size];
	int i = 0;
	int last=0;//position of the last element inserted in  the levelOrder array
	levelOrder[i]=arr[0];
	//subtree start - to - end contains both left and right subtree
	//not necessarily separted as left and right
	subtree_start[i]=1;
	subtree_end[i]=size-1;

	while(i!=size){
		int rootOfSubtree = levelOrder[i];
		int start = subtree_start[i];
		int end = subtree_end[i];

		if(start>end){
			i++;
			if(i==size)
				break;
			continue;
		}
		//seperate left and right sub tree
		int aux1[end-start+1],aux2[end-start+1],size1=0,size2=0;

		for(int j=start;j<=end;j++){
			if(arr[j]<rootOfSubtree)
				aux1[size1++]=arr[j];
			else
				aux2[size2++]=arr[j];
		}
		//replace arr from start to end by aux1 elements followed by
		//aux2 elements
		int k = start;
		for(int j=0;j<size1;j++)
			arr[k++]=aux1[j];
		int division = k;
		for(int j=0;j<size2;j++)
			arr[k++]=aux2[j];
		if(start<division){
			levelOrder[++last]=arr[start];
			subtree_start[last]=start+1;
			subtree_end[last]=division-1;
		}
		if(division<=end){
			levelOrder[++last]=arr[division];
			subtree_start[last]=division+1;
			subtree_end[last]=end;
		}
		i++;

	}
}
bool ifBSTSimilar(int arr1[],int arr2[],int size){
	int level_order1[size],level_order2[size];
	level_order_from_arr_of_bst(arr1,size,level_order1);
	level_order_from_arr_of_bst(arr2,size,level_order2);

	for(int i=0;i<size;i++)
		if(level_order1[i]!=level_order2[i])
			return false;

	return true;
}
//add all the greater values to the BST nodes
void addGreater(BSTNode *root){
	int sumofallNodes=0;
	BSTNode *current = root;
	while(current!=NULL){
		if(current->left==NULL){
			sumofallNodes+=current->data;
			current=current->right;
		}else{
			BSTNode *pre = current->left;
			while(pre->right!=NULL && pre->right!=current)
				pre=pre->right;

			if(pre->right==NULL){
				pre->right = current;
				current=current->left;
			}else{
				pre->right = NULL;
				sumofallNodes+=current->data;
				current=current->right;

			}
		}
	}

	int sumoflesserNodes=0;
	current = root;
	//do another traversal
	while(current!=NULL){
		if(current->left==NULL){
			int curr_data=current->data;
			current->data = sumofallNodes - sumoflesserNodes;
			sumoflesserNodes+=curr_data;
			current=current->right;
		}else{
			BSTNode *pre = current->left;
			while(pre->right!=NULL && pre->right!=current)
				pre=pre->right;

			if(pre->right==NULL){
				pre->right = current;
				current=current->left;
			}else{
				pre->right = NULL;
				int curr_data=current->data;
				current->data = sumofallNodes - sumoflesserNodes;
				sumoflesserNodes+=curr_data;
				current=current->right;

			}
		}
	}
}
//function to remove all the elements
//in a bst that lie outside the given range
//(min,max)
//
void remove_outside_range(BSTNode **root,int min,int max){
	BSTNode *current = *root;
	BSTNode *parent = NULL;
	while(current!=NULL){
		if(current->data==min){
			current->left = NULL;
			break;
		}
		if(current->data < min){
			if(parent == NULL){
				*root = current->right;
				current = *root;
			}else{
				if(parent->left == current){
					parent->left = current->right;
					current=parent->left;
				}else{
					parent->right = current->right;
					current=parent->right;
				}

			}
		}
		else if(current->data > min){
			parent=current;
			current=current->left;
		}
	}
	current = *root;
	while(current != NULL){
		if(current->data == max){
			current->right=NULL;
			break;
		}
		if(current->data < max){
			parent = current;
			current=current->right;
		}else if(current->data > max){
			if(parent==NULL){
				*root = current->left;
				current = *root;

			}else{
				if(parent->left == current){
					parent->left = current->left;
					current=parent->left;
				}else{
					parent->right = current->left;
					current=parent->right;
				}
			}
		}
	}
}
//given preorder traversal check if bst is a linked list
bool ifLinkedList_preorder(int pre[],int size){
	int max=INT_MAX,min=INT_MIN;
	for(int i=0;i<size;i++){
		if(!(pre[i]<max&&pre[i]>min))
			return false;

		if(i!=size-1){
			if(pre[i]<pre[i+1]){
				min=pre[i];
			}else{
				max=pre[i];
			}

		}
	}
	return true;
}
//function to construct BST from the preorder traversal
void create_BST_preorder(BSTNode **root,int pre[],int size){
	 *root = new BSTNode(pre[0]);
	stack <BSTNode *> st;
	st.push(*root);

	for(int i=1;i<size;i++){
		BSTNode *current = new BSTNode(pre[i]);
		if(pre[i]<st.top()->data){
			st.top()->left = current;
			st.push(current);
		}else{
			BSTNode *previous = NULL;
			while((!st.empty())&&st.top()->data<pre[i]){
				previous = st.top();
				st.pop();
			}
			previous->right = current;
			st.push(current);
		}
	}
}
//post order is given by L R root
//so reverse of post order array
//follows root R L
//so algorithm is quite similar to creat_BST_preorder
void create_BST_postorder(BSTNode **root,int post[],int size){
	*root = new BSTNode(post[size-1]);
	stack <BSTNode *> st;
	st.push(*root);
	for(int i=size-2;i>=0;i--){
		BSTNode *current = new BSTNode(post[i]);
		if(post[i]>st.top()->data){
			st.top()->right = current;
			st.push(current);
		}else{
			BSTNode *previous = NULL;
			while((!st.empty())&&post[i]<st.top()->data){
				previous = st.top();
				st.pop();
			}
			previous->left=current;
			st.push(current);
		}
	}
}
//given a sorted array construct a balanced bst
void create_BST_from_sorted_array(BSTNode **root,int A[],int size){
	int start = 0;
	int end = size-1;
	stack <BSTNode *> st;
	stack <int> st_start;
	stack <int> st_end;
	*root = new BSTNode(A[(start+end)/2]);
	st.push(*root);
	st_start.push(((start+end)/2)+1);
	st_end.push(end);
	start = 0;
	end=((start+end)/2)-1;
	BSTNode *current = *root;

	while(1){
		if(start<end){
			int half = (start+end)/2;
			BSTNode *node=new BSTNode(A[half]);

			if(node->data<current->data)
				current->left=node;
			else
				current->right=node;
				current=node;
			st.push(node);
			st_start.push(half+1);
			st_end.push(end);
			end=half-1;
		}else{
			if(start==end){
				BSTNode *node=new BSTNode(A[start]);
				if(node->data<current->data)
					current->left=node;
				else
					current->right=node;
				start=end+1;
			}

			if(st.empty())
				break;
			while(start>end){
				current=st.top();st.pop();
				start = st_start.top();st_start.pop();
				end=st_end.top();st_end.pop();
			}
		}
	}
}
class LLNode{
public:
	int data;
	LLNode *next;
	LLNode(int a){
		data = a;
		next = NULL;
	}
};
void insert(LLNode **head,int data){
	if(*head == NULL){
		*head = new LLNode(data);
	}else{
		LLNode *temp=*head;
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next = new LLNode(data);
	}
}
LLNode *middle(LLNode *start,LLNode *end){

	LLNode *fast=start;
	LLNode *slow=start;
	while(1){
		if(fast==NULL)
			break;
		if(fast==end)
			break;
		if(fast->next==end)
			break;
		slow=slow->next;
		fast=fast->next->next;
	}

	return slow;
}
void create_BST_from_sorted_linkedlist(BSTNode **root,LLNode *head){
	LLNode *start = head;
	LLNode *end = NULL;
	LLNode *mid = middle(start,end);
	*root = new BSTNode(mid->data);
	BSTNode *current = *root;
	stack <BSTNode *> st;
	stack <LLNode *> st_start;
	stack <LLNode *> st_end;
	st.push(current);
	st_start.push(mid->next);
	st_end.push(end);
	end = mid;

	while(1){

		if(start->next!=end&&start!=end){

			mid = middle(start,end);
			BSTNode *node = new BSTNode(mid->data);
			if(node->data<current->data)
				current->left=node;
			else
				current->right=node;
			current=node;
			st.push(current);
			st_start.push(mid->next);
			st_end.push(end);
			end=mid;
			continue;

		}
		 if(start->next==end||start==end){

			if(start->next==end){
				if(start->data<current->data)
					current->left = new BSTNode(start->data);
				else
					current->right = new BSTNode(start->data);

			}
			start=end;
			if(st.empty())
				break;
			while(start==end||start==NULL){

				current=st.top();st.pop();
				start=st_start.top();st_start.pop();
				end=st_end.top();st_end.pop();

				if(st.empty())
					break;
			}

			if(st.empty()){
				if(start==end||start==NULL)
					break;
			}
		}

	}
}
//a doubly linked list can be represented using a tree node
//the front and back are basically the left and right
void insert_dll(BSTNode **head,int data){
	if(*head == NULL)
		*head = new BSTNode(data);
	else{
		BSTNode *temp = *head;
		while(temp->right != NULL)
			temp=temp->right;

		temp->right = new BSTNode(data);
		temp->right->left = temp;
	}
}
BSTNode *middle(BSTNode *start,BSTNode *end){

	BSTNode *fast=start;
	BSTNode *slow=start;
	while(1){
		if(fast==NULL)
			break;
		if(fast==end)
			break;
		if(fast->right==end)
			break;
		slow=slow->right;
		fast=fast->right->right;
	}

	return slow;
}
void create_BST_from_sorted_doublelinkedlist(BSTNode **head,BSTNode **root){
	BSTNode * start = *head;
	BSTNode * end = NULL;
	BSTNode * mid = middle(start,end);
	*root = mid;
	BSTNode *current = *root;
	stack <BSTNode *> st;
	stack <BSTNode *> st_start;
	stack <BSTNode *> st_end;
	st.push(current);
	st_start.push(mid->right);
	st_end.push(end);
	end = mid;
	mid->right = NULL;
	while(1){
		if(start->right!=end&&start!=end){
			mid = middle(start,end);
			if(mid->data > current->data ){
				current->right = mid;
			}else{
				current->left = mid;
			}
			current = mid;
			st.push(current);
			st_start.push(mid->right);
			st_end.push(end);
			end=mid;
			mid->right=NULL;
		}else{
			if(start->right==end){
				if(start->data > current->data)
					current->right = start;
				else
					current->left =start;
				start->left = NULL;
				start->right = NULL;
			}
			start = end;
			if(st.empty())
				break;
			while(start==end || start == NULL){
				current = st.top();st.pop();
				start = st_start.top();st_start.pop();
				end = st_end.top();st_end.pop();
				if(st.empty())
					break;
			}
			if(st.empty()&&(start == NULL|| start == end ))
				break;
		}

	}
}

//function boolean iftriplet_with_sum0
//true if a triplet with sum zero is found in a Balanced bst
//helper function - restricted search
//it receives two parameters 1.root 2.restricted_subtreenode1 3.restricted_subtreenode2
//3.key . it looks for key in the BST but not in the restricted subtree nodes
//
BSTNode* restricted_search(BSTNode *root,BSTNode* restricted_node1,BSTNode* restricted_node2,int key){
	BSTNode *c = root;
	while(c!=NULL){
		if(c==restricted_node1)
			return NULL;
		if(key>c->data){
			c=c->right;
		}
		else if(key<c->data){
			c=c->left;
		}else{
			if(c==restricted_node2)
				return NULL;
			else
				return c;

		}

	}

	return NULL;
}

bool ifTriplet_with_sum_0(BSTNode *root){
	if(root == NULL)
		return false;
	bool iffound=false;
	BSTNode *c = root;
	stack <BSTNode *> outer;
	outer.push(c);
	while(!outer.empty()){
		BSTNode *use = NULL;
		if(c!=NULL){
			c=c->left;
			if(c!=NULL)
				outer.push(c);
			continue;
		}else{
			use = outer.top();outer.pop();
			c=use->right;
			if(c!=NULL)
				outer.push(c);
		}
		//go in the left subtree

		if(use->left!=NULL){
			stack <BSTNode*> inner;
			inner.push(use->left);
			BSTNode *c1=use->left;
			while(!inner.empty()){
				if(c1!=NULL){
					c1=c1->left;
					if(c1!=NULL)
						inner.push(c1);
				}else{
					c1=inner.top();inner.pop();

					BSTNode *temp = restricted_search(root,use->left,use,-(use->data+c1->data));
					if(temp!=NULL){
						//cout<<"One of the three triplets are "<<use->data<<", "<<c1->data<<", "<<temp->data<<endl;
						iffound=true;
					}
					c1=c1->right;
					if(c1!=NULL)
						inner.push(c1);

				}
			}
		}
		//do the same for the right subtree
		if(use->right!=NULL){
			stack <BSTNode*> inner;
			inner.push(use->right);
			BSTNode *c1=use->right;
			while(!inner.empty()){
				if(c1!=NULL){
					c1=c1->left;
					if(c1!=NULL)
						inner.push(c1);
				}else{
					c1=inner.top();inner.pop();

					BSTNode *temp = restricted_search(root,use->right,use,-(use->data+c1->data));

					if(temp!=NULL){
						//cout<<"One of the three triplets are "<<use->data<<", "<<c1->data<<", "<<temp->data<<endl;
						iffound=true;
					}
					c1=c1->right;
					if(c1!=NULL)
						inner.push(c1);

				}
			}
		}

	}
	return iffound;
}
//if we copy inorder array to another array and sort that array
//going from left to right the first mismatch between respective elements
//will tell us which nodes have been swapped
BSTNode* findParent (BSTNode *root,BSTNode* node){

}
//exchanges two BST nodes of a BSTsearch Tree
//use cases
//first and second are both not null
//	first ,second ,first_parent,second_parent
//1.first_parent = null,second_parent !=null
//1-a second_parent = first , first _parent!=null
//1-b second_parent = first , first_parent == null
//2.second_parent can not be null
//3.first_parent = second_parent
//4.
void exchange(BSTNode **root,BSTNode *first,BSTNode *second,BSTNode *first_parent,BSTNode *second_parent){
	if(second_parent == null || first == null || second == null)
		return;
	if(first_parent == null && second_parent == null)
		return;
	if(second_parent == null){
		BSTNode *temp = first;
		BSTNode *temp_parent = first_parent ;
		first = second;
		first_parent = second_parent ;
		second = temp;
		second_parent = temp_parent ;
	}



	if(first_parent == null){
		//can second be a child ?


		if(second_parent != first){
			BSTNode *first_left = first -> left ; first -> left = null;
			BSTNode *first_right = first -> right ; first -> right = null;

			BSTNode *second_left = second -> left ; second -> left = null;
			BSTNode *second_right = second -> right ; second -> right = null;

			*root = second ;

			if(second_parent -> left == second)
				second_parent -> left = first;
			else
				second_parent -> right = first
			BSTNode *temp = second ;
			second = first ;
			first  = second ;

			first->left = first_left;second -> left = second_left;
			first -> right = first_right;second -> right = second_right;
		}else{
			if(first_parent -> left )
			BSTNode *first_left = first -> left ; first -> left = null;
			BSTNode *first_right = first -> right ; first -> right = null;

			BSTNode *second_left = second -> left ; second -> left = null;
			BSTNode *second_right = second -> right ; second -> right = null;

		}
	}else{

		if(second_parent != first){
			BSTNode *first_left = first -> left ; first -> left = null;
			BSTNode *first_right = first -> right ; first -> right = null;

			BSTNode *second_left = second -> left ; second -> left = null;
			BSTNode *second_right = second -> right ; second -> right = null;

			if(first_parent -> left = first)
				first_parent -> left = second ;
			else
				first_parent -> right = second ;

			if(second_parent -> left == second)
				second_parent -> left = first;
			else
				second_parent -> right = first ;

			BSTNode *temp = second ;
			second = first ;
			first  = second ;

			first->left = first_left;second -> left = second_left;
			first -> right = first_right;second -> right = second_right;
		}else{


		}

	}

}
void two_nodes_swapped_correct_bst(BSTNode **root){
	BSTNode *current = *root , *current_parent = null;
	BSTNode *prev = null, *prev_parent = null;
	BSTNode *first = null,*first_parent= null;
	BSTNode *second = null,*second_parent = null;
	BSTNode *first_next = null;

	cout<<endl;
	stack < pair <BSTNode *,BSTNode *> > st;

	do{
		if(current == null){
			pair <BSTNode*,BSTNode*> p = st.top();st.pop();
			//current = st.top();st.pop();
			current = p . first;
			current_parent = p.second;



			if(prev!=null&&current->data < prev-> data && first == null){
				first_parent = prev_parent;
				first = prev ;
				first_next = current;
			}

			if(prev!=null&&current->data < prev->data && first!= null){
				second_parent = current_parent;
				second = current ;

			}


			cout << current -> data<<" ";
			prev = current ;
			prev_parent = current_parent;

			current = current -> right ;
			current_parent = prev;
		}

		if(current!=null){
			//current parent can only be null in case of root node
			st.push(make_pair(current,current_parent));
			current_parent = current;
			current = current -> left;

		}

	}while(!st.empty());
	cout<< endl;


	if(second != null){
		cout<<"The swapped nodes are "<<first ->data <<" and "<<second->data<<endl;
		if(first_parent!=null)
			cout <<"There parents are "<<first_parent->data << " and "<<second_parent->data<<endl;
		else
			cout<<"First is root and second parent = "<<second_parent->data << endl;

		exchange(root,first,second,first_parent,second_parent);


	}
	else{
		cout <<"The swapped nodes are "<<first->data<<" and "<<first_next->data<<endl;
		if(first_parent != null)
		cout <<"There parents are "<<first_parent->data << " and "<<first->data<<endl;
		else
			cout<<"first has no parent and is the parent of "<<first_next->data<<endl;
		exchange(root,first,first_next,first_parent,first);

	}

	//find parent of both


}
//traverse both the trees inorder simultaneously
//if node to print for first tree is ready raise flag to stops its further traversal
//similarly for second
//if nodes to print for both are ready the smaller one will be printed
//flag will be raise so that this nodes tree can be traveresed further
void print_merged_BST(BSTNode *root1,BSTNode *root2){
	BSTNode *c1=root1;
	BSTNode *c2=root2;
	stack <BSTNode *> st1;
	stack <BSTNode *> st2;

	if(c1!=NULL)
		st1.push(c1);
	if(c2!=NULL)
		st2.push(c2);
	bool trav1=true;
	bool trav2=true;
	BSTNode *use1=NULL;
	BSTNode *use2=NULL;
	while((!st1.empty())&&(!st2.empty())){
		if(trav1){
			if(c1!=NULL){
				c1=c1->left;
				if(c1!=NULL)
					st1.push(c1);
			}else{
				use1=st1.top();st1.pop();
				c1=use1->right;
				if(c1!=NULL)
					st1.push(c1);
			}
		}

		if(trav2){
			if(c2!=NULL){
				c2=c2->left;
				if(c2!=NULL)
					st2.push(c2);
			}else{
				use2=st2.top();st2.pop();
				c2=use2->right;
				if(c2!=NULL)
					st2.push(c2);
			}
		}

		if(use1!=NULL)
			trav1=false;
		if(use2!=NULL)
			trav2=false;

		if((!trav1)&&(!trav2)){
			if(use1->data<use2->data){
				cout<<use1->data<<" ";
				use1=NULL;
				trav1=true;
			}else if(use1->data>use2->data){
				cout<<use2->data<<" ";
				use2=NULL;
				trav2=true;
			}else{
				//equal
				cout<<use1->data<<" ";
				use1=NULL;use2=NULL;
				trav1=true;trav2=true;
			}
		}
	}
	if((st1.empty())&&(st2.empty()))
		return;
	if(!st1.empty()){
		if(use1!=NULL&&use2!=NULL){
			if(use1->data<use2->data){
				cout<<use1->data<<" "<<cout<<use2->data<<" ";
			}else{
				cout<<use2->data<<" "<<cout<<use1->data<<" ";
			}

			/*c1=use1->right;
			if(c1!=NULL)
				st1.push(use1);*/
		}
		else if(use1!=NULL){
			cout<<use1->data<<" ";
		}else if(use2!=NULL){
			cout<<use2->data<<" ";
		}
		while(!st1.empty()){
			if(c1!=NULL){
				c1=c1->left;
				if(c1!=NULL)
					st1.push(c1);
			}else{
				c1=st1.top();st1.pop();
				cout<<c1->data<<" ";
				c1=c1->right;
				if(c1!=NULL)
					st1.push(c1);
			}
		}
	}else{
		if(use1!=NULL&&use2!=NULL){
			if(use1->data<use2->data){
				cout<<use1->data<<" "<<cout<<use2->data<<" ";
			}else{
				cout<<use2->data<<" "<<cout<<use1->data<<" ";
			}

			/*c1=use1->right;
			if(c1!=NULL)
				st1.push(use1);*/
		}
		else if(use1!=NULL){
			cout<<use1->data<<" ";
		}else if(use2!=NULL){
			cout<<use2->data<<" ";
		}

		while(!st2.empty()){
			if(c2!=NULL){
				c2=c2->left;
				if(c2!=NULL)
					st2.push(c2);
			}else{
				c2=st2.top();st2.pop();
				cout<<c2->data<<" ";
				c2=c2->right;
				if(c2!=NULL)
					st2.push(c2);
			}
		}
	}
}
//gives the node for Bst with node->data=key or else
//the smallest node which is greater than key
BSTNode * ceiling(BSTNode *root,int key){
	BSTNode *c=root;
	BSTNode *ans=NULL;
	while(c!=NULL){
		if(key<c->data){
			if(ans==NULL)
				ans=c;
			else{
				if(c->data<ans->data)
					ans=c;
			}
			c=c->left;

		}
		else if(key>c->data){
			c=c->right;
		}
		else
			return c;
	}
	return ans;
}
BSTNode * floor(BSTNode *root,int key){
	BSTNode *c=root;
	BSTNode *ans=NULL;
	while(c!=NULL){
		if(key>c->data){
			if(ans==NULL)
				ans=c;
			else{
				if(c->data>ans->data)
					ans=c;
			}
			c=c->right;

		}
		else if(key<c->data){
			c=c->left;
		}
		else
			return c;
	}
	return ans;
}
//FIND THE NUMBER OF ALL POSSIBLE BST
//THAT CAN BE CONSTRUCTED FROM
//N-KEYS - catalan Number
//code in generalAlgos.cpp

//Convert BST to a sorted
//DLL returns head of the
//DLL
BSTNode * BST_to_sortedDLL(BSTNode *root){
	BSTNode *current = NULL;
	BSTNode *left_rightest = NULL;
	BSTNode *right_leftest = NULL;
	BSTNode *head = NULL;
	stack <BSTNode*> st;
	st.push(root);

	//find head
	current = root;
	while(current->left != NULL)
		current = current->left;
	head = current;
	//first convert to linked list
	//gives the benifit of marking nodes that we
	//are done with as node->left = NULL
	while(!st.empty()){
		current = st.top();st.pop();
		left_rightest=NULL;
		right_leftest=NULL;

		if(current->left!=NULL){
			left_rightest=current->left;
			while(left_rightest->right!=NULL)
				left_rightest=left_rightest->right;
			if(!(left_rightest==current->left&&left_rightest->left==NULL))
			st.push(current->left);
		left_rightest->right = current;
		}

		if(current->right!=NULL){
			right_leftest=current->right;
			while(right_leftest->left!=NULL)
				right_leftest=right_leftest->left;
			if(!(right_leftest==current->right&&right_leftest->right==NULL))
			st.push(current->right);
			current->right = right_leftest;
		}
		current->left = NULL;

	}
	//convert to doubly linked list here
	BSTNode *temp = head;
	while(temp->right!=NULL){
		temp->right->left = temp;
		temp=temp->right;
	}
	return head;
}
//prints DLL whose node is BSTNode
void print_DLL(BSTNode *head){
	BSTNode *temp = head;
	BSTNode *temp1;
	cout<<" print forward direction"<<endl;;
	while(temp!=NULL){

		cout<<temp->data<<" ";
		temp1=temp;
		temp=temp->right;
	}
	cout<<endl;

	cout<<"print backward"<<endl;
	while(temp1!=NULL){
		cout<<temp1->data<<" ";
		temp1=temp1->left;
	}
	cout<<endl;
}
int main(int argc, char const *argv[])
{
	BSTNode *root = NULL;
	BSTNode *head = NULL;

	//BSTInsert(&root);
	exact_tree_input(&root);
	print(root);

	/*head = BST_to_sortedDLL(root);
	print_DLL(head);
*/

	two_nodes_swapped_correct_bst(&root);
	print (root);
	//clock_t t;
	//t=clock();

	//t=clock()-t;

	//printf ("It took (%f seconds).\n",((float)t)/CLOCKS_PER_SEC);


	return 0;
}
