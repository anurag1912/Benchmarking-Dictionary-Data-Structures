#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
struct Node{
	Node *parent;
	Node *left;
	Node *right;
	std::string key;	
};
Node * search(int, Node *);
Node * insert(Node *, Node *);
void inordertraversal(Node *);
void deleteNode(int, Node *);
int main()
{
	//std::string arr[] = {"Anurag", "Mashruwala", "Anurag"};
	//int arr[] = {3,1,5};
	struct Node *head = NULL;
	struct Node *temp1 = NULL;
	
	std::ifstream fin("Database.txt");
	if(!fin.is_open())
	{
	
		std::cout<<"Cannot open file! Terminating...\n";
		return 1;
	}	
	std::string s;
	std::string temp;
	int i; //unsigned long count =0;
	while(getline(fin,s))
	{	i=0;
		while(s[i])
		{	
		

		

		
	

			if(s[i]>='A' && s[i]<='Z' || s[i]>='0'&&s[i]<='9'||s[i]>='a' && s[i]<='z')
				temp += s[i++];
			else
			switch(s[i]) {
				case '-':
				
				case '\'':
				{	if(!temp.empty())
						temp+=s[i];
					
					
					i++;
					break;
				}
					
				default: {
					if(!temp.empty())
					{
					temp1 = new Node;
					std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
					temp1->key= temp;
					temp1->left=NULL;
					temp1->parent=NULL;
					temp1->right=NULL;
					head = insert(head, temp1);

					
					temp.clear();
					//count++;
					}
					i++;
					break;
				}
				
					
			}			
		}
	
	}
	if(!temp.empty()){
	temp1 = new Node;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	temp1->key= temp;
	temp1->left=NULL;
	temp1->parent=NULL;
	temp1->right=NULL;
	head = insert(head, temp1);
	//count++;
	}
	//std::cout<<"Number of words = "<<count<<"\n";
	
	fin.close();
	
/*
	deleteNode(5,head);
	deleteNode(4,head);
	deleteNode(3,head);
	deleteNode(2,head);
	deleteNode(10,head);
	deleteNode(6, head);
*/
	//inordertraversal(head);
	return 0;
}
Node * insert(Node *head, Node *temp){
	
		
	if(head==NULL) {
	head = temp;
	head->left=NULL;
	head->parent=NULL;
	head->right = NULL;
	return head;
	}

	Node *ptr =head;
	Node *parent;
	while(ptr!=NULL) {
		
		if(temp->key<ptr->key) {
		parent = ptr;
		ptr = ptr->left;
		}
		else if(temp->key>ptr->key) {
		parent = ptr;
		ptr = ptr->right;
		}
		else
		return head;
	}		
	if(temp->key<parent->key)
	parent->left=temp;
	else
	parent->right = temp;
	temp->parent = parent; 
	
	return head;
	
	
	
}

void inordertraversal(Node *h)
{

	if(h->left!=NULL)
	{
	inordertraversal(h->left);
}
	std::cout<<h->key<<" ";
	if(h->parent!=NULL)
	std::cout<<"Parent key = "<<h->parent->key<<"\n";
	else
	std::cout<<"\n";
	if(h->right!=NULL)
	{
	inordertraversal(h->right);
	}


/*
	Node *temp;
	if(head->left!=NULL)
	inordertraversal(head->left);
	std::cout<<head->key<<"    ";
	if(head->parent!=NULL)
	std::cout<<"Head key = "<<head->parent->key<<"\n";
	else
	std::cout<<"\n";
	if(head->right!=NULL)
	inordertraversal(head->right);
*/	
	
}
/*
Node * search(int no, Node *head)
{	while(head!=NULL)
 		{
		 if(no<head->key)
 			head = head->left;
 		 else if(no>head->key)
 			head = head->right;
 		else return head;
 	}
	
	return NULL;
}
*/
/*
void deleteNode(int no, Node *head)
{
	
	Node *ptr = search(no, head);
	if(ptr!=NULL)
	{	Node *temp = ptr;

		if(ptr->left!=NULL && ptr->right!=NULL)
		{
			ptr = ptr->left;
			while(ptr->right!=NULL)
			ptr=ptr->right;
			
			temp->key = ptr->key;
		
			if(ptr->left!=NULL)
			{	
				temp = ptr;
				ptr = ptr->parent;
				if(ptr->left==temp)
				{
					
					ptr->left = temp->left;
					temp->left->parent = ptr;
					
				}
				else
				{	
					
					ptr->right = temp->left;
					temp->left->parent = ptr;
					
					
					
				}
					delete temp;
			
			}
			
			
			
			else
			{	temp = ptr;
				ptr = ptr->parent;
				if(ptr->left==temp)
				{	
				
					ptr->left=NULL;
									

				}
				
				else
				{	
												

					ptr->right=NULL;

				}
					delete temp;
			}
		}
		else if(ptr->left!=NULL){
			
			ptr = ptr->parent;
			if(ptr->left==temp) {
				
				ptr->left = temp->left;
				temp->left->parent = ptr;
				
				
			}
			else {
				
				ptr->right = temp->left;
				temp->left->parent = ptr;
				
			}
			delete temp;
		}
		else if(ptr->right!=NULL){
			
			ptr = ptr->parent;
			if(ptr->left==temp) {
				
				ptr->left = temp->right;
				temp->right->parent = ptr;
				
				
			}
			else {
				
				ptr->right = temp->right;
				temp->right->parent = ptr;
				
			}
			delete temp;
		}	
			
			
		
		
		else{
			
			
			ptr = ptr->parent;
			if(ptr->left==temp){
				
				ptr->left=NULL;
				
			}
			else
				ptr->right=NULL;
			delete temp;
		}
		
}
	}
	
	
*/
