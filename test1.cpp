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
	//�洢������Ķ�ջ 
	//cout<<sop.top();
	stack<double> nums;
	//�洢�������Ķ�ջ��
	if(test[test.size()-1]!=';')
	{
		test+=';';
	 } //������ֹ����Ϊ���ܺͲ�����ջ�е�����Ӧ�� 
	 cout<<test<<endl;
	string tempstr;
	sop.push(';');
	int flag=0;
	for(int i=0;i<test.size();i++)
	{
	//	cout<<"��"<<i+1<<"�α�������"<<endl;
	//	cout<<test[i]<<endl;

		if(test[i]==';')
		{//�Ѿ������β�� 
			cout<<"�ɹ������β"<<endl; 
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
		{//������ɨ�迪ʼ 
			//cout<<"�ɹ�����ɨ��"<<endl;
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
				{//ʣ�µľ��Ǹ���������ˣ����໥�Ƚ����ȼ� 
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
			//	cout<<"���ֳ������ӣ�"<<endl;
			//	cout<<tempstr<<endl;
			}	
		}
	}	
	cout<<nums.top()<<endl; 
	return 0;
 } 
