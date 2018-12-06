#include<iostream>
using namespace std;
class Node
{
	public:
		int data;
		Node *next;
		Node()
		{
			data=0;
			next=NULL;
		}
		Node(int e)
		{
			data=e;
			next=NULL;
		}
};

class LinkList
{
	Node *head;
	int length;
	public:
		LinkList()
		{
			head=new Node;
		}
		void add(int t)
		{
			Node *p,*q,*t;
			t=new Node(t);
			Node *node;
			 
		}
		
};

int main()
{
	LinkList a;
	a.add(1);
	return 0;
}
