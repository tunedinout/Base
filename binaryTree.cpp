#include <iostream>
#include <cstdlib>
#include <stack>
#include <queue>
using namespace std;
#define null NULL
int max (int a,int b){
	return a > b ? a : b;
}
class btree_node{
public:
	int data;
	btree_node *left;
	btree_node *right;
	btree_node(int a,btree_node *l,btree_node *r){
		left = l;
		right = r;
		data = a;
	}
	btree_node(int a){
		data = a;
		left = null;right = null;
	}
};
void insert_in_btree(btree_node **root,int d){
	if(*root == NULL)
		*root = new btree_node(d,NULL,NULL);
	else{
		btree_node *current = *root;
		btree_node *prev = NULL;
		while(current!=NULL){
			if(d <= current->data){
				prev = current;
				current = current->left;
			}else{
				prev = current;
				current = current->right;
			}
		}

		//find the right node
		if(d <= prev->data)
			prev->left = new btree_node(d,NULL,NULL);
		else
			prev->right = new btree_node(d,NULL,NULL);
	}
}

////
class q_node{
	public :
	btree_node *element;
	q_node *next;

};
q_node *head=NULL;
q_node *tail=NULL;
void push(btree_node *ptr){


	q_node *node = new q_node();
	node->element = ptr;
	node->next = NULL;
	if(head == NULL){
		head = node;
		tail = node;
	}else{
		tail->next = node;
		tail = node;
	}

}
btree_node *pop(){
	if(head == NULL)
		return NULL;
	q_node *temp = head;
	head = head->next;
	return temp->element;
}//////
void print_childern(btree_node *ptr){
	cout<< ptr->data <<" : ";
	if(ptr->left!=NULL)
		cout<<"L [ "<<ptr->left->data<<" ] ";
	else
		cout<<"L [null] ";

	if(ptr->right!=NULL)
		cout<<"R [ "<<ptr->right->data<<" ] ";
	else
		cout<<"R [null] ";
	cout <<endl;
}
void print_reg(btree_node *root){
	if(root == NULL)
		return;


	btree_node *temp = root;
	while(temp != NULL){

		print_childern(temp);

		if(temp->left!=NULL)
			push(temp->left);
		if(temp->right != NULL)
			push(temp->right);
		temp = pop();


	}
}
void input(btree_node **root){
	int a;
	while(1){
		cin>>a;
		if(a == -1)
			return;
		else{
			insert_in_btree(root,a);
		}
	}
}
void exact_tree_input(btree_node **root){
	stack<btree_node*> st;
	cout<<"For NULL child enter -1"<<endl;

	int k;
	cin>>k;
	if(k==-1)
		return;

	*root = new btree_node(k,NULL,NULL);
	st.push(*root);
	while(!st.empty()){
		btree_node * node = st.top();st.pop();

		cout<<"Enter the left child of " << node->data<<endl;;
		int k;
		cin>>k;
		if(k==-1)
			node->left = NULL;
		else
			node->left = new btree_node(k,NULL,NULL);
		cout<<"Enter the right child of "<<node->data<<endl;
		cin>>k;
		if(k==-1)
			node->right=NULL;
		else
			node->right=new btree_node(k,NULL,NULL);

		if(node->left!=NULL)
			st.push(node->left);
		if(node->right!=NULL)
			st.push(node->right);

	}
}
/////helper linked list n
class node {
public:
	btree_node *element;
	node *next;
	//these two will help in preorder
	bool if_left;
	bool if_right;
	node (btree_node *el,node *n){
		element = el;
		next = n;

		if_right=false;
		if_left=false;
	}
};
void push_node_last(node **head,node **tail,btree_node *el){
	if(*head == NULL){
		*head = new node(el,NULL);
		*tail = *head;
	}
	else{
		node *new_node = new node(el,NULL);
		(*tail)->next = new_node;
		*tail = (*tail)->next;
	}
}
void push_node_first(node **head,node **tail,btree_node *el){
	if(*head == NULL){
		*head = new node(el,NULL);
		*tail = *head;
	}else{

		node *new_node = new node(el,NULL);
		new_node->next = *head;
		*head = new_node;
	}
}
node* pop_node_first(node **head,node **tail){
	if(*head == NULL)
		return NULL;
	else{
		if(*head == *tail)
			*tail = (*tail)->next;
		node *temp = *head;
		*head = (*head)->next;
		return temp;
	}
}
btree_node * search(btree_node *node,int a){
	if(node == null)
		return null;
	if(node->data == a)
		return node;
	else{
		btree_node *n1 = search(node->left,a);
		btree_node *n2 = search(node->right,a);
		return n1 == null ? n2 : n1;
	}


}
//using an explicit stack
void print_level_order_newline(btree_node *root){
	if(root == NULL)
		return;
	node *head = NULL;
	node *tail = NULL;
	push_node_last(&head,&tail,root);
	push_node_last(&head,&tail,NULL);
	node *ptr;
	ptr = NULL;
	while(1){

		ptr = pop_node_first(&head,&tail);

		if(ptr == NULL || ptr->element == NULL)
			break;

		while(ptr->element!=NULL){
			cout<<ptr->element->data<<" ";
			if(ptr->element->left!=NULL)
				push_node_last(&head,&tail,ptr->element->left);
			if(ptr->element->right!=NULL)
				push_node_last(&head,&tail,ptr->element->right);

			ptr = pop_node_first(&head,&tail);
		}
		push_node_last(&head,&tail,NULL);
		cout<<endl;
	}

}
//height of a node is the number of edges on the longest path from the node to a leaf
int height(btree_node *node){
	if(node == null)
		return -1;
	else
		return max( (1 + height(node->left)),(1 + height(node -> right)));
}
//using the recursive stack
void print_level_order_newline_recur(btree_node *node,int height){
	if(node == null)
		return;
	if(height == 0)
		cout<<node->data<<" ";
	else{
		print_level_order_newline_recur(node->left,height-1);
		print_level_order_newline_recur(node->right,height-1);
	}


}
void print_level_order_newline_recursive(btree_node *root){
	int h = height(root);
	for(int i=0;i<=h;i++){
		print_level_order_newline_recur(root,i);
		cout<<endl;
	}
}
//////////////////////////////////////////////////////////

