#include<iostream> 
#include<map>
using namespace std;
int main()
{
	pair<int,string> a;

	map<int ,string> maptest;
	maptest.insert(pair<int,string>(102,"active"));
	maptest.insert(map<int,string>::value_type(321,"hai"));
	map<int, string>::iterator m_lter; 
	for(m_lter=maptest.begin();m_lter!=maptest.end();m_lter++)
	{
		cout<<m_lter->second<<endl;
	}
	
	return 0;
}
