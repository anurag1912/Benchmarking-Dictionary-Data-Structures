#include<iostream>
#include<stdlib.h>
#include<string>
#include<algorithm>
#include<fstream>
#define MAX(A,B) ((A)>(B)?(A):(B))
struct Node{
	Node *parent;
	Node *left;
	Node *right;
	std::string key;	
	long long height;
};
//Node * search(int, Node *);
Node * insert(Node *, Node *);
void inordertraversal(Node *);
//void deleteNode(int, Node *);
int maxHeight(Node *);
void rotation(Node *, int);
void leftrotate(Node *);
struct Node *head = NULL;
void doubleleftrotate(Node *);
void rightrotate(Node *);
void doublerightrotate(Node *);
int main()
{
//	std::string arr[] = {"Anurag", "Mashruwala", "Mashruwala"};
	//int arr[] = {3,1,5};
	
	struct Node *temp1 = NULL;
	std::ifstream fin("Database.txt");
	if(!fin.is_open())
	{
	
		std::cout<<"Cannot open file! Terminating...\n";
		return 1;
	}	
	std::string s;
	std::string temp;
	int i; unsigned long count =0;
	while(getline(fin,s))
	{		
		
	i=0;
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
					if(count==0)
					head = insert(head, temp1);
					else
					insert(head, temp1);
					temp.clear();
					count++;
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
	if(count==0)
	head = insert(head, temp1);
	else
	insert(head, temp1);
		count++;
	}
	//std::cout<<"Number of words = "<<count<<"\n";
	
	fin.close();

//inordertraversal(head);
	//print(head);
	return 0;
}
Node * insert(Node *head, Node *temp){
	
		
	if(head==NULL) {
	head = temp;
	head->left=NULL;
	head->parent=NULL;
	head->right = NULL;
	head->height = 0;
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
	
	
	
	
	
	
	
	while(temp!=NULL)
	{
		
		
	if(temp->left==NULL && temp->right == NULL)	{
		
		temp->height = 0; 
		
		
	}
	else {
		
	if(temp->left==NULL){
		temp->height = ((temp->right->height>-1)?temp->right->height:-1) + 1;
		if(abs(-1 - temp->right->height)>1)
		{rotation(temp, -1);
		//std::cout<<"in here\n";
		break;
		}
		
		
	}	
	else if(temp->right==NULL) {
		temp->height = ((temp->left->height>-1)?temp->left->height:-1) + 1;
		if(abs(temp->left->height -  (-1))>1)
		{rotation(temp,1);
		break;
		}
		
		
		
	}	
	
	else {
		temp->height = ((temp->left->height>temp->right->height)?temp->left->height:temp->right->height) + 1;
		if(abs(temp->left->height - temp->right->height)>1)
		{rotation(temp, (temp->left->height - temp->right->height));
		break;
		}
		
		
	}
	}	
	temp = temp->parent;	
	}
	
	return head;
	
	
		
	
}
void rotation(Node *temp, int heavy)
{
if(heavy>0){
Node *left = temp->left;
if(left->left!=NULL && left->right!=NULL)
{
	int balance = left->left->height - left->right->height;
	if(balance<0)
{	doublerightrotate(left);
	rightrotate(temp);
}
	else {
	
	rightrotate(temp);
}
}


else if(left->left==NULL) {
doublerightrotate(left);
rightrotate(temp);	
	
	
}
else {
	rightrotate(temp);	
}

}	
else{
	//std::cout<<"CCCC\n";
Node *right = temp->right;
if(right->left!=NULL && right->right!=NULL)
{	//std::cout<<"AAAAA\n";
	int balance = right->left->height - right->right->height;
	if(balance<0)
	leftrotate(temp);
	else 
	{doubleleftrotate(right);
	leftrotate(temp);
	}
}


else if(right->left==NULL) {
	//std::cout<<"BBBBB\n";
	leftrotate(temp);	
	
	
}
else {
	doubleleftrotate(right);
	leftrotate(temp);	
	
}
	
	
}
}
void doublerightrotate(Node* C) {
	
	Node *B = C->right;
	//---------------------------------I-------------------------------------//
	
		C->parent->left = B;
		B->parent = C->parent;
	
	//---------------------------------I-------------------------------------//
	
	//---------------------------------II-------------------------------------//
		C->right = B->left;
		if(B->left!=NULL)
			B->left->parent = C;
	//---------------------------------II-------------------------------------//
	
	//---------------------------------III-------------------------------------//
		C->parent = B;
		B->left = C;
	//---------------------------------III-------------------------------------//
	
}
void doubleleftrotate(Node* C)
{	
	Node *B = C->left;
	//--------------------------I---------------------------//
		
		C->parent->right =B;
		B->parent = C->parent;
				
	//--------------------------I---------------------------//
	
	//--------------------------II---------------------------//
		C->left = B->right;
		if(B->right!=NULL)
		B->right->parent = C;
		
	//--------------------------II---------------------------//
	
	//--------------------------III---------------------------//
	
		C->parent = B;
		B->right = C;
	
	//--------------------------III---------------------------//

}	
void leftrotate(Node *A)
{	

	Node*B = A->right;
	B->parent = A->parent;
	
	if(A==head)
	{

	head = B;
	}
	else
	{	if(A->parent->left==A)
		A->parent->left = B;
		else
		A->parent->right = B;
	}
	 A->right = B->left;
	if(B->left!=NULL)
	B->left->parent= A;
	A->parent = B;
	
	B->left = A;
	
	maxHeight(B);

}
	
	
void rightrotate(Node * A) {

	Node *B = A->left;
	//--------------------I---------------------------//
	if(A==head) {
		head = B;
	}
	else {
		
		if(A->parent->left==A)
		A->parent->left=B;
		else
		A->parent->right = B;
	}
	B->parent = A->parent;
	//--------------------I---------------------------//
	
	//--------------------II---------------------------//
	
		A->parent = B;
	
		A->left = B->right;
		B->right = A;
		if(A->left!= NULL)
		A->left->parent = A;
	//--------------------II---------------------------//
	maxHeight(B);
	
}	
	

void inordertraversal(Node *h)
{
	if(h->left!=NULL)
	{
	inordertraversal(h->left);
}
	std::cout<<h->key<<" Height = "<<h->height<<" ";
	if(h->parent!=NULL)
	std::cout<<"Parent key = "<<h->parent->key<<"\n";
	else
	std::cout<<"\n";
	if(h->right!=NULL)
	{
	inordertraversal(h->right);
	}
/*


	if(h->left!=NULL)
	{std::cout<<"H->key"<<h->key<<"\n";
	inordertraversal(h->left);
	}
	std::cout<<".....\n";
	std::cout<<h->key<<" Height = "<<h->height<<"\n";
	if(h->right!=NULL)
	{ std::cout<<"H->key: "<<h->key<<"\n";
	inordertraversal(h->right);
	}
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
int maxHeight(Node *temp)
{	
	if(temp==NULL)
		return -1;
	
	else
		{
		temp->height =  MAX(maxHeight(temp->left), maxHeight(temp->right)) +1 ; 
		return temp->height;
}
}
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
