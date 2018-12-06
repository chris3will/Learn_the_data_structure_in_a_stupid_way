#include<iostream>
#include<cstring>
using namespace std;
void getNext(char *p,int next[])
{
	int pLen=strlen(p);
	int j=0;
	int k=-1;
	next[0]=-1;
	while(j<pLen-1)
	{
		if(k==-1||p[k]==p[j])
		{
			k++;
			j++;
			if(p[k]!=p[j])
			{
				next[j]=k;
			}
			else
			{
				next[j]=next[k];
			}
		}
		else
		{
			k=next[k];
		}
	}
}
int main()
{
	char a[9]={'1','2','3','5','1','2','3','4','9'};
	int pp[9];
	memset(pp,0,sizeof(pp));
	getNext(a,pp);
	for(int i=0;i<strlen(a);i++)
	cout<<pp[i]<<endl;
	return 0;
}
