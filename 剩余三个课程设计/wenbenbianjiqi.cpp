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
12/7号最终完成 with c++11 and vscode and clang++
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
        list<string> textUnBuf;//it can just be used once, but may change the typeof value to 'list' or some other STL.
        int curUnNo;
        int maxLine;
        ifstream inFile;
        ofstream outFile;
    public:
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
            cout << "^^^You made it!^^^" << endl;
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
            cout << "$$$Is uploading your text content~~~~~" << endl;
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
            int row = 1;
            cout << "#########################" << endl;
            for (ev = textBuf.begin(); ev != textBuf.end();ev++)
            {
                cout << "(" << row << "): ";
                cout << *ev << endl;
                row++;
            }
            cout<<"#########################"<<endl;
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
            cout << theLine << " : this time the line is ;" << endl;
            //在改变之前，先将缓冲区的数据存到撤销缓冲区中
            //SaveUndo();
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
                            if(theLine=="\n")
                            {
                                it = textBuf.erase(it);
                            }
                            else
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
        bool isEmpty() { return textBuf.size() == 0; }
        bool NextLine();//转到下一行
        bool PreviousLine();//转到前一行
        bool GotoLine();//转到指定行
        bool GotoLine(int to);
        bool InsertLine(); //插入一行
        bool DeleteLine();
        void Run();        //unDone
        void FindString(); //unDone
        void SaveUndo();
        void Undo();
        //void FindAll();
};
void TextEdit::SaveUndo()
{
    int temp;
    temp = curUnNo;
    curUnNo = curNo;
    curNo = curUnNo;
    list<string>::iterator tp;
    textUnBuf.clear();
    for (tp = textBuf.begin();tp!=textBuf.end();tp++)
    {
        textUnBuf.push_back(*tp);
    }
    cout << "$$$you have save a copy in UNDO BUFFER successfully!" << endl;    
}
void TextEdit::Undo()
{
    if(textUnBuf.size()==0)
    {
        cout << "$$$the textUnBuf has nothing" << endl;
    }   
    else
    {
        curNo = curUnNo;
        textBuf.swap(textUnBuf);
        cout << "We have recover the last condition." << endl;
    }  
}
void TextEdit::FindString()
{//maybe somedays I can add some acions for the found.
    if(!isEmpty())
    {//is not empty
        Display();
        cout << "$$$We are in the searching period, do you want to search in the specific line or in all the txt file?" << endl;
        cout << "$$$ !c! for current line and !a! for the whole file." << endl;
        cout << "$$$ Attention, you are at the " << curNo << " line now!" << endl;
        char choice;
        cin >> choice;
        getchar();
        while(choice!='c'&&choice!='a')
        {
            cout << "$$$ AGAIN !c! for current line and !a! for the whole file." << endl;
            cin >> choice;
            getchar();
        }
        int got = 0;
        cout << "$$$Please enter the content you want to match!" << endl;
        string theContent;
        getline(cin, theContent);
        int len = theContent.length();//needed thing.
        cout << "$$$The content happens in ( if it exist ): \n";
        int row = 1;
        list<string>::iterator it;
        for (it = textBuf.begin();it!=textBuf.end();it++)
        {
           
            int flag = 0;
            //int times = 0;
            string tempstr(*it);
            int newlen = tempstr.size();
            while(flag<=(newlen-len))
            { 
                int tp = tempstr.find(theContent);
                if(choice=='c'&&row==curNo)
                {
                    if(tp==flag)
                    {
                        cout << "No. " << row << " line: ";
                        cout << "pos: " << tp << endl;
                        flag = 0;
                        tempstr.erase(tp, len);
                        newlen = tempstr.size();
                        got = 1;
                    }
                }
                if(choice=='a')
                {
                    if(tp==flag)
                    {
                    cout << "No. " << row << " line: ";
                    cout << "pos: " << tp << endl;
                    flag = 0;
                    tempstr.erase(tp, len);
                    newlen = tempstr.size();
                    got = 1;
                    }
                }
                flag++;
            }
            row++;
        }
        if(got==0)
        {
            cout << "$$$Sorry, no match here." << endl;
        }
    }
    else
    {
        cout << "$$$Sorry, the file is empty, nothing can be found." << endl;
    }
}

