#include<iostream>
#include<cstring>
using namespace std;
template<class ElemType>
class Node
{
	public:
		ElemType data;
		Node<ElemType> *next;
		Node()
		{
			next=NULL;
		}
		Node(ElemType item,Node<ElemType> * link =NULL)
		{
			data=item;
			next=link;
		}
};

template<class ElemType>
class LinkList
{
	public:
	Node<ElemType> *head;
	Node<ElemType> *GetElemPtr(int position)const;
	void Init();
	
	LinkList()
	{
		Init();
	}
	virtual ~LinkList();
	int Length()const;
	bool Empty()const;
	void Clear();
	void Traverse(void (*vist)(const ElemType &)) const;
	int GetElem(int position,ElemType &e)const;
	int SetElem(int position,const ElemType &e);
	int Delete(int position,ElemType &e);
	int Insert(int position,const ElemType &e);
	LinkList(const LinkList<ElemType>&copy);
	LinkList<ElemType>&operator=(const LinkList<ElemType>&copy);
};

template<class ElemType>
Node<ElemType> *LinkList<ElemType>::GetElemPtr(int position)const
{
	Node<ElemType> *tmpPtr=head;
	int curPosition=0;
	while(tmpPtr!=NULL&&curPosition<position)
	{
		tmpPtr=tmpPtr->next;
		curPosition++;
	}
	if(tmpPtr!=NULL&&curPosition==position)
	{
		return tmpPtr;
	}
	else
	{
		return NULL;
	}
}

template<class ElemType>
void LinkList<ElemType>::Init()
{
	head=new Node<ElemType>;//且之前已经定义了Node的无参构造函数此时的HEAD->NEXT=null； 
}

template<class ElemType>
LinkList<ElemType>::~LinkList()
{
	Clear();
	delete head;
}

template<class ElemType>
int LinkList<ElemType>::Length() const
{
	int count=0;
	for(Node<ElemType> *tmpPtr=head->next;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
	{
		count++;
	}
	return count;
}

template<class ElemType>
bool LinkList<ElemType>::Empty()const
{
	return head->next==NULL;
}

template<class ElemType>
void LinkList<ElemType>::Clear()
{
	ElemType tmpElem;
	while(Length()>0)
	{
		Delete(1,tmpElem);
	}
}

template<class ElemType>
void LinkList<ElemType>::Traverse(void (*visit)(const ElemType &))const
{
	for (Node<ElemType>*tmpPtr=head->next;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
	{
		(*visit)(tmpPtr->data);
	}
}

template<class ElemType>
int LinkList<ElemType>::GetElem(int position, ElemType &e)const
{
	if(position<1||position>Length())
	{
		return 0;
	}
	else
	{
		Node<ElemType> *tmpPtr;
		tmpPtr=GetElemPtr(position);//取出指向第position个结点的指针
		e=tmpPtr->data;
		return 1; 
	}
}

template<class ElemType>
int LinkList<ElemType>::SetElem(int position,const ElemType &e)
{
	if(position<1||position>Length())
	{
		return 0;
	}
	else
	{
		Node<ElemType> *tmpPtr;
		tmpPtr=GetElemPtr(position);
		tmpPtr->data=e;
		return 1;
	}
}

template<class ElemType>
int LinkList<ElemType>::Insert(int position,const ElemType &e)
{
	if(position<1||position>Length()+1)
	{
		return 0;
	}
	else
	{
		Node<ElemType> *tmpPtr;
		tmpPtr=GetElemPtr(position-1);
		Node<ElemType> *newPtr;
		newPtr=new Node<ElemType>(e,tmpPtr->next);
		tmpPtr->next=newPtr;
		return 1;
	}
}

template<class ElemType>
int LinkList<ElemType>::Delete(int position,ElemType &e)
{
	if(position<1||position>Length())
	{
		return 0;
	}
	else
	{
		Node<ElemType> *tmpPtr;
		tmpPtr=GetElemPtr(position-1);
		e=tmpPtr->next->data;
		tmpPtr=tmpPtr->next->next;	
		return 1;
	}
}


int main()
{
	LinkList<int> a;
	cout<<a.Insert(1,1);
	cout<<endl;
	cout<<a.Length();
		
	return 0;
}