//INORDER TRAVERSAL
void inorder_iterative(btree_node *root){
	if(root == NULL)
		return;
	node *head = NULL;
	node *tail = NULL;
	btree_node *current = root;
	while(1){

		if(current==NULL){
			node *temp = pop_node_first(&head,&tail);
			cout<<temp->element->data<<" ";
			current = temp->element->right;
		}



		if(current!=NULL){
			push_node_first(&head,&tail,current);
			current=current->left;

		}

		if(head==NULL)
			break;

	}

	cout<<endl;
}
//PREORDER TRAVERSAL
void preorder_iterative(btree_node *root){
	if(root == NULL)
		return;
	node *head = NULL;
	node *tail = NULL;
	push_node_first(&head,&tail,root);
	while(head!=NULL){

		node *ptr = pop_node_first(&head,&tail);
		cout<<ptr->element->data<<" ";
		if(ptr->element->right != NULL)
			push_node_first(&head,&tail,ptr->element->right);
		if(ptr->element->left!=NULL)
			push_node_first(&head,&tail,ptr->element->left);


	}

	cout<<endl;
}
//POSTORDER TRAVERSAL
//devised by me
void postorder_iterative_single_stack(btree_node *root){
	if(root == NULL)
		return;

	btree_node *last_poped = NULL;
	stack<btree_node*> st;
	st.push(root);

	while(!st.empty()){
		if(last_poped == NULL){
			btree_node *c = st.top();
			if(c->left!=NULL){
				st.push(c->left);
				last_poped=NULL;
			}else{
				if(c->right!=NULL){
					st.push(c->right);
					last_poped=NULL;
				}else{
					last_poped=st.top();st.pop();
					cout<<last_poped->data<<" ";
				}
			}
		}else if(last_poped == st.top()->left){
			btree_node *c = st.top();
			if(c->right!=NULL){
				st.push(c->right);
				last_poped=NULL;
			}else{
				last_poped=st.top();st.pop();
				cout<<last_poped->data<<" ";
			}
		}else if(last_poped == st.top()->right){
				last_poped=st.top();st.pop();
				cout<<last_poped->data<<" ";
		}
	}

	cout<<endl;

}
void inorder_morris_traversal(btree_node *root){
	if(root == NULL)
		return;

	btree_node *current = root;
	btree_node *pre = NULL;

	while(current!=NULL){
		if(current->left == NULL){
			cout<<current->data<<" ";
			current = current ->right;
		}else{
			//find the right most node of currents left child and set
			//its right chld to current (this will be the current nodes inorder predecessor )

			pre = current->left;

			while(pre->right!=NULL && pre->right!=current)
				pre = pre->right;

			if(pre->right == NULL){
				pre->right = current;
				current = current->left;
			}

			else{
				pre->right = NULL;
				//since pre->right was equal to current
				//means we are done with the left subtree
				cout << current->data << " ";
				current = current -> right;
			}
		}
	}
}
void preorder_morris_traversal(btree_node *root){
	if(root == NULL)
		return;
	btree_node *current = root ;
	btree_node	*pre = NULL;
	//cout<<current->data << " ";
	while(current!=NULL){
		if(current->left == NULL){
			cout<<current->data<<" ";
			current = current ->right;
		}else{
			//find the right most node of currents left child and set
			//its right chld to current (this will be the current nodes inorder predecessor )

			pre = current->left;

			while(pre->right!=NULL && pre->right!=current)
				pre = pre->right;

			if(pre->right == NULL){
				pre->right = current;
				cout<<current->data<<" ";
				current = current->left;
				//in preoder always print root first
				//cout<<current->data << " ";
			}

			else{
				pre->right = NULL;
				//since pre->right was equal to current
				//means we are done with the left subtree
				current = current -> right;
			}
		}
	}

}
void postorder_morris_traversal(btree_node *root){
	if(root == NULL)
		return;

	///morris traversal cant help in postorder since
	//after visiting the root of the left child of the
	//left subtree we need a link to the right of
	//the root node

}
//maximum depth or height iterative
int maximum_depth_recursive(int depth,btree_node *current){
	if(current == NULL)
		return depth;

	else{
		int a = 0,b = 0;
			a = maximum_depth_recursive(depth+1,current->left);
			b = maximum_depth_recursive(depth+1,current->right);

		return a>b?a:b;
	}

}