bool TextEdit::DeleteLine()
{
    if(textBuf.size()!=0)
    {
        cout << "$$Please enter the specific line you want to delete.(0 for all)" << endl;
        int theNo;
        cin >> theNo;
        
        if(theNo==0)
        {
            textBuf.clear();
            cout << "$$$nothing is left ~!" << endl;
        }
        else
        {
            list<string> tempBuf;
            list<string>::iterator it;
            int row = 1;//the line which is being operated.
            for (it = textBuf.begin(); it != textBuf.end();it++)
            {
                if(row==theNo)
                {
                    continue;
                }
                tempBuf.push_back(*it);
                row++;
            }
            cout<<"$$$We have delete it!"<<endl;
            textBuf.swap(tempBuf);
            tempBuf.clear();
        }
    }
    else
    {
        cout << "$$$The file is empty, nothing can be deleted." << endl;
    }
}
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
        cout << "$$$you are now at the first line, so you can't move back to the zero one!" << endl;
        return false;
    }
    else
    {
        curNo--;
        cout<<"$$$your current line has been minused one."<<endl;
        return true;
    }
}
bool TextEdit::GotoLine(int to)
{
    if(to>0&&to<=maxLine)
    {
        curNo=to;
        cout<<"$$$we made it for you to the special line!"<<endl;
        return true;
    }
    else
    {
        cout << "$$$the number is out of range! we can't insert it!" << endl;
        return false;
    }
}
bool TextEdit::GotoLine()
{
    int to;
    cout << "$$$Please enter the line no to want to arrive." << endl;
    cin>>to;
    if(to>0&&to<=maxLine)
    {
        curNo=to;
        cout<<"$$$We made it for you to the special line!"<<endl;
        return true;
    }
    
    else
    {
        cout << "$$$The number is out of range!" << endl;
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
    getchar();
    if(GotoLine(num))
    {//we find that!
        cout << "$$$Please Enter the content you just want to insert!" << endl;
        string toinsert;
        getline(cin, toinsert);
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
        cout << "$$$This procedure has been done properly!" << endl;
        return true;
    }
    
    return false;
}

void TextEdit::Run()
{
    cout << "______________________Welcome to My TextEdit______________________" << endl;
    ReadFile("file_in.txt");//we think it as a prem eidition. and we load it at the beginning of the work.
    Display();

    char command='\0';
    while(command!='q')
    {
        cout << "$$$Please Enter your right command!" << endl;
        cout << "u:Undo\tc:ChangeLine\tf:FindString\td:DeleteLine\ti:InsertLine" << endl;
        cout << "g:GotoLine\ts:Display\tp:PreviousLine\tn:NextLine\tq:quit" << endl;
        cin >> command;
        getchar();
        cout << endl;
        switch(command)
        {
            case 'u':
                Undo();
                break;
            case 'c':
                SaveUndo();
                ChangeLine();
                break;
            case 'f':
                SaveUndo();
                FindString();
                break;
            case 'd':
                SaveUndo();
                DeleteLine();
                break;
            case 'i':
                SaveUndo();
                InsertLine();
                break;
            case 'g':
                SaveUndo();
                GotoLine();
                break;
            case 's'://show
                //SaveUndo();
                Display();
                break;
            case 'p':
                SaveUndo();
                PreviousLine();
                break;
            case 'n':
                SaveUndo();
                NextLine();
                break;
            default:
                break;
        }
    }
    WriteFile("file_out.txt");//at the end, we save the answer in the out file.

}






int main()
{
    TextEdit little;
    little.Run();
    return 0;
}
