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
12/6决定放弃数据结构书本上的例子，利用string和list和基本的文件操作进行活动。

*/
#include<iostream>
#include<fstream>
#include<list>
#include<string>
#include<algorithm>
#include<cstring>

using namespace std;


class TextEdit
{
    private:
    //毕竟这是个文本编辑器，我就不用什么什么模板了，string足以.
        list<string> textBuf;
        int curNo;
        int curPa;//当前段落,但可能后期再考虑这个吧
        list<string> textUnBuf;
        int curUnNo;
        int maxLine;
        ifstream inFile;
        ofstream outFile;
    public:
       
        /*
        void upload()
        {
            T temp;
            while(!inFile.eof())
            {
                getline(inFile, temp);
                textBuf.push_back(temp);
                curNo += 1;
                maxLine += 1;
                //记录当前加载到了第几行
                delete temp;
            }  
        }
        */
       /*
       void WriteFile()
       {//最终文件操作完成,需要把缓冲区的文件进行写回
            if(outFile.is_open())
            {
                cout << "写文件已经打开，可以进行正常写入" << endl;
                list<string>::iterator tt;
                string tempstr;
                while(!outFile.eof())
                {

                }
            }
       }
       */
        TextEdit()
        {
            curPa=maxLine=curNo=curUnNo=0;
            //ReadFile
        }
        ~TextEdit()
        {
            if(inFile.is_open())
            {
                inFile.close();
            }
            if(outFile.is_open())
            {
                outFile.close();
            }
            cout << "$$$You made it!$$$" << endl;
        }
        void ReadFile(const string& filename)
        {
            inFile.open(filename, ios::in);
            string tempstr;
            while(!inFile.eof())
            {
                
                getline(inFile, tempstr);
                textBuf.push_back(tempstr);
                //curNo += 1;
                maxLine += 1;
                //记录当前加载到了第几行
                //delete temp;
            }
            curNo = 1;//当前行是文件的第一行
        }
        void WriteFile(const string& filename)
        {
            if(!outFile.is_open())
            outFile.open(filename, ios::out);
            string tempstr;
            for (list<string>::iterator hh = textBuf.begin(); hh != textBuf.end();hh++)
            {
                outFile << *hh<<'\n';
                //curNo-= 1;   
                //记录当前加载到了第几行
                //delete temp;
            }
            textBuf.clear();
            if(outFile.is_open())
            {
                outFile.close();
            }
        }
        void Display()
        {//每次操作后可以展示对应的结果
            list<string>::iterator ev;
            for (ev = textBuf.begin(); ev != textBuf.end();ev++)
            {
                cout << *ev << endl;
            }
        }
        void tempsave()
        {
            list<string>::iterator tp;
            for (tp = textBuf.begin();tp!=textBuf.end();tp++)
            {
                textUnBuf.push_back(*tp);
            }
            cout << "$$$you have save a copy first successfully!" << endl;
        }
        void ChangeLine()
        {
            Display();
            string theLine;//你想更改的内容
            
            int lineNo;
            cout << "$$$PLease enter the Line Number you want to change.(0 for all and the other number for one)" << endl;
            cin >> lineNo;
            getchar();//just to skip the LineNo you just entered before.
            cout << "$$$Now enter the message you want to modify: " << endl;
            getline(cin, theLine);//this is the special thing.

            //在改变之前，先将缓冲区的数据存到撤销缓冲区中
            tempsave();
            if(textBuf.size()!=0)
            {//读入文件有内容才进行操作
                string curLine("\0");
                int row = 1;//当前执行
                list<string> tempBuf;
                int flag = 0;
                if(lineNo!=0)
                for (list<string>::iterator it = textBuf.begin(); it != textBuf.end();it++)
                {//先找到相关元素
                    
                    {
                        if(row!=lineNo)
                            tempBuf.push_back(*it);
                        else
                        {//找到该行
                            flag = 1;
                            tempBuf.push_back(theLine);
                        }
                    }
                    row++;
                }
                if(flag==0&&lineNo!=0)
                {
                    cout << "$$$Sorry for missing your line Num, enter again please." << endl;
                }
                else
                {//You have found the target, now let's do something with it!
                    if(lineNo!=0)
                        textBuf.swap(tempBuf);
                    else
                    {
                        textBuf.assign(textBuf.size(), theLine);
                    }
                    tempBuf.clear();
                }
            }
            else
            {
                cout << "$$$The file is empty or some errors occured" << endl;
            }
            cout<<"$$$this is what you have done"<<endl;
            Display();
        }

