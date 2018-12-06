#include<iostream>
#include<queue>
#include<cstdlib>
using namespace std;

struct TreeNode
{
    char data;
    unsigned freq;
    string co;

    TreeNode* lchild;
    TreeNode* rchild;

    TreeNode(char data,unsigned freq)
    {
        lchild=rchild=NULL;
        this->data=data;
        this->freq=freq;
    }
};

struct Compare
{
    bool operator()(TreeNode* l,TreeNode* r)
    {
        return (l->freq>r->freq);
    }
};

//void printCodes(TreeNode *root)

TreeNode* createHuff(char data[],int freq[],int size)
{
    TreeNode *top, *left, *right;
    priority_queue<TreeNode *, vector<TreeNode *>, Compare> theTree;
    for(int i=0;i<size;i++)
    {
        theTree.push(new TreeNode(data[i], freq[i]));
    }

    while(theTree.size()>1)
    {
        left=theTree.top();
        theTree.pop();
        right=theTree.top();
        theTree.pop();

        top = new TreeNode('$', left->freq + right->freq);
        top->lchild=left;
        top->rchild=right;
        theTree.push(top);
    }

    return theTree.top();
}
//setcodes(example,"");
void setcodes(TreeNode *node,const string &str)
{
    if(!node)
    {
        return;
    }
    if(node!=NULL)
    {
        
        node->co=str;
        //cout << node->co << "::" << node->data << endl;
        setcodes(node->lchild, str + "0");
        setcodes(node->rchild, str + "1");
       
    }
}

void preShow(TreeNode* node)
{
    if (node!=NULL)
    {
        if (node->data!='$')
        cout<<node->co<<" : "<<node->data<<endl;
        preShow(node->lchild);
        preShow(node->rchild);
    }
}

int main()
{
    char data[]={'a','b','c','d','e','f'};
    int freq[] = { 3, 52, 23, 24, 15, 77};
    int size = sizeof(data) / sizeof(data[0]);
    TreeNode *flag = createHuff(data, freq, size);
    setcodes(flag, "");
    preShow(flag);
    return 0;
}
