#include<iostream>
using namespace std;
template<typename TYPE>
class List
{
	int length;
	int maxSize;
	TYPE *data;
	
	public:
		List()
		{
			cout<<"����һ��Ĭ�ϴ�С��˳�����󳤶�ֻ��10Ŷ~"<<endl; 
			length=0;
			maxSize=10;
			data=new TYPE[maxSize];
		}
		List(int max)
		{
			cout<<"��������˺�һ�������Ĺ��캯������󳤶�Ϊ��"<<max<<endl; 
			length=0;
			maxSize=max;
			data=new TYPE[maxSize];
		}
		
		bool full()const
		{
			return length>=maxSize;
		}//�ж����Ա��Ƿ��Ѿ��� 
		void Init(int size)
		{
			maxSize=size;
			delete []data;
			length=0;
		}//��ʼ�� 
		int Length()const
		{
			return length+1;
		}
		bool Empty()const
		{
			return length==0;
		}
		void Clear()
		{
			length=0;
			delete []data;
		}
		void Traverse(void (*visit)(TYPE &))
		{
			for (int curPos=1;curPos<=Length();curPos++)
			{
				(*visit)(data[curPos-1]);
			}
		}
		TYPE GetElem(int pos)
		{
			if(pos<1||pos>Length())
			{
				return -1;
			}
			else
			{
				return data[pos-1];
			}
		}
		TYPE SetElem(int pos,TYPE &e)
		{
			if(pos<1||pos>Length())
			{
				return -1;
			}
			else
			{
				data[pos-1]=e;
				return 0;
			}
		}
		TYPE Delete(int pos,TYPE &e)
		{
			if(pos<1||pos>Length())
			{
				return -1;
			}
			else
			{
				e=data[pos-1];
				TYPE temp;
				for(int i=Length()-1;i>=pos-1;i--)
				{
					if(pos==length&&pos==1)
					{
						data[0]=NULL;
						return 0;
					}
					if(i==(Length()-1))
					{
					temp=data[i-1];
					data[i-1]=data[i];
					data[i]=NULL;
					}
					else
					{
						data[i-1]=data[i];
						data[i]=temp;
					}
				}
				length--;
				return e;
			}
		}
		TYPE Insert(int pos,const TYPE &e)
		{
			if(pos<1||pos>=Length()+1)
			{
				return -1;
			}
			else
			{
				if(length+1>maxSize)
				{
					cout<<"�������б����Χ���޷����"<<endl;
					return -1; 
				}
				else
				{
					for(int i=length-1;i>pos-1;i--)
					{
						data[i]=data[i-1];
					}
					data[pos-1]=e;
				}
				length++;
			}
		}
		
 } ;
int main()
{
	List <int>a;
	a.Insert(1,1);
	int an; 
	cout<<a.GetElem(1)<<endl;
	a.Insert(1,1);
	cout<<a.full()<<endl;
	cout<<a.Length()<<endl;
	//cout<<a.Length()<<endl;
	
	return 0 ;
 } 