        bool NextLine();//转到下一行
        bool PreviousLine();//转到前一行
        bool GotoLine();//转到指定行
        bool GotoLine(int to);
        bool InsertLine(); //插入一行
        void Run();        //unDone
        void FindString(); //unDone

};
bool TextEdit::NextLine()
{
    if(curNo+1>maxLine)
    {
        cout << "$$$this is the last line, can't move anymore!" << endl;
        return false;
    }
    else
    {
        curNo++;
        cout << "$$$the line number has been added one." << endl;
        return true;
    }
}
bool TextEdit::PreviousLine()
{
    if(curNo==1)
    {
        cout << "you are now at the first line, so you can't move back to the zero one!" << endl;
        return false;
    }
    else
    {
        curNo--;
        cout<<"your current line has been minused one."<<endl;
        return true;
    }
}
bool TextEdit::GotoLine(int to)
{
    if(to>0&&to<=maxLine)
    {
        curNo=to;
        cout<<"we made it for you to the special line!"<<endl;
        return true;
    }
    else
    {
        cout << "the number is out of range!" << endl;
        return false;
    }
}
bool TextEdit::GotoLine()
{
    int to;
    cout << "Please enter the line no to want to arrive." << endl;
    cin>>to;
    if(to>0&&to<=maxLine)
    {
        curNo=to;
        cout<<"we made it for you to the special line!"<<endl;
        return true;
    }
    
    else
    {
        cout << "the number is out of range!" << endl;
        return false;
    }
    
}
bool TextEdit::InsertLine()
{
    //这里要用到读写，从新更改缓冲区，不过还是采用创建一个新的临时缓冲区作为解决方案
    cout << "$$$Now we want to insert a line, but attention, the lines after it will just be shift 1 time." << endl;
    cout<<"$$$Please enter which line do you want to insert the it"<<endl;
    int num;
    cin >> num;
    if(GotoLine(num))
    {//we find that!
        cout << "Please Enter the content you just want to insert!" << endl;
        string toinsert;
        cin >> toinsert;
        list<string> tempBuf;
        list<string>::iterator it = textBuf.begin();
        int row = 1;//the line which we can operator directly
        for (it=textBuf.begin(); it != textBuf.end();it++)
        {
            if(row==num)
            {
                tempBuf.push_back(toinsert);
                toinsert.clear();
            }
            tempBuf.push_back(*it);
            row++;
        }
        textBuf.swap(tempBuf);
        tempBuf.clear();
        Display();
    }
    cout << "$$$this procedure has been done properly!" << endl;
}





int main()
{
    /*
    list<string> ltest;
    list<string>::iterator fl;
    ltest.push_front("123");
    ltest.push_front("456");
    ltest.push_back("789");

    ifstream inFile("file_in.txt",ios::in);
    if(inFile.is_open())
    {
        string tempstr;
        while(!inFile.eof())
        {
            getline(inFile, tempstr);
            ltest.push_back(tempstr);
            tempstr.clear();
        }
        inFile.close();
    }
    else
    {
        cout << "打开失败" << endl;
    }

    for (fl = ltest.begin(); fl != ltest.end();fl++)
    {
        cout << *fl << " ";
    }
    */

    TextEdit little;
    
    little.ReadFile("file_in.txt");
    //little.ChangeLine();
    little.InsertLine();
    little.WriteFile("file_out.txt");
    return 0;
}
