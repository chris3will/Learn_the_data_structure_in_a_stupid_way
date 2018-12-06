#include<map>
#include"queue"
#include"iostream"
#include"algorithm"
#include"utility"
#include<cstring>
#include<vector>
using namespace std;
typedef vector<bool> Huff_code;





using namespace std;

template<class T>
class TreeNode
{
	private:
		T element;
	public:
		TreeNode<T> *lchild;
		string code;
		TreeNode<T> *rchild;
		TreeNode(T elem):element(elem),lchild(NULL),rchild(NULL){}
		bool AddL(TreeNode<T> &lnew);
		bool AddR(TreeNode<T> &rnew);
		template<class C>
		friend void preorder(TreeNode<C> *t);
		
		template<class C>
		friend void pre(TreeNode<T> *t);
};

template<class T>
void preorder(TreeNode<T> *t){
    if(t){
        cout<<t->element<<endl;
        preorder(t->lchild);
        preorder(t->rchild);
    }

}
template<class T>
void pre(TreeNode<T> *t)
{
	if(t){
		cout<<t->code<<endl;
		pre(t->lchild);
		pre(t->rchild);
	}
}

template<class T>
class wei_in_pair;


template<class T>
class TreeNode_Weight:public TreeNode<T>
{
	friend class wei_in_pair<T>;
	private:
		
		
		int weight;
	public:
		TreeNode_Weight(T elem,int wei):TreeNode<T>(elem),weight(wei){}
		TreeNode_Weight* operator+(TreeNode_Weight<T> &elem){
			return new TreeNode_Weight('\0',this->weight+elem.weight);
		}
		int GetWeight() const
		{
			return this->weight;
		}
};

template<class T>
class wei_in_pair
{
	template<class C>
	friend bool operator >(wei_in_pair<C> a,wei_in_pair<C> b);
	private:
		pair<int,TreeNode_Weight<T>*> elem;
	public:
		wei_in_pair(TreeNode_Weight<T> &obj){
			elem.first=obj.weight;
			elem.second=&obj;
		}
		TreeNode_Weight<T> * second() const
		{
			return elem.second;
		}
};

template<class T>
bool operator>(wei_in_pair<T> a,wei_in_pair<T> b)
{
	return a.elem.first>b.elem.first;
}
/*
template<class T>
priority_queue<wei_in_pair<T>, vector<wei_in_pair<T> >, greater<wei_in_pair<T> > >  pq;
*/

template<class T>
TreeNode_Weight<T>* buildHuff(priority_queue<wei_in_pair<T>, vector<wei_in_pair<T> >, greater<wei_in_pair<T> > > pq);

template<class T>
bool TreeNode<T>::AddL(TreeNode<T> &lnew){
	if(this->lchild==NULL)
	{
		this->lchild=&lnew;
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
bool TreeNode<T>::AddR(TreeNode<T> &rnew){
	if(this->rchild==NULL)
	{
		this->rchild=&rnew;
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
TreeNode_Weight<T>* buildHuff(priority_queue<wei_in_pair<T>, vector<wei_in_pair<T>>, greater<wei_in_pair<T>> > pq)
{
	TreeNode_Weight<T> *root,*lchild,*rchild;
	if(pq.empty())
	{
		return NULL;
	}
	if(pq.size()==1)
	{
		root=pq.top().second();
		pq.pop();
		return root;
	}
	
	while(true)
	{
		if(pq.top().second()->lchild)
		{
			rchild=pq.top().second();
			rchild->code+="1";
			pq.pop();
			lchild=pq.top().second();
			lchild->code+="0";
			pq.pop();
		}
		else
		{
		
		lchild=pq.top().second();
		lchild->code+="0";
		pq.pop();
		rchild=pq.top().second();
		rchild->code+="1";
		pq.pop();
		}
		root= *rchild + *lchild;
		root->AddL(*lchild);
		root->AddR(*rchild);
		if(pq.empty()){
			break;
		}
		pq.push(wei_in_pair<T>(*root));
	}
	return root;
}

int main()
{
	priority_queue<wei_in_pair<int>, vector<wei_in_pair<int> >, greater<wei_in_pair<int> >> pq;

	TreeNode_Weight<int> a1(1, 1);
	TreeNode_Weight<int> a2(2, 2);
	TreeNode_Weight<int> a3(4, 3);
	TreeNode_Weight<int> a4(9, 9);



	wei_in_pair<int> a5(a1),a6(a2),a7(a3),a8(a4);
	pq.push(a5);
	pq.push(a6);
	pq.push(a7);
	pq.push(a8);
	TreeNode_Weight<int> *tt = buildHuff(pq);
	preorder(tt); 
	pre(tt);
	return 0;
	return 0;
}