//maximum depth or height recursive
int maximum_depth_iterative(btree_node *root){
	if(root == NULL)
		return 0;

	//we do a level order traversal
	//to mark end of the level we use a
	//dummy node

	node *head = NULL;
	node *tail = NULL;
	push_node_last(&head,&tail,root);
	push_node_last(&head,&tail,NULL);
	int depth = 0;
	node *ptr = NULL;
	while(1){

		depth++;

		ptr = pop_node_first(&head,&tail);
		if(ptr == NULL || ptr->element == NULL)
			break;
		while(ptr->element!=NULL){
			if(ptr->element->left!=NULL)
				push_node_last(&head,&tail,ptr->element->left);
			if(ptr->element->right!=NULL)
				push_node_last(&head,&tail,ptr->element->right);

			ptr = pop_node_first(&head,&tail);
		}


		push_node_last(&head,&tail,NULL);
	}

	return depth;

}
int maximum_depth_iterative_postorder(btree_node *root){
	btree_node *c = root;
	stack<btree_node *> st;
	st.push(c);
	btree_node *l_p = null;//last poped element

	int c_d = 0, m_d = 0;//current depth and max depth
	while(!st.empty()){
		c=st.top();
		//c will never be null
		if(l_p == null )
			if(c->left!=null){
				st.push(c->left);
				c_d++;
				m_d = c_d > m_d ? c_d : m_d ;
				l_p=null;
				continue;
			}

		if(l_p == c->left){
			if(c->right != null){
				st.push(c->right);
				c_d++;
				l_p=null;
			}
			else{
				l_p = st.top();st.pop();
				c_d--;
			}
		}else{
			l_p = st.top();st.pop();
			c_d--;
		}

		m_d = c_d > m_d ? c_d : m_d ;
	}

	return m_d;
}
//can we find maximum depth without using
//stack i.e via MORRIS TRAVERSAL
int maximum_depth_iterative_morris(btree_node *root){
	if(root == NULL)
		return 0;


	btree_node *current = root;
	btree_node *pre = NULL;
	int maxDepth = 0;
	int current_depth=0;

	while(current!=NULL){
		if(current->left == NULL){
			//not possible
				// while doing morris traversal
				// if c->left == null ; c= c->right; if c is not null after this we would do current_depth++
													//which is right
				//but we are going from leaf to parent i.e using a threaded link we would do current_depth++
													//which is wrong
			//verify if this is a genuine right node or a threaded link

			current = current -> right;

			if(current==null)
				continue;
			pre=current -> left;
			int pathlength = 1;
			while(pre!=null&&pre->right!=current){
				pathlength++;
				pre=pre->right;
			}

			if(pre == null)
				current_depth++;

			if(pre==current){
				pre->right = null;
				current_depth = current_depth - pathlength ;
				current = current->right;
			}


		}else{
			//find the right most node of currents left child and set
			//its right chld to current (this will be the current nodes inorder predecessor )
			pre = current->left;
			int pathlength = 0;
			while(pre->right!=NULL && pre->right!=current){
				pathlength++;
				pre = pre->right;
			}

			if(pre->right == NULL){
				pre->right = current;
				current = current->left;
				current_depth++;
			}

			else {
				pre->right = null;
				current = current->right;
				current_depth = current_depth -pathlength;
			}


		}
		maxDepth = current_depth > maxDepth ? current_depth : maxDepth;
	}
	return maxDepth;
}
//recursive method to determine size of a tree
int size_of_tree_recursive(btree_node *root){
	if(root == NULL)
		return 0;

	int a=0,b=0;
	if(root->left!=NULL)
		a = size_of_tree_recursive(root->left);

	if(root->right!=NULL)
		b = size_of_tree_recursive(root->right);

	return 1+a+b;
}
//iterative method to determine size of a tree
int size_of_tree_iterative(btree_node *root){
	if(root == NULL)
		return 0;
	///we simply use level order traversal
	//and count every non-null element in the stack

	node *head = NULL;
	node *tail = NULL;

	push_node_last(&head,&tail,root);
	push_node_last(&head,&tail,NULL);

	int count = 0;
	node *ptr = NULL;
	while(1){
		ptr = pop_node_first(&head,&tail);

		if(ptr == NULL||ptr->element == NULL)
			break;

		while(ptr->element!=NULL){
			count++;

			if(ptr->element->left!=NULL)
				push_node_last(&head,&tail,ptr->element->left);

			if(ptr->element->right!=NULL)
				push_node_last(&head,&tail,ptr->element->right);

			ptr = pop_node_first(&head,&tail);
		}

		push_node_last(&head,&tail,NULL);
	}

	return count;
}

