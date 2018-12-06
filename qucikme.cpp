#include<iostream>
using namespace std;

template<class T>
void quicksort(T a[],int l,int r)
{
	if(l<l)
	{
		T temp=a[l];
		int i=l;int j=r;
		while(i<j)
		{
			while((i<j)&&a[j]>=temp)
			j--;
			if(i<j)
			a[i++]=a[j];
			
			while((i<j)&&a[i]<=temp)
			i++;
			if(i<j)
			a[j--]=a[i];
		}
		a[i]=temp;
		quicksort(a,l,i-1);
		quciksort(a,i+1,r);
	}
}
int main()
{
	
	return 0;
}
