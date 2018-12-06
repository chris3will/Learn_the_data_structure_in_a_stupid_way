#include<stdio.h>
#include<stdlib.h>
void strcat(char *a,char *b)
{
	while(*a!='\0')
	{
		a++;
	}
	while(*b!='\0')
	{
		*a=*b;
		a++,b++;
	}
	*a='\0';
 } 
 
 int main()
 {
 	char *a="23";
 	return 0;
 }