//recursive method to test if two tree are identical
bool if_trees_identical(btree_node *root1,btree_node *root2){
	if(root1 == NULL&&root2!=NULL)
		return false;
	if(root1!=NULL&&root2==NULL)
		return false;

	if(root1 == NULL && root2 == NULL)
		return true;

	if(root1->data !=root2->data)
		return false;
	else{
		bool leftSub = if_trees_identical(root1->left,root2->left);
		bool rightSub = if_trees_identical(root1->right,root2->right);

		return leftSub&&rightSub;
	}
}
//iterative method to test if two trees are identical
//since this is a traversal problem any traversal can
//be used to check if trees are identical
bool if_trees_identical_morris(btree_node *root1,btree_node *root2){
	//using morris traversal
	btree_node *current1 = root1;
	btree_node *current2 = root2;

	btree_node *pre1 = NULL;
	btree_node *pre2 = NULL;

	while(1){
		if(current1->left == NULL){
			current1=current1->right;
		}else{
			pre1 = current1->left;
			while(pre1->right!=NULL&&pre1->right!=current1)
				pre1=pre1->right;

			if(pre1->right == NULL){
				pre1->right = current1;
				current1=current1->left;
			}

			else{
				pre1->right = NULL;
				current1 = current1->right;
			}

		}

		if(current2->left == NULL){
			current2=current2->right;
		}else{
			pre2 = current2->left;
			while(pre2->right!=NULL&&pre2->right!=current2)
				pre2=pre2->right;

			if(pre2->right == NULL){
				pre2->right = current2;
				current2=current2->left;
			}

			else{
				pre2->right = NULL;
				current2 = current2->right;
			}

		}

		if(current1 == NULL&&current2!=NULL)
			return false;
		if(current1!=NULL&&current2==NULL)
			return false;

		if(current1==NULL&&current2==NULL)
			return true;

		if(current1->data != current2->data)
			return false;
	}

	return true;

}
//the below function is to be used
//to print the mirror of the given tree
//this function  needs  in-out datastructures
void voidFunc(){

}
btree_node* convert_to_mirror(btree_node *root){
	stack<btree_node *> st;
	st.push(root);

	btree_node *c=root,*r=null,*l=null;
	btree_node *l_p = null;


	while(!st.empty()){
		c=st.top();st.pop();
		r=c->right;
		l=c->left;


		//r==null?voidFunc():st.push(r);
		//l==null?voidFunc():st.push(l);
		if(r!=null)
			st.push(r);
		if(l!=null)
			st.push(l);

		c->right = l;
		c->left = r;

	}

	return root;
}
//CONSTRUCT TREE FROM THE INORDER AND PREORDER
//since size of the inorder and preorder array
//will be the same
//we use two stack
//one two hold the array
//cotaining the right subtree
//another two hold the pointers
//to the nodes which have been
//created but their right  children
//not yet assigned
class st_array{
	public :
	int start;
	int end;
	st_array *next ;
	st_array(int a,int b){
		start = a;
		end = b;
		next = NULL;
	}
};
void push_st_array_first(st_array **head,int a,int b){
	if(*head == NULL)
		*head = new st_array(a,b);
	else{
		st_array *temp = new st_array(a,b);
		temp->next = *head;
		*head = temp;
	}
}
st_array *pop_st_array_first(st_array **head){
	if(*head == NULL)
		return NULL;
	else{
		st_array * temp = *head ;
		(*head)=(*head)->next;
		return temp;
	}
}
int search_in_array(int arr[],int element,int l,int r){
	for(int i=l;i<=r;i++)
		if(arr[i]==element)
			return i;

	return -1;

}
//complexity o(n^2)
//complexity can be brought down to
//nlogn by implying binary search
class range{
	private :
	int start;
	int end;
public:

