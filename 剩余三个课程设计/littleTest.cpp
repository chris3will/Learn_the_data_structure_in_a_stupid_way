#include<iostream>
#include<fstream>
#include<istream>
#include<string>
#include<string.h>

using namespace std;
/*
class sim
{
    private:
      int data;
    public:
        void changed()
        {
            data += 1;
        }
        ~sim(){}
        sim()
        {
            data = 0;
            changed();
            cout << data << endl;
        }
};

int main()
{
    sim s;
    return 0;
}
*/

static char GetChar(istream &inStream = cin)
{
    	char ch;								// 临时变量
	while ((ch = (inStream).peek()) != EOF	// 文件结束符(peek()函数从输入流中接受1
											// 字符,流的当前位置不变)
		&& ((ch = (inStream).get()) == ' '	// 空格(get()函数从输入流中接受1字符,流
											// 的当前位置向后移1个位置)
		|| ch == '\t'));					// 制表符
	
	return ch;	
}


int main()
{   /*
    const char *filename = "file_out.txt";
    //先把文件名给定义好
    long l, m;
    ifstream file(filename, ios::in | ios::binary);

    l = file.tellg();
    file.seekg(0, ios::end);
    m = file.tellg();
    file.close();
    cout << "size of " << filename;
    cout << " is " << (m - 1) << " bytes.\n";
    
    char szTest[1000] = {0};
    int len = 0;

    FILE *fp = fopen("file_in.txt", "r");
    if(fp==NULL)
    {
        printf("error\n");
        return 1;
    }
    else
    {
        while(!feof(fp))
        {
            
            fgets(szTest, sizeof(szTest) - 1, fp);
            printf("%s", szTest);
        }
        fclose(fp);
    }
    ifstream in("file_in.txt", ios::in);
    ofstream out("file_out.txt", ios::out | ios::app);
    if(in.is_open()&&out.is_open())
    {
        string aa;
        while(!in.eof())
        {
            getline(in, aa);
            cout << aa << endl;
        }
        in.close();
        out.close();
    }
    */
   string a("\ta");
   cout << a;
   char c = '3';
   string b;
   cout << a + c;
   cout << (b=="\0");
   b.assign(a);
   cout << b;
   cout << a;

   return 0;
}
