#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
#define null NULL
int max (int a,int b){
	if(a>b)
		return a;
	else
		return b;
}
class node{
public:
	int data ;
	node *next ;
	node(int data){
		this->data = data ;
		next = NULL ;
	}
} ;
void print_list(node *head){

	if(head == NULL)
		return;
	node* temp = head;
	while(temp!=NULL){
		cout<<"[ "<<temp->data<<" ] --> ";
		
		temp = temp->next;
	}
	cout<<endl;
}
void insert_at_tail(node **head,int value){
	if(*head==NULL){
		*head = new node(value);
		return;
	}

	node* temp = *head;
	while(temp->next!=NULL){
		temp = temp->next;
	}

	temp->next=new node(value);

}
void insert_at_head(node **head,int value){
	if((*head) == NULL){
		*head = new node(value);
		return ;
	}

	node* temp = *head;
	*head = new node(value);
	(*head)->next = temp;
	return;

}
void insert_at_postition(node** head,int position,int value){
	//if position is greater than equal to size+1
	//the function returns
	if(position==1){
		insert_at_head(head,value);
		return;
	}

	node* current = *head;
	node* prev = NULL;
	int pos = 1;
	while(current!=NULL){
		if(pos == position){
			prev->next = new node(value);
			prev->next->next = current;
			return;
		}
		prev=current;
		current=current->next;
		pos++;
	}
	
	if(pos==position){
		prev->next = new node(value);
	}

}
node* search(node* head,int key){
	if(head == NULL)
	return NULL;

	node* temp = head;
	while(temp!=NULL){
		if(temp->data = key)
			return temp;
		temp=temp->next;
	}

	return NULL;
}
void delete_at_tail(node **head){
	if(*head==NULL){
		return;
	}

	node* temp = *head;
	while(temp->next->next!=NULL){
		temp = temp->next;
	}
	temp->next=NULL;
}
void delete_at_head(node **head){
	if(*head == NULL)
		return ; 
	
	*head = (*head)->next;
	return ;

}
void delete_at_postition(node** head,int position){
	if(*head == NULL)
		return;

	if(position==1){
		*head=(*head)->next;
		return;
	}
	node* current = *head;

	node* prev = NULL;
	int pos = 1;
	while(current!=NULL){
		if(pos == position){
			prev->next = current->next;
			return;
		}
		prev=current;
		current=current->next;
		pos++;
	}

}

node* input_list(){
	int size;
	cin>>size;
	int i=0;
	node* head = NULL;
	node *temp =NULL;
	while(i!=size){
		int value;
		cin>>value;
		if(head==NULL){
			head = new node(value);
			temp=head; 
		}else{
			temp->next = new node(value);
			temp=temp->next;

		}
		i++;
	}
	return head;
}
int countCommon(node *a,node *b){
	int count = 0;
	for(;a&&b;a=a->next,b=b->next)
		if(a->data == b->data)
			count++;
		else
			break;

		return count;
}
void find_longest_palindrome(node *head){
	///within a linked list find longest palindrome
	
	node *current = head;
	node *prev = NULL;
	int result =0;
	while(current){
		//point current to previous
		//store the pointer current next in next
		node *next = current->next;
		current->next = prev;

		//at this point the palindrome can be odd
		//if prev to head (reverse iteration) and next to tail
		//are compared against
		result = max(result,2*countCommon(prev,next)+1);

		//the palidrome will be even (if so)
		//current to head and next to tail are compared
		result = max(result,2*countCommon(current,next));

		prev = current;
		current = next;
	}

	cout<<"The longest palidrome is of length "<<result<<endl;


}

void exchange_two_keys_simple(node **head,int key1,int key2){
	//ASSUM both the keys are in the list

	//get the node of both the keys and previous of the first node(key1) || node (key2)
	//whichever is first
	node *n1 = null,*prev_n1 = null,*prev_n2 = null,*n2 = null,*temp = *head;
	while(temp!=null){
		if((temp->data == key1 || temp->data == key2)) {
				if(n1 == null)
				n1 = temp;
				else
				n2 = temp;
		}
		if(n1==null)
			prev_n1 = temp;
		else if(n2==null)
			prev_n2 = temp;
		else
			break;
		temp = temp -> next;
	}

	if(n1->next == n2){
		if(prev_n1!=null){
			prev_n1 -> next = n2;
		}else{
			*head = n1->next;
		}
			n1 -> next = n2->next;
			n2->next = n1;
	}else{

		//prev_n2 can not be null dettach n2
		prev_n2->next = n2->next;
		//detach m1
		if(prev_n1 == null){
			*head = (*head)->next;
			n2->next = *head;
			*head = n2;
			
		}else{
			prev_n1->next = n1->next;
			n2->next = prev_n1->next;
			prev_n1->next = n2;
		}
		n1->next = prev_n2->next;
		prev_n2->next = n1;
	}

	
	
}
int main(int argc, char const *argv[])
{
	node* head = input_list();
	//find_longest_palindrome(head);
	int key1,key2;
	cin>>key1>>key2;
	exchange_two_keys_simple(&head,key1,key2);
	print_list(head);
	return 0;
}