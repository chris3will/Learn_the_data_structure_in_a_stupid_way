#include<iostream>
using namespace std;
struct tree
{
	int data;
	tree *left,*right;
};

class Btree
{
	static int n;
	static int m;
	public:
		tree *root;
		Btree()
		{
			root=NULL;
		}
		void create_Btree(int);
		void Preorder(tree *);
		void inorder(tree *);
		void Postorder(tree *);
		void display1(){Preorder(root);cout<<endl;
		}
		void display2(){inorder(root);cout<<endl;
		}
		void display3(){Postorder(root);cout<<endl;
		}
		int count(tree *);
		int findleaf(tree *);
		int findnode(tree *);
};
int Btree::n=0;
int Btree::m=0;

void Btree::create_Btree(int x)
{
	tree *newnode=new tree;
	newnode->data=x;
	newnode->right=newnode->left=NULL;
	if(root==NULL)
	{
		root=newnode;
	}
	else
	{
		tree *back;
		tree *current=root;
		while(current!=NULL)
		{
			back=current;
			if(current->data>x)
			{
				current=current->left;
			}	
			else
			{
				current=current->right;
			}
		}
		if(back->data>x)
			{
				back->left=newnode;
			}
		else
			{
				back->right=newnode;
			}
	}
}

int Btree::count(tree *p)
{
	if(p==NULL)
	{
		return 0;
	}
	else
	{
		return count(p->left)+count(p->right)+1;
	}
}

void Btree::Preorder(tree *temp)
{
	if(temp!=NULL)
	{
		cout<<temp->data<<endl;
		Preorder(temp->left);
		Preorder(temp->right);
	}
}

int main()
{
	Btree trr;
	int n=5;
	while(n--)
	{
		trr.create_Btree(n);
	}
	trr.root->left->data=5;
	trr.Preorder(trr.root);
	return 0;
}
