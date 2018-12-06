#include<iostream>
#include<cstring>
using namespace std;
template<class T>
struct Bnode
{
	T data;
	Bnode<T> *lchild;
	Bnode<T> *rchild;
 };
 
 template<class T>
 class Btree
 {
 	public: 
 		static T count;
	 Bnode<T> *root;
 	
 		Btree(){
 			count=0;
 			root=NULL;
		}
	 void preOrder(Bnode<T> *anode)
		{
			 Bnode<T> *help=anode;
			if(help!=NULL)
			{  cout<<"这是第"<<++count<<" : ";
				cout<<help->data<<" ; ";
				preOrder(help->lchild);
				preOrder(help->rchild);
			}
		}
		void addnode1(Bnode<T> *temp)
		{		
			if(root==NULL)
 		{
 			cout<<"到现在为止还是空的"<<endl; 
 			root=temp;
		 }
		 else
		 {
		 	Bnode<int> *back;
		 	Bnode<int> *current=root;
		 	while(current!=NULL)
		 	{
		 		back=current;//记录下最后一个位置，便于找回，并在此处赋值 
		 		if(current->data>temp->data)
		 		{
		 			current=current->lchild;
				 }
				 else
				 {
				 	current=current->rchild;
				 }
			 }
			 if(back->data>temp->data)
			 {
			 	back->lchild=temp; 
			 }
			 else
			 {
			 	back->rchild=temp;
			 }
		 }
		}
 
 	void addnode2(Bnode<T> **temp,T key)
 	{
 	
 		Bnode<T> *newnode=new Bnode<T>;
		newnode->data=key;
		newnode->rchild=newnode->lchild=NULL;
		*temp=newnode;
		cout<<(**temp).data<<endl;
	 }
 };
 template<class T>
 T Btree<T>::count=0;
 
 int main()
 {
 	Btree<int> atest;
 	
 	atest.addnode2(&atest.root,666);
 	int n;
 	cin>>n;
 	while(n--)
 	{
 		Bnode<int> *temp=new Bnode<int>;
 		cin>>temp->data;
 		temp->rchild=NULL;
 		temp->lchild=NULL;
 		atest.addnode1(temp);
 		
	 }
 	atest.preOrder(atest.root);
 	cout<<"Asd"<<endl;
 	//atest.addnode2(atest.root)
 	atest.preOrder(atest.root->rchild); 
 	
 	return 0;
 }