	range(int a,int b){
		start = a;
		end = b;
	}
	int getS(){
		return start;
	}
	int getE(){
		return end;
	}
};
//O(n) devised me and simple to understand

		//idea here is to store the range of the subtrees in a stack
		//but to keep track of which elements already created in the tree
		//The stack contains two type of ranges
		// Case 1 : [L --- R+1] R+1 is the index of node whose left subtree is in [L-----R]
		// Case 2 :[L+1 --- R] L is the index of node whose right subtree is in [L+1-----R]

		//when an element is popped if L is set true then the popped range is treated
		//as such in case : 1 and case 2 depending on the value of L


		//after each iteration the value of L is chosen by the below rationale
		//A : if we could push  a right tree
		//B : if we could push  a left subtree

		//A && B : L = true
		//~A && B : L = true
		//A  && ~B : L = false
		//~A && ~B : L = false, here assuming that whichever element is on the stack the left subtree has been dealt with already

		//futther this can be merged to
		// B  : true
		// ~B :	false
//ASSUM : The whole binary Tree has different nodes
// OR The elements of inorder and preorder are distinct
btree_node *construct_tree_inorder_preorder(int inorder[],int preorder[],int size){
	//index of preorder elements in inorder array
	int inx[size];
	//el stores the pointer to the node of a particular data element in inorder array
	btree_node *el[size];
	for(int i=0;i<size;i++)
		el[i] = null;
	btree_node *current = null;
	int c=0,e=size-1,m=0,current_i=0;
	stack<range *> st;

	//if the left or right element of stack top range to be attached
	bool L=true;

	for(int i=0;i<size;i++)
		for(int j = 0;j<size;j++)
			if(preorder[i] == inorder[j])
			inx[i] = j;

		m = inx[0];
		el[m] = new btree_node(inorder[m]);

		if(m!=e)
			st.push(new range(m,e));
		if(c!=m)
			st.push(new range(c,m));
		if(c==m)
			L = false;

	for(int pre_it = 1; pre_it < size ; pre_it++){
		range * r = st.top (); st.pop() ;
		c = r->getS();e = r->getE();

		if(L){
			current_i = e;
			e = e-1;
		}else{
			current_i = c;
			c = c+1;
		}

		if(el[current_i]==null)
			el[current_i] = new btree_node(inorder[current_i]);
		m = inx[pre_it];
		if(el[m]==null)
			el[m] = new btree_node(inorder[m]);

		current = el[current_i];
		if(L)
			current->left = el[m];
		else
			current->right = el[m];

		if(m!=e)
			st.push(new range(m,e));
		if(c!=m)
			st.push(new range(c,m));
		if(c<m)
			L = true;
		else
			L = false;
	}

	return el[inx[0]];
}


//took a while to realise this

