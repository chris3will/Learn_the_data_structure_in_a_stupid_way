#include<stdio.h>
#include<stdlib.h>
void strCat(char *a,char *b)
{
	int i=0;int j=0;
	while(*(a+i)!='\0')
	{
		printf("%c",*(a+i));
		i++;
	}
	
	while(*b!='\0')
	{
		printf(*(a+i));
		*(a+(i))=*(b+j);
		i++;j++;
	}
	printf("lucky"); 
	*(a+i)='\0';
 } 
 
 int main()
 {
 	char *a;
 	char *b;
 	a=(char*)malloc(30*sizeof(char));
 	b=(char*)malloc(30*sizeof(char));
 	scanf("%s%s",a,b);
	strCat(a,b);
	printf("%s\n",a);  
	
 	return 0;
 }
