#include<iostream>
#include<cstring>
using namespace std;
class LinkList;
class Node
{
	public:
	int data;
	Node *next;
	Node *last;
};

class LinkList
{
		Node *head;
		Node *tail;
		int length;
	public:
		LinkList()
		{
			head=new Node;
			head->next=NULL;
			length=0;
		}
		/*~LinkList()
		{
			Clear();
			delete head;
		}
		*/
		//LinkList(const LinkList &copy)
		//{//利用判断长度加插入函数
		//}
		int Length()
		{
			int count=0;
			Node *tmpPtr=head->next;
			while(tmpPtr)
			{
				count++;
				tmpPtr=tmpPtr->next;
			}
			return count;
		 } 
		void PushBack(int temp)
		{
			Node *p=head->next;
			Node *newPtr;
			newPtr=new Node;
			newPtr->data=temp;
			newPtr->next=NULL;
			while(p)
			{
				p=p->next;
				cout<<"@22"<<endl;
			}
			p->next=newPtr;
			cout<<"@33"<<endl;
		}
		void Clear()
		{
			head->next=NULL;
		}
};
int main()
{
	LinkList ll;
	cout<<ll.Length();
	ll.PushBack(2);
	cout<<ll.Length();
	return 0;
}


