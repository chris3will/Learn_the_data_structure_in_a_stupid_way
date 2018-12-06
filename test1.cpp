#include<iostream>
#include<cstring>
#include<cmath>
#include<stack>
double solve(char op,double num1,double num2)
{
	if(op=='+')
	{
		return num1+num2;
	 } 
	else if(op=='-')
	{
		return num1-num2;
	}
	else if(op=='*')
	{
		return num1*num2;
	}
	else if(op=='/')
	{
		return num1/num2;
	}
	else if(op=='^')
	{
		return pow(num1,num2);
	 } 
}
int pri(char op)
{
	switch(op)
	{
		case ';':return 0;break;
		case '+':
		case '-':return 1;break;
		case '*':
		case '/':return 2;break;
		case '^':return 3;break;
		default:break; 
	}
}
int ischar(char op)
{
	switch(op)
	{
		case'+':
		case'-':
		case'*':
		case'/':
		case'^':
		case'(':
		case')':return 1;break;
		default:return 0;
	}
 } 
using namespace std;
int main()
{
	string test;
	cin>>test;
	//cout<<test.size();
	stack<char> sop;
	//存储运算符的堆栈 
	//cout<<sop.top();
	stack<double> nums;
	//存储操作数的堆栈；
	if(test[test.size()-1]!=';')
	{
		test+=';';
	 } //增加休止符，为了能和操作符栈中的数对应， 
	 cout<<test<<endl;
	string tempstr;
	sop.push(';');
	int flag=0;
	for(int i=0;i<test.size();i++)
	{
	//	cout<<"第"<<i+1<<"次遍历数组"<<endl;
	//	cout<<test[i]<<endl;

		if(test[i]==';')
		{//已经到达结尾了 
			cout<<"成功到达结尾"<<endl; 
			if(tempstr.size()!=0)
			{
				
				nums.push(pow(-1,flag)*stod(tempstr));
				tempstr.clear();
			}
			while(sop.top()!=';')
			{
			char op=sop.top();
			sop.pop();
			double numr=nums.top();
			//cout<<nums.top()<<" this is d test "<<endl;
			nums.pop();
			
			double numl=nums.top();
			//cout<<nums.top()<<" this is e test"<<endl;
			nums.pop();
			//cout<<solve(op,numl,numr)<<endl;
			nums.push(solve(op,numl,numr));
			}
			//cout<<nums.top()<<" this is c test!"<<endl;
		}
		else
		{//从左到右扫描开始 
			//cout<<"成功继续扫描"<<endl;
		//	cout<<ischar(test[i])<<endl;
			if(ischar(test[i])==1)
			{
				if(test[i]=='-'&&(i==0||(i>=1&&test[i-1]=='(')))
				{
					flag=1;
					nums.push(0);
					continue;
				}
				if(test[i]=='+'&&(i==0||(i>=1&&test[i-1]=='(')))
				{
					flag=0;
					nums.push(0);
					continue;
				}
				
				if(tempstr.size()!=0)
				{ 
					nums.push(pow(-1,flag)*stod(tempstr));
					flag=0;
				//	cout<<nums.top()<<" this is also a test"<<endl;
					tempstr.clear();
				}
				
				if(test[i]=='(')
				{
					sop.push(test[i]);
					continue;
				}
				if(test[i]==')')
				{
					while(sop.top()!='(')
					{
						char op=sop.top();
						sop.pop();
						double numr=nums.top();
						nums.pop();
						double numl=nums.top();
						nums.pop();
						nums.push(solve(op,numl,numr));
						cout<<nums.top()<<" this is a test!"<<endl;
					}
					sop.pop();
				}
				else
				{//剩下的就是各种运算符了，再相互比较优先级 
					if(pri(test[i])>pri(sop.top()))
					{
						sop.push(test[i]);
					}
					else
					{
						char op=sop.top();
						sop.pop();
						double numr=nums.top();
						nums.pop();
						double numl=nums.top();
						nums.pop();
						sop.push(test[i]);
						nums.push(solve(op,numl,numr));
						//cout<<nums.top()<<" this is b test!"<<endl;
					}
				}
			}
			else
			{
				tempstr+=test[i];
			//	cout<<"数字长度增加！"<<endl;
			//	cout<<tempstr<<endl;
			}	
		}
	}	
	cout<<nums.top()<<endl; 
	return 0;
 } 
