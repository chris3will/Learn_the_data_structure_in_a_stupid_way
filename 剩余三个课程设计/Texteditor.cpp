/*
Start at 17:16 on 12/13/2018
#按下指定按钮可以操纵文本编辑器切换到相应功能
#R：读取文本文件到缓冲区，缓冲区一千的任何内容将丢失，当前行是文件的第一行
#W: 将缓冲区的内容写入文本文件，当前行或缓冲区均不变
#I：插入单个新行，用户必须在恰当的提示符的响应中键入新行并提供其行号
#D：删除当前行并移到下一行
#F:可以从第1行开始或从当前行开始，查找包含有用户请求的目标串的第一行
#C:将用户请求的字符串修改成用户请求的替换文本，可选择是仅在当前行中有效的还是对全文有效的
#Q：退出编辑器，立即结束
#H：现实解释所有命令的帮助消息，程序也接受?作为H的替代者
#N:当前行移动到下一行，也就是移到缓冲区的下一行
#P:当前行移动到上一行，也就是移到缓冲区的上一行
#B:当前行移到开始处，也就是移到缓冲区的第一行
#E:当前行移到结束处，也就是移到缓冲区的最后一行
#G:当前行移到缓冲区中用户指定的行
#V:查看缓冲区的全部内容，打印到终端
*/
#include"dbl_lk_list.h"
#include"string.h"
#include<cstring>
#include<string.h>
#include<iostream>
#include<ctime>
#include<fstream>

using namespace std;

class LineEditor
{
    private:
        DblLinkList<String> textBuffer;
        int curLineNo;
        DblLinkList<String> textUnDoBuffer;
        int curUnDoLineNo;
        ifstream inFile;
        ofstream outFile;
    //辅助函数
    /*
        StatusCode NextLine();//转到下一行
        StatusCode PreviousLine();//转到前一行
        StatusCode GotoLine();//转到指定行
        StatusCode InsertLine();//插入一行
    */
        void ChangeLine();//替换当前行或所有的指定文本串
        void ReadFile()//读入文本文件,应该是把文件都读入到缓冲区文件中,在这个操作完成后
        {
            if(inFile.is_open())
            {
                String temp;
                int cur = 0;
                while(!inFile.eof())
                {
                    getline(inFile,temp.CStr())
                    //getline(inFile,temp.CStr()); 
                    textBuffer.Insert(cur++, temp);
                }
                inFile.close();
            }
            else
            {
                cout << "操作错误,文件打开失败！";
            }
            
        }
        void WriteFile();//写文本文件
        void FindString();//查找串

    public:
        LineEditor(char infName[],char outfName[])//构造函数，文本来源即，输出文本
        {
            inFile.open(infName,ios::in);
            outFile.open(outfName, ios::out);
        }
        void Run();
};

void LineEditor::ChangeLine()
{//操作结果，用户输入制定文本串，在当前行或所有行中用输入的新文本串替换指定文本串
//替换成功返回SUCCESS,否则FAIL
    char answer;//用户初始回答字符
    bool initialResponse=true;//初始回答

    do{
        //循环直到用户输入恰当的回答为止
        if(initialResponse)
        {
            cout<<"替换当前行 c(urrent) 或替换所有行 a(ll): ";
        }
        else
        {
            cout<<"用c或a回答: ";
        }

        answer=GetChar();//从输入流跳过空格及制表符获取一字符
        while(cin.get()!='\n');//忽略用户输入的其他字符
        answer=tolower(answer);
        initialResponse=false;
    }while(answer!='c'&&answer!='a');

    cout<<"输入要被替换的指定文本串: ";
    String strOld=Read(cin);
    cout<<"输入新文本串: ";
    String strNew=Read(cin);

    for(int row=1;row<=textBuffer.Length();row++)
    {
        if(answer=='c'&&row!=curLineNo)
        {
            //只替换当前行，row不为当前行
            continue;
        }
        String strRow;//行
        textBuffer.GetElem(row,strRow); 
        int index=Index(strRow,strOld);
        if(index!=-1)
        {
            String newLine;//新行
            Copy(newLine,strRow,index);
            Concat(newLine,strNew);//连接新文本串
            const char * oldLine=strRow.CStr();
            Concat(newLine,(String)(oldLine+index+strlen(strOld.CStr())));
            //连接指定文本串吼的串，oldLine+index+strlen(strOld.CStr())用于
            //计算一个临时指针，指向紧跟在被替换字符串后的字符，然后将c风格串转换为String,并连接到newline后面
            textBuffer.SetElem(row,newLine);//设置当前串新行
        }
    }
}