//if we just keep attaching left nodes
//storing the current and previous pointer to visitedNodes
//in each step either assign current to previous -> left or
//get something out of stack and make current -> right
//since only two scenarios are possible if we make sure to attach left nodes as we go
//then we wont have to back track for attaching left nodes i.e in forward iteration
// if we make sure no left node to be attached was left , then we need to backtrack for
//attaching right nodes
btree_node * construct_tree_inorder_preorder_simple(int inorder[],int preorder[],int size){
	int inx[size];
	stack<int> st;
	//element array holds the refrences of btree_node
	btree_node *el[size];

	for(int i=0;i<size;i++)
		for(int j = 0;j<size;j++)
			if(preorder[i] == inorder[j])
			inx[i] = j;

		btree_node *root = new btree_node(preorder[0]);
		el[0] = root;

		int current_pre_index = 0;
		int prev_pre_index = -1;

		for(int i=1;i<size;i++){
			prev_pre_index = current_pre_index;

			el[i] = new btree_node(preorder[i]);
			current_pre_index = i;

			if(inx[current_pre_index] < inx[prev_pre_index]){
				el[prev_pre_index]->left = el[current_pre_index];
				st.push(prev_pre_index);
			}else{
				while(!st.empty() && inx[current_pre_index] >= inx[st.top()]){
					prev_pre_index = st.top();
					st.pop();
				}

				el[prev_pre_index] -> right = el[current_pre_index];

			}
		}



	return root;
}
//CONSTRUCT TREE FROM INORDER AND POSTORDER
// it's the same algo as above
//but in this we process the right chld
//and put left child to be created later
//also we scan the postorder array from
//the last
//This goes with the understanding
//that postorder is reverse of preorder
//and in this reverse order
//the right node will always be encountered
//first after root
//this is why in this algo we process the right node
//and put the left subtree in the stack
btree_node *construct_tree_inorder_postorder(int inorder[],int postorder[],int size){

	int inx[size];
	//el stores the pointer to the node of a particular data element in inorder array
	btree_node *el[size];
	for(int i=0;i<size;i++)
		el[i] = null;
	btree_node *current = null;
	int c=0,e=size-1,m=0,current_i=0;
	stack<range *> st;

	//if the left or right element of stack top range to be attached
	bool L=false;

	for(int i=0;i<size;i++)
		for(int j = 0;j<size;j++)
			if(postorder[i] == inorder[j])
			inx[i] = j;

		m = inx[size-1];
		el[m] = new btree_node(inorder[m]);

		if(c!=m)
			st.push(new range(c,m));
		if(m!=e)
			st.push(new range(m,e));

		if(m==e)
			L = true;

	for(int post_it = size-2; post_it >= 0; post_it--){
		range * r = st.top (); st.pop() ;
		c = r->getS();e = r->getE();

		if(L){
			current_i = e;
			e = e-1;
		}else{
			current_i = c;
			c = c+1;
		}

		if(el[current_i]==null)
			el[current_i] = new btree_node(inorder[current_i]);
		m = inx[post_it];
		if(el[m]==null)
			el[m] = new btree_node(inorder[m]);

		current = el[current_i];
		if(L)
			current->left = el[m];
		else
			current->right = el[m];

		if(c!=m)
			st.push(new range(c,m));
		if(m!=e)
			st.push(new range(m,e));
		if(m<e)
			L = false;
		else
			L = true;
	}

	return el[inx[size-1]];

}
int locate_min_index_element(int arr1[],int arr2[],int start ,int end,int size){
	int lowest_so_far = size+1;
	for(int i=start;i<=end;i++){
		for(int j=0;j<=size-1;j++){
			if(arr2[j]==arr1[i])
				if(j<=lowest_so_far){
					lowest_so_far=j;
					break;
				}

		}
	}

	return lowest_so_far;
}
//two parallel stacks are used
//one to store the nodes
//other to store the right subtree
//start and end indices in inorder
//To decrease the complexity
//we need to construct a segment tree
//which can answer the query:
//for a given range in inorder array
//all the elements that are
//present in this range
//, which one occurs the earliest(least index)
//in the level order array
//ouput the index of this element in
//the level order array
btree_node *construct_tree_level_order_inorder(int inorder[],int levelOrder[],int size){

	queue <btree_node *> ds1;
	queue <range *> ds2;
	int indexInInorder[size];//contains the index of the element in inorder array for the index of element in level order



	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			if(inorder[j]==levelOrder[i])
				indexInInorder[i] = j;

		ds2.push(new range(0,indexInInorder[0]-1));
		ds2.push(new range(indexInInorder[0]+1,size-1));
		btree_node *root = new btree_node(levelOrder[0]);

		ds1.push(root);
		ds1.push(root);



	for(int l_i=1;l_i<size;){

		if(ds1.empty() || ds2.empty()){
			cout<<"fatal error at index "<<l_i<<endl;
			return null;
		}
		range * r = ds2.front();ds2.pop();btree_node *front = ds1.front();
		int start = r->getS();
		int end = r->getE();

		if(start > end ){
			ds1.pop();
			continue;
		}
		btree_node *temp = new btree_node(levelOrder[l_i]);

		//here it is assured that front element of ds2 i.e range contains element l_i


		int indexChild = indexInInorder[l_i];
		int indexParent = -1;
		if(start-1!=-1&&inorder[start-1]==front->data)
			indexParent = start - 1;
		if(end+1!=size&&inorder[end+1]==front->data)
			indexParent = end + 1;

		if(indexParent == -1){
			cout<<"fatal error at index "<<l_i<<endl;
			return null;
		}


		ds2.push(new range (start,indexChild-1));
		ds2.push(new range (indexChild+1,end));
		ds1.push(temp);
		ds1.push(temp);

		if(indexChild < indexParent){
			front -> left = temp;
			ds1.pop();
		}else{
			front -> right = temp;
			ds1.pop();
		}

		l_i++;
	}

	return root;
}



