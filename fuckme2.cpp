#include<iostream>
using namespace std;

class Node{
	public:
		int data;
		Node *next;
		Node *last;
		Node()
		{
			data=0;
			next=NULL;
			last=NULL;
		}
		Node(int item,Node *link=NULL)
		{
			data=item;
			next=link;
			last=link;  
		}
};
class LinkList{
	private:
		Node *Head;
		int length;
	public:
		LinkList()
		{
			Head=new Node;
			Head->next=NULL;
			Head->last=NULL;
			length=0;
		}
		Node *GetHead()
		{
			return Head;
		}
		int Length()
		{
			return length;
		}
		void PushBack(int i)
		{
			Node *tail=Head;
			while(tail->next!=NULL)
			{
				tail=tail->next;
			}
			Node *temp=new Node;
			temp->data=i;
			temp->next=NULL;
			tail->next=temp;
			temp->last=tail;
			tail=temp;
			//tail->next=NULL;
			length++;
		}
		void shift()
		{	
			Node *node=new Node;
			Node *pre=new Node;
			pre=NULL;
			node=Head->next;
			while(node!=NULL)
			{
				//cout<<"###"<<endl;
				Node *pnext=node->next;
				node->next=pre;
				pre=node;
				node=pnext;
			}
			Head= new Node;
			Head->next=pre;	
		}
		void Insert(int pos,int e)
		{
			if(pos<1||pos>Length()+1)
			{
				cout<<"请输入正确的插入位置"<<endl; 
			}
			else
			{
				int curp=1;
				Node *curptr=new Node;
				curptr=Head->next;
				while(curptr&&curp<pos-1)
				{
					curptr=curptr->next;
					curp++;
				}
				Node *newnode=new Node;
				newnode->data=e;
				newnode->next=curptr->next;
				curptr->next=newnode;
				cout<<"此次插入成功"<<endl;
			}
		}
		int Delete(int i);
		int GetData(int i);
		int Search(int obj);
		void Display()
		{
			if(length==0)
			{
				cout<<"此时链表为空"<<endl;
			}
			Node *p=new Node;
			p=Head->next;
			while(p!=NULL)
			{
				cout<<p->data<<endl;
				p=p->next;
			}
		}
};
int main()
{
	LinkList a;
	cout<<"请输入你期望的链表长度"<<endl;
	int n;
	cin>>n;
	int i=0;
	while(n--)
	{
		i++;
		cout<<"请输入你希望的第 "<<i<<" 个结点值 "<<endl;
		int temp;
		cin>>temp;
		a.PushBack(temp);
	 } 
	a.Insert(2,233);
	
	a.Display();
	a.shift();
	cout<<"change"<<endl;
	a.Display();
	return 0;
}
