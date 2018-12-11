#include<iostream>
#include<queue>
#include<cstdlib>
#include<algorithm>
#include<unordered_map>
#include<stdio.h>
#include<fstream>
#include<sstream>
/*
    该版本尝试修改字符种类和权重的生成与保存问题，即采用固定的256大小存储
*/
using namespace std;
unsigned long size = 256;
unordered_map<char, string> aftercode;


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
    bool IsLeaf()
    {
        return lchild == NULL && rchild == NULL;
    }
};
TreeNode* createHuff(char data[], int freq[], int size);
struct Compare
{
    bool operator()(TreeNode* l,TreeNode* r)
    {
        if(l->freq>r->freq)
        {
            return 1;
        }
        else if(l->freq==r->freq)
        {
            if(l->data>r->data)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
};
void uncompress();


TreeNode* createHuff(char data[],int freq[],int size)
{
    TreeNode *top, *left, *right;
    priority_queue<TreeNode *, vector<TreeNode *>, Compare> theTree;
    for(int i=0;i<size;i++)
    {
        if(freq[i]!=0)
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
            cout<<node->data<<" : "<<node->co<<endl;
        preShow(node->lchild);
        preShow(node->rchild);
    }
}

void preGetafterCode(TreeNode* node)
{//这里很关键

    if (node!=NULL)
    {
        if (node->data!='$')
            aftercode.insert(make_pair(node->data, node->co));
        preGetafterCode(node->lchild);
        preGetafterCode(node->rchild);
    }
}


unordered_map<char,int> UploadandCount(const string& filename)
{//read the source
    //直接定义一个规模大小为256的字典，key为256个char，value初始化都设置为0
    fstream inFile(filename,ios::in);
    string tempstr;
    unordered_map<char, int> umap;
    for (int i = 0; i < 256;i++)
    {
        umap.insert(make_pair(char(i), 0));
    }
        while (!inFile.eof())
        { //except the '\n',we count the [a-z],[A-Z], and some , . ; ' ' \, like these.
            //cout << "yihang";
            getline(inFile, tempstr);
            //文件跳过了换行符，手动补上
            tempstr += "\n";
            for (int i = 0; i < tempstr.length(); i++)
            {
                if (umap.find(tempstr[i]) == umap.end())
                { //如果没找到
                    umap.insert(make_pair(tempstr[i], 1));
                    //cout << tempstr[i] << endl;
                }
                else
                { //如果找到了
                    umap[tempstr[i]] += 1;
                }
            }
            tempstr.clear();
        }
    
    if(inFile.is_open())
    {
        inFile.close();
    }
    //after upload the only one line file
    return umap;
}
void compress()
{//先存文件总大小,总的字符数，也可以说是他的长度。然后是一个字典序列，这些东西都存储在一行中
//正式的文本或其他内容是从第二行开始的
    unordered_map<char, int> it = UploadandCount("codesource.txt");
    int length=it.size();//
    
    //字符的种类数目
    char p[256];
    for (int i = 0; i < 256;i++)
        p[i] = '$';
    int c[256];
    //p中存了字符的种类，实际种类，但这里用的是动态数组，是否考虑char型的固定256版本？
    //c中存储了各个字符的权重即出现次数。所有字符权重的总和即文本或其他文件的长度
    unsigned long thelength=0;//文件字符总长度
    unordered_map<char, int>::iterator ss;
    int flag = 0;
    for (ss = it.begin(); ss != it.end();ss++)
    {
        //cout << "shit";
        p[flag] = ss->first;
        c[flag] = ss->second;
        thelength += ss->second;
        //cout << p[flag] << "@@@ " << c[flag] << endl;
        if(ss->second!=0) 
		cout << ss->first << " : " << ss->second << endl;
        flag++;
    }

    TreeNode *root = createHuff(p, c, length);
    //把数据输入哈夫曼树中，以便得到哈夫曼编码
    setcodes(root, "");
    //各个带权结点的编码已编码完成
    //preShow(root);
    preShow(root);
   
    preGetafterCode(root);
    cout << "the size is: " << aftercode.size() << endl;
    
    unordered_map<char, string>::iterator pp;
    //利用一个新的哈希表将每个字符对应的哈夫曼编码进行存储
    /*
    for (pp = aftercode.begin(); pp != aftercode.end();pp++)
    {
        //cout << "gg" << endl;
        cout << pp->first << ":" << pp->second << endl;
    }
    */

    //一下内容全是为了服务压缩过程
    ofstream outFile("codetarget.txt", ios::out|ios::binary);
    
    
    if(outFile.is_open())
    {//读压缩文件，读入文件头，获得字符总数，字符种数，以及huffman表信息重建哈夫曼树
        //cout << "asd"<< endl;
        stringstream ss;
        ss << thelength;
        string b(ss.str());
        outFile.write(b.c_str(), sizeof(char));
        ss.str("");

        //把这个文件的规模写进去
        //还应该把这个哈夫曼树导入进文件


        //outFile<<aftercode.size()
        //outFile.write((char*)&aftercode, aftercode.size());
        for (int i = 0; i < 256;i++)
        {
            ss << it[char(i)];
            b=ss.str();
            cout << b << endl;
            outFile.write(b.c_str(), sizeof(char));
            ss.str("");
        }
        //outFile.write("\n", sizeof("\n"));

        //把字典存进文件

        ifstream iFile("codesource.txt", ios::in);
        //先把头文件写进去才行
        string tempstr;
        while(!iFile.eof())
        {
            //按行读取，八位一存八位一存，每行最后不足8位的补0
            //unsigned char inc = 0;
            //int index = 0;//一个字节的八位
            string atemp;
            getline(iFile, tempstr);
            int len = tempstr.size();
            unsigned char buffer = 0;
            int bits = 0;//记录压缩文件的比特数
            //cout << tempstr[2] << endl;
            for (int i = 0; i <len;i++)
            {
                //cout << buffer << endl;
                
                if(aftercode.find(tempstr[i])!=aftercode.end())
                {
                    string code(aftercode[tempstr[i]]);
                    //每个位置对应的哈夫曼
                    for (int j = 0; j < code.size();j++)
                    {//满八位一输出,到达每一行末尾了。包括后加的换行符，如果缓冲区字符没有满八位，则在其后全部补0
                        buffer <<= 1;
                        if(code[j]=='1')
                        {
                            buffer += 1;
                            bits++;
                        }
                        if(bits%8==0)
                        {
                        outFile << buffer;
                        buffer = 0;
                        }
                        if(bits%8!=0&&i==len-1)
                        {
                            while(bits<=8)
                            {
                            buffer <<= 1;
                            bits++;
                            }
                            outFile << buffer;
                            buffer = 0;
                        }
                    }
                    //cout << buffer << endl;
                }
            }
                //outFile << atemp << "\n";
                //outFile << "\n";
            atemp.clear();
            }
            iFile.close();
            
        }
        outFile.close();
    
}

string Decode(const string& target,TreeNode * root)
{//要保证TreeNode 总是根节点， string target是每一行待处理的数据，即二进制串，进行返回，因为每次读取一个字节，即长度为8的string类型数据
    string result = "";
    TreeNode *node;
    node = root;
    for (int pos = 0; pos < target.length();pos++)
    {
        if(target[pos]=='0')
            node = node->lchild;
        else
            node = node->rchild;

        if(node->IsLeaf())
        {
            result += node->data;
            node = root;
        }
    }
    delete node;
    return result;
}





void Uncompress()
{//先读入字符数目，然后读取字节和对应的权重，然后构件哈夫曼树。然后按字节提取文件内容，然后每个字节每个字节的处理
    
    ifstream infp;
    infp.open("targetsource.txt", ios::in|ios::binary);
    //读入文件
    
    
    ofstream outfp;
   
    outfp.open("targettest.txt", ios::out);

    //infp.seekg(0, ios::beg);
    //将文件指针回复到文件最开始的样子

    const unsigned long n = 256;
    char ch[n];
    int w[n];//权
    unsigned long size = 0;
    char *cha=nullptr;
    unsigned long len = 0;
    char thelong;
    infp.read(&thelong,sizeof(thelong));
    //cout<<thelong<<endl;
    size = int(thelong);//把除了规模和字典之外的文件规模进行记录
    cout<<size<<endl;
    //
    cout<<"begin!"<<endl;
    //getline(infp, basicmsg);
    for(int i=0;i<n;i++)
    {
        ch[i]=char(i);
        //问题在于我怎样知道每一个字符后面的权重是几位的? 无论是字符形式还是char形式，我现在都不知道读取几位
        char *temp=nullptr;
        infp.read(temp, sizeof(char));
        cout<<*temp<<endl;
        w[i] = int(*temp);//假设256个字符，每一个都是一个char，每一个数据的权重都已经化成了八位2进制数，这样读取出来的都OK
    }

    //TreeNode *root = createHuff(p, c, length);

    TreeNode *root = createHuff(ch, w, 256);
    infp.read(cha, sizeof(char));
    //infp >> cha;
    while(!infp.eof())
    {
        
        string tempstr = "";
        unsigned char c=(unsigned char)*cha;
        for(int i=0;i<8;i++)
        {
            if(c<128)tempstr+="0";
            else
                tempstr += "1";
            c=c<<1;
        }

        string tempres = Decode(tempstr, root);

        for (int i = 0; i < tempres.length();i++)
        {
            len++;
            outfp << tempres[i];

            if(len==size)
                break;
        }
        if(len==size)break;//解压完毕退出循环
        infp.read(cha, sizeof(char));
        //infp>>cha;
    }
    outfp.close();
    infp.close();
    cout << "complete this period" << endl;
}





int main()
{
    //主函数实现的即是一个压缩的过程
    /*
    char data[]={'a','b','c','d','e','f'};
    int freq[] = { 3, 52, 23, 24, 15, 77};
    
    int size = sizeof(data) / sizeof(data[0]);
    TreeNode *flag = createHuff(data, freq, size);
    setcodes(flag, "");
    
    preShow(flag);
    
    cout << Decode("11100100", flag);
    */
    compress();

    return 0;
}
    //preShow(root);
     

