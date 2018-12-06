#include<stack>
#include<iostream>
#include<cmath>
#include<cstring>

using namespace std;

class EV{
	stack<double> nums;
	stack<char> ops;
	string test;
	public:
		EV(string &input)
		{
			test=input;
		}
		int ischar(char op)
		{
			switch(op){
			
				case '+':
				case '-':
				case '*':
				case '/':
				case '^':
				case '(':
				case ')':return 1;break;
				default:break;
			}
		}
		int priroity(char op)
		{
			switch(op){
			
				case ';':
				case '=':return 0;break;
				case '+':
				case '-':return 1;break;
				case '*':
				case '/':return 2;break;
				case '^':return 3;break;
				default:break;
			}
		}
		double tosolve(double numl,double numr,char op)
		{
			
			if(op=='+')
			{
				return numl+numr;
			}
			else if(op=='-')
			{
				return numl-numr;
			 } 
			 else if(op=='*')
			 {
			 	return numl*numr; 
			 }
			 else if(op=='/')
			 {
			 	return numl/numr;
			 }
			 else 
			 {
			 	return pow(numl,numr);
			 }
		}
		void Run();
};
void EV::Run()
{
	int len=test.size();
	if(test[len-1]!='=')
	{
		test+="=";
	} //确保获得一位终止标志
	string strnum;

	double tempnum;
	int flag=0;//用来记录处于第一个数字的正负性
	len=test.size();
	cout<<test;
	ops.push('=');
	for(int i=0;i<len;i++)
	{
		
		if(test[i]=='=')
		{
			
		/*	if(strnum.size()!=0)
			{
				tempnum=stod(strnum);
                if(flag== -1)
                {
                    tempnum=pow(-1,flag)*stod(strnum);
                    flag=0;
                }
                nums.push(tempnum);
                strnum.clear();
			}
		*/	
			while(ops.top()!='=')
			{
				 char op=ops.top();
                ops.pop();
                double numr=nums.top();
                nums.pop();
                double numl=nums.top();
                nums.pop();
                double result=tosolve(numl,numr,op);
                nums.push(result);
			}
		}
		else
		{
			if(ischar(test[i])==1)
			{//判断是否为符号 
				if(test[i]=='+'&&(i==0||(i>=1&&test[i-1]=='(')))
				{
					strnum+='0';
					ops.push('+') ;
					continue;
				}
				if(test[i]=='-'&&(i==0||(i>=1&&test[i-1]=='(')))
				{
					strnum+='0';
					ops.push('-');
					continue;
				}
				if(strnum.size()!=0)
				{//现在碰到了符号，之前字符串有长度，即有数字，我要记录下来 
					double tempnum=stod(strnum);
					nums.push(tempnum);
					strnum.clear();
				}
				if(test[i]=='(')
				{
					ops.push('(');
					continue;
				}
				if(test[i]==')')
				{
					while(ops.top()!='(')
					{
						char op=ops.top();
						
						ops.pop();
						double numr=nums.top();
						nums.pop();
						double numl=nums.top();
						nums.pop();
						double tempres=tosolve(numl,numr,op);
						nums.push(tempres); 
					}
					ops.pop();//把左括号退出来 
				}
				else
				{
					
					if(priroity(test[i])>priroity(ops.top()))
					{
						ops.push(test[i]);
					}
					else
					{
						char op=ops.top();
						ops.pop();
						double numr=nums.top();
						nums.pop();
						double numl=nums.top();
						nums.pop();
						ops.push(test[i]);
						double tempres=tosolve(numl,numr,op);
						nums.push(tempres); 
					}
				}
			 }
			else
			{
				strnum+=test[i];
			}	 
		}
	}
	cout<<nums.top()<<endl;
	
}

int main()
{
	string ab;
	cin>>ab;
	EV a(ab);
	a.Run();
	
	return 0;
}
