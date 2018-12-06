#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct MinHeapNode{
    //创建哈夫曼树的基础结点

    char data;
    unsigned freq;

    //出现频率和相应的字符

    MinHeapNode *left,*right;

    MinHeapNode(char data,unsigned freq){
        left = right = NULL;
        this->data=data;
        this->freq = freq;
    }
};


//为了得到最小的堆，需要进行比较

struct compare{
    bool operator()(MinHeapNode* l,MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

//输出哈夫曼树然后通过遍历打印哈夫曼树

void printCodes(struct MinHeapNode *root,string str)
{
    if(!root)
    {
        return;
    }
    if (root->data!='$')
    {
        cout << root->data << ": " << str <<'\n';
    }
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}


void HuffmanCodes(char data[],int freq[],int size)
{
    struct MinHeapNode *left, *right, *top;
    //用于中间迭代时重新指向需要的地方
    priority_queue<MinHeapNode*, vector<MinHeapNode *>, compare> minHeap;
    for (int i = 0; i < size;i++)
    {
        minHeap.push(new MinHeapNode(data[i],freq[i]));
    }
    while(minHeap.size()!=1)
    {
        left = minHeap.top();
        minHeap.pop();

        right=minHeap.top();
        minHeap.pop();

        top = new MinHeapNode('$', left->freq + right->freq);
        top->left=left;
        top->right=right;
        minHeap.push(top);
    }

    printCodes(minHeap.top(), "");
}

int main()
{
    char arr[] = {'a','b','c','d','e','f'};
    int freq[]={5,9,12,13,16,45};

    int size=sizeof(arr)/sizeof(arr[0]);

    HuffmanCodes(arr, freq, size);
    return 0;
}