//ONLY APPLICABLE TO COMPLETE BINARY
//SEARCH TREE
//construct tree from level order
//THIS ALGO CAN BE USED FOR BINARY
//SEARCH TREE I.E LEFT CHILD LESS
//THAN ROOT AND OPP. FOR LEFT CHILD
//The complexity is O(n)
//since each element in the
//array is processed once
btree_node *construct_tree_level_order(int lv[],int size){
	node *head = NULL;
	node *tail = NULL;

	int i=0;
	btree_node *root=NULL,*current=NULL;

	while(i!=size){
		if(i==0){
			root = new btree_node(lv[0],NULL,NULL);
			current = root;
			i++;
		}else{
			if(head == NULL)
				return root;
			current = pop_node_first(&head,&tail)->element;
		}

		if(lv[i]<=current->data){
			current->left = new btree_node(lv[i],NULL,NULL);
			push_node_last(&head,&tail,current->left);
			i++;
			if(lv[i]>current->data){
				current->right = new btree_node(lv[i],NULL,NULL);
				push_node_last(&head,&tail,current->right);
				i++;
			}
			continue;
		}

		if(lv[i]>current->data){
			current->right = new btree_node(lv[i],NULL,NULL);
			push_node_last(&head,&tail,current->right);
			i++;
		}

	}

	return root;

}

//prints all the root-leaf path
//algorithm followed is simply
//taking the algo for morris traversal
//and where ever a leaf is implied
//print the path array
//also empty the path array whenever
// a root is visited
void print_root_leaf_morris(btree_node *root){
	if(root == NULL)
		return;
	int depth = maximum_depth_iterative_morris(root);
	int path_array[depth];
	int last=0;
	path_array[last]=root->data;
	btree_node *current=root;
	while(current!=NULL){
		if(current->left==NULL){
			current = current->right;
			//since left and right are both NULL
			if(current == NULL){
				for(int i=0;i<=last;i++)
					cout<<path_array[i]<<" ";
				cout<<endl;
			}

			if(current!=NULL)
			path_array[++last]=current->data;;
		}else{
			btree_node *pre = current->left;

			while(pre->right!=NULL&&pre->right!=current)
				pre=pre->right;

			if(pre->right==NULL){
				pre->right = current;
				current=current->left;
				path_array[++last]=current->data;
			}

			else{

				//The condition of leaf hold when
				//right and left are both NULL
				//pre->right == current
				//implies without this, this node
				//was a leaf
				if(pre->left == NULL){
					for(int i=0;i<last;i++)
						cout<<path_array[i]<<" ";
					cout<<endl;
				}

				//time to remove some elements
				//the root must have been added to
				//the path_arry
				//when current=current->right
				last--;
				pre = current->left;
				last--;
				while(pre->right!=current){
					last--;
					pre=pre->right;
				}
				pre->right = NULL;
				current = current->right;
				if(current!=NULL)
					path_array[++last]=current->data;



			}
		}


	}
}
//
void print_lCA_morris(btree_node *root,int key1, int key2){
	if(root == NULL)
		return;
	int depth = maximum_depth_iterative_morris(root);
	int pth_arr_aux[depth];
	int pth_arr_prim[depth];
	int last_aux=0;
	int last=0;
	pth_arr_prim[last]=root->data;
	bool found1=false,found2=false;
	btree_node *current = root;
	while(current!=NULL){
		if(current->data == key1){
			if(!found1&&!found2){
				found1 = true;

				for(int i=0;i<=last;i++){
					pth_arr_aux[i]=pth_arr_prim[i];
					last_aux=i;
				}

			}else if(found2 == true){
				break;
			}
		}


		if(current->data==key2){
			if(!found1&&!found2){
				found2 = true;

				for(int i=0;i<=last;i++){
					pth_arr_aux[i]=pth_arr_prim[i];
					last_aux=i;
				}
			}
			else if(found1 == true){
				break;
			}
		}




		if(current->left == NULL){
			current = current->right;
			if(current!=NULL)
				pth_arr_prim[++last]=current->data;
		}else{
			btree_node *pre = current->left;

			while(pre->right!=NULL&&pre->right!=current)
				pre=pre->right;


			if(pre->right == NULL){
				pre->right = current;
				current = current->left;
				pth_arr_prim[++last]=current->data;
			}

			else{
				//in this path
				//where pre->right = current
				//first and the last element are the root
				//of this path
				last--;

				pre=current->left;
				last--;
				while(pre->right!=current){
					last--;
					pre = pre->right;
				}
			}
		}
	}

	if(found1||found2){
		cout<<"One of the keys is not present in the tree"<<endl;
		return;
	}

	///find the element from the last
	//which is common to both the path arrays
	//and print it
}


