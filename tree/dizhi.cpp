#include<iostream>
using namespace std;
int  add(int *p)
	{
		cout<<"haha"<<endl;
		return *p+3;
	}
int main()
{
	int n=4;
	int *t=&n; 
	cout<<t<<endl;
	cout<<add(&n)<<endl;
	int a=6;
	int *p=&a;
	cout<<p<<endl;
	cout<<*p<<endl;
	//cout<<*p<<endl;
	cout<<&p<<endl;
	cout<<&*p<<endl;
	return 0;
 } 