void LineEditor::FindString()
{
    char answer;
    bool initialResponse=true;//初始回答
    do
    {
        if(initialResponse)
        {
            cout << "从第一行开始 f(irst)或从当前行开始 c(urrent): ";
        }
        else
        {
            cout << "用 f 或 c 回答： ";
        }

        answer=GetChar();//从输入流跳过空格及制表符获取一字符
        while(cin.get()!='\n');
        answer=towlower(answer);
        initialResponse=false;
    }while(answer!='f'&&answer!='c');
    if(answer=='f')curLineNo=1;

    int index;
    cout<<"输入被查找文本串。"<<endl;
    String searchString=Read(cin);//输入查找文本串

    String curLine;//当前行

    textBuffer.GetElem(curLineNo,curLine);
    while((index=Index(curLine,searchString))==-1)
    {//查找指定文本串
        if(curLineNo<textBuffer.Length())
        {//查找下一行
            curLineNo++;
            textBuffer.GetElem(curLineNo,curLine);
        }
        else
        {
            //已完成所有行的查找
            break;
        }
    }

    if(index==-1)
    {
        cout<<"查找失败"<<endl;
    }
    else
    {
        //查找成功
        cout<<curLine.CStr()<<endl;
        for(int i=0;i<index;i++)
        {
            cout<<" ";
        }
        for(int j=0;j<(int)strlen(searchString.CStr());j++)
        {
            //在查找串前的位置显行
            cout<<"^";
        }
        cout<<endl;
    }

}
void LineEditor::Run()
{
    char userCommand;//用户命令

    do
    {
        String tempString;//临时串
        String curLine;//当前行

        if(curLineNo!=0)
        {
            //存在当前行
            textBuffer.GetElem(curLineNo,curLine);//取出当前行
            cout<<curLineNo<<" : "//显示行号
                <<curLine.CStr()<<endl<<" ? ";//显示当前行及问号?
        }
        else
        {
            //不存在当前行
            cout<<"文件缓存空"<<endl<<"?";
        }

        userCommand=GetChar();
        userCommand=tolower(userCommand);
        while(cin.get()!='\n');

        if(userCommand!='u'&&userCommand!='h'&&userCommand!='?'&&userCommand!='v')
        {
            //存储撤销信息
            textUnDoBuffer=textBuffer;//用于撤销的缓存
            curUnDoLineNo = curLineNo;//用于撤销的行号
        }

        //运行操作命令
        switch(userCommand)
        {
            case 'b':
            if(textBuffer.Empty())
            {
                //文本缓存空
                cout << "警告：文本缓存空" << endl;
            }
            else
            {
                //文本缓存非空，转到第一行
                curLineNo=1;
            }
            break;
            case 'c':
            //替换当前行或所有行
            if(textBuffer.Empty())
            {
                ChangeLine();
            }
            break;
            case 'd':
            if(textBuffer.Delete(curLineNo,tempString)!=SUCCESS)
            {
                cout << "错误：删除失败" << endl;
            }
            break;
            case 'e':
            //转到最后一行
            if(textBuffer.Empty())
            {
                cout<<"警告:文本缓存为空"<<endl;
            }
            else
            {//转到最后一行
                curLineNo=textBuffer.Length();
            }
            break;
            case 'f':
            //从当前行或第一行开始查找制定文本
            if(textBuffer.Empty())
            {
                cout<<"警告：文本缓存空"<<endl;
            }
            else
            {
                //从当前行开始查找指定文本
                FindString();
            }
            break;
            /*
            case 'g':
            if(GotoLine()!=SUCCESS)
            {
                cout << "警告: 没有那样的行" << endl;
            }
            break;
            */
            case '?':
            case 'h':
            cout<<"有效命令: b(egin),c(change),d(del),e(end)"<<endl;
            cout<<"f(find),g(go),h(help),i(insert),n(next),p(prior)"<<endl;
            cout<<"q(quit),r(read),u(undo),v(view),w(write)"<<endl;
            break;
            case 'i':
            /*
            if(InsertLine()!=SUCCESS)
            {
                cout << "错误: 插入行出错" << endl;
            }
            break;
            case 'n':
            if(NextLine()!=SUCCESS)
            {
                cout<<"警告：当前行已是最后一行"<<endl;
            }
            break;
            case 'p':
            if(PreviousLine()!=SUCCESS)
            {
                cout<<"警告：当前行已是第一行"<<endl;
            }
            break;
            */
            case 'q':
            break;
            case 'r':
            ReadFile();
            break;
            case 'u':
            Swap(textUnDoBuffer,textBuffer);
            Swap(curUnDoLineNo,curLineNo);
            break;
            case 'v':
            textBuffer.Traverse(Write);
            break;
            case 'w':
            if(textBuffer.Empty())
            {
                cout<<"警告:文本缓存空"<<endl;
            }
            else
            {
                WriteFile();
            }
            break;
            default:
            cout<<"输入h或？获得帮助或输入有效命令字符:\n";
        }
    }
    while(userCommand!='q');
}

int main()
{
    ofstream example("example.txt");
    if(example.is_open())
    {
        example<<"asa";
        example.close();
    }
    return 0;
}