//finds the size of largest BST subtree in a bst
//RECURSIVE METHOD
//helper
int find_largest_bst_subtree_finder(btree_node *root,int *max_value,int *min_value,bool *is_bst,int *largest_size_bst){


	if(root==NULL){
		*max_value=INT_MIN;
		*min_value=INT_MAX;
		*largest_size_bst=0;
		*is_bst=true;
		return 0;
	}

	int left_sub_bst_size = find_largest_bst_subtree_finder(root->left,max_value,min_value,is_bst,largest_size_bst);

	int left_sub_max = *max_value;
	int left_sub_min = *min_value;
	bool left_sub_is_bst = *is_bst;
	int left_sub_largest_size_bst = *largest_size_bst;

	*max_value=INT_MIN;
	*min_value=INT_MAX;
	*largest_size_bst=0;
	*is_bst=false;

	int right_sub_bst_size = find_largest_bst_subtree_finder(root->right,max_value,min_value,is_bst,largest_size_bst);

	int right_sub_max = *max_value;
	int right_sub_min = *min_value;
	bool right_sub_is_bst = *is_bst;
	int right_sub_largest_size_bst = *largest_size_bst;

	if(right_sub_is_bst&&left_sub_is_bst&&left_sub_max<root->data&&right_sub_min>root->data){
		*largest_size_bst=left_sub_largest_size_bst+right_sub_largest_size_bst+1;
		*is_bst = true;
	}else{
		*largest_size_bst = left_sub_bst_size>right_sub_bst_size?left_sub_bst_size:right_sub_bst_size;
		*is_bst = false;

	}
		*max_value=right_sub_max>left_sub_max?right_sub_max:left_sub_max;
		*max_value=(*max_value)>root->data?(*max_value):root->data;
		*min_value=right_sub_min<left_sub_min?right_sub_min:left_sub_min;
		*min_value=(*min_value)<root->data?(*min_value):root->data;



	return *largest_size_bst;
}
//function
int find_largest_bst_subtree(btree_node *root){
	int max_value = INT_MIN;
	int min_value = INT_MAX;
	bool is_bst=false;
	int largest_size_bst = 0;
	return find_largest_bst_subtree_finder(root,&max_value,&min_value,&is_bst,&largest_size_bst);
}
//iterative solution : unable to find
int main(int argc, char const *argv[])
{
	// btree_node *root = NULL;
	// exact_tree_input(&root);
	// print_reg(root);

	/*convert_to_mirror(root);
	print_reg(root);*/
	/*int node_value;
	cin >> node_value;
	cout <<"height is = "<<height(search(root,node_value))<<endl;*/
	//print_level_order_newline_recursive(root);
	//cout << maximum_depth_iterative_morris(root) <<endl;
	// inorder_morris_traversal(root);
	// cout<<endl;
	// print_level_order_newline(root);
	// cout<<endl;

	int size; cin >>size;
	int inorder[size];
	int preorder[size];
	for(int i=0;i<size;i++)
		cin >> inorder[i];
	for(int i=0;i<size;i++)
		cin >> preorder[i];

	btree_node *root = construct_tree_inorder_preorder(inorder,preorder,size);

	print_reg(root);

	root = construct_tree_inorder_preorder_simple(inorder,preorder,size);

	cout << " ----------------------      "<<endl;
	print_reg(root);
	return 0;
}
