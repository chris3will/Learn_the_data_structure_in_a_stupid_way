#include<iostream>
#include<cstring>
#include<map>
#include<cmath>
#include<stack>
using namespace std;
double answer(char op,double numl,double numr)
{
	switch(op)
	{
		case '+':return numl+numr;break;
		case '-':return numl-numr;break;
		case '*':return numl*numl;break;
		case '/':return numl/numr;break;
		case '^':return pow(numl,numr);break;
		default:break; 
	}
}
int main()
{
	string test;
	cin>>test;
	map<char,int>pri=
	{
		{';',0},{'+',1},{'-',1},{'*',2},{'/',2},{'^',3}
	};
	stack<double>nums;
	stack<char>ops;
	int flag=0;//�����һ���ַ�ǰǰ���ܴ��ڵ������� 
	string tempstr;
	ops.push(';');
	if(test[test.length()-1]!=';')
	{
		test+=';';
	 } 
	 
	for(int i=0;i<test.length();i++)
	{
		if(test[i]==';')
		{
			nums.push(pow(-1,flag)*stod(tempstr));
			flag=1;
			
			while(sop.top()!=';')
			{
				
				}	
		}
		
	}
	return 0;
}
