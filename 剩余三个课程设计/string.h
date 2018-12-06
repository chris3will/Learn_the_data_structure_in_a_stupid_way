#ifndef __STRING_H__
#define __STRING_H__

#include "lk_list.h"							// 锟斤拷锟斤拷锟斤拷锟斤拷

// 锟斤拷锟斤拷
class String 
{
protected:
//  锟斤拷实锟街碉拷锟斤拷锟捷筹拷员:
	mutable char *strVal;						// 锟斤拷值
	int length;									// 锟斤拷锟斤拷	

public:                           
//  锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟酵凤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟截憋拷锟斤拷系统默锟较凤拷锟斤拷锟斤拷锟斤拷:
	String();									// 锟斤拷锟届函锟斤拷 
	virtual ~String();							// 锟斤拷锟斤拷锟斤拷锟斤拷
	String(const String &copy);					// 锟斤拷锟狡癸拷锟届函锟斤拷
	String(const char *copy);					// 锟斤拷C锟斤拷锟阶拷锟斤拷墓锟斤拷旌拷锟�
	String(LinkList<char> &copy);				// 锟斤拷锟斤拷锟皆憋拷转锟斤拷锟侥癸拷锟届函锟斤拷
	int Length() const;							// 锟襟串筹拷锟斤拷			 
	bool Empty() const;		
						// 锟叫断达拷锟角凤拷为锟斤拷
	String &operator =(const String &copy);		// 锟斤拷锟截革拷值锟斤拷锟斤拷锟�
	const char *CStr() const;					// 锟斤拷锟斤拷转锟斤拷锟斤拷C锟斤拷锟�
	char operator[](int pos) const
	{
		return strVal[pos];
	}	// 锟斤拷锟斤拷锟铰憋拷锟斤拷锟斤拷锟�
};

// 锟斤拷锟斤拷夭锟斤拷锟�
String Read(istream &input);					// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟诫串
String Read(istream &input, char &terminalChar);
	// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟诫串锟斤拷锟斤拷锟斤拷terminalChar锟斤拷锟截达拷锟斤拷锟斤拷锟街凤拷
void Write(const String &s);					// 锟斤拷锟斤拷锟�
void Concat(String &addTo, const String &addOn);
	// 锟斤拷锟斤拷addOn锟斤拷锟接碉拷addTo锟斤拷锟侥猴拷锟斤拷
void Copy(String &copy, const String &original);
	// 锟斤拷锟斤拷original锟斤拷锟狡碉拷锟斤拷copy
void Copy(String &copy, const String &original, int n);
	// 锟斤拷锟斤拷original锟斤拷锟斤拷n锟斤拷锟街凤拷锟斤拷锟斤拷copy 
int Index(const String &target, const String &pattern, int pos = 0);
	// 锟斤拷锟斤拷模式锟斤拷pattern锟斤拷一锟斤拷锟斤拷目锟疥串target锟叫从碉拷pos锟斤拷锟街凤拷锟斤拷始锟斤拷锟街碉拷位锟斤拷
String SubString(const String &s, int pos, int len);	
	// 锟斤拷s锟侥碉拷pos锟斤拷锟街凤拷锟斤拷始锟侥筹拷锟斤拷为len锟斤拷锟接达拷
bool operator ==(const String &first, const String &second);
	// 锟斤拷锟截癸拷系锟斤拷锟斤拷锟�==
bool operator <(const String &first, const String &second);
	// 锟斤拷锟截癸拷系锟斤拷锟斤拷锟�<
bool operator >(const String &first, const String &second);
	// 锟斤拷锟截癸拷系锟斤拷锟斤拷锟�>
bool operator <=(const String &first, const String &second);
	// 锟斤拷锟截癸拷系锟斤拷锟斤拷锟�<=
bool operator >=(const String &first, const String &second);
	// 锟斤拷锟截癸拷系锟斤拷锟斤拷锟�>=
bool operator !=(const String &first, const String &second);
	// 锟斤拷锟截癸拷系锟斤拷锟斤拷锟�!=

// 锟斤拷锟洁及锟斤拷夭锟斤拷锟斤拷锟绞碉拷植锟斤拷锟�
String::String()
//  锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟绞硷拷锟斤拷锟� 
{
	length = 0;									// 锟斤拷锟斤拷锟斤拷为0
	strVal = NULL;								// 锟秸达拷
}

String::~String()
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷俅锟斤拷锟斤拷头糯锟斤拷锟秸硷拷每占锟�
{
	delete []strVal;							// 锟酵放达拷strVal
}

String::String(const String &copy)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷纱锟絚opy锟斤拷锟斤拷锟铰达拷锟斤拷锟斤拷锟斤拷锟狡癸拷锟届函锟斤拷
{
	length = strlen(copy.CStr());				// 锟斤拷锟斤拷
	strVal = new char[length + 1];				// 锟斤拷锟斤拷娲拷占锟�
	strcpy(strVal, copy.CStr());				// 锟斤拷锟狡达拷值
}

String::String(const char *copy)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟紺锟斤拷锟阶拷锟斤拷锟斤拷锟斤拷麓锟斤拷锟斤拷锟阶拷锟斤拷锟斤拷旌拷锟�
{
	length = strlen(copy);						// 锟斤拷锟斤拷
	strVal = new char[length + 1];				// 锟斤拷锟斤拷娲拷占锟� 
	strcpy(strVal, copy);						// 锟斤拷锟狡达拷值
}

String::String(LinkList<char> &copy)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷员锟阶拷锟斤拷锟斤拷锟斤拷麓锟斤拷锟斤拷锟阶拷锟斤拷锟斤拷旌拷锟�
{
	length = copy.Length();						// 锟斤拷锟斤拷
	strVal = new char[length + 1];				// 锟斤拷锟斤拷娲拷占锟� 
	for (int i = 0; i < length; i++) 
	{	// 锟斤拷锟狡达拷值
		copy.GetElem(i + 1, strVal[i]);
	}
	strVal[length] = '\0';						// 锟斤拷值锟斤拷'\0'锟斤拷锟斤拷	
}

int String::Length() const
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷卮锟斤拷锟斤拷锟�			 
{
	return length;
}

bool String::Empty() const
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷为锟秸ｏ拷锟斤拷锟斤拷true锟斤拷锟斤拷锟津返伙拷false
{
	return length == 0;
}

String &String::operator =(const String &copy)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷馗锟街碉拷锟斤拷锟斤拷
{
	if (&copy != this)
	{
		delete []strVal;						// 锟酵凤拷原锟斤拷锟芥储锟秸硷拷
		length = strlen(copy.CStr());			// 锟斤拷锟斤拷
		strVal = new char[length + 1];			// 锟斤拷锟斤拷娲拷占锟� 
		strcpy(strVal, copy.CStr());			// 锟斤拷锟狡达拷值
	}
	return *this;
}

const char *String::CStr() const
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟阶拷锟斤拷锟紺锟斤拷锟�
{
	return (const char *)strVal;				// 锟斤拷值锟斤拷锟斤拷转锟斤拷
}
/*
char String::operator [](int pos) const
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷卤锟斤拷锟斤拷锟斤拷
{
	
}
*/
void Concat(String &addTo, const String &addOn)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟絘ddOn锟斤拷锟接碉拷addTo锟斤拷锟侥猴拷锟斤拷
{
	const char *cFirst = addTo.CStr();			// 指锟斤拷锟揭伙拷锟斤拷锟�
	const char *cSecond = addOn.CStr();			// 指锟斤拷诙锟斤拷锟斤拷锟�
	char *copy = new char[strlen(cFirst) + strlen(cSecond) + 1];// 锟斤拷锟斤拷娲拷占锟�
	strcpy(copy, cFirst);						// 锟斤拷锟狡碉拷一锟斤拷锟斤拷
	strcat(copy, cSecond);						// 锟斤拷锟接第讹拷锟斤拷锟斤拷
	addTo = copy;								// 锟斤拷锟斤拷值
	delete []copy;								// 锟酵凤拷copy
}

String Read(istream &input)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷氪�
{
	LinkList<char> temp;						// 锟斤拷时锟斤拷锟皆憋拷
	int size = 0;								// 锟斤拷始锟斤拷锟皆憋拷锟斤拷
	char c;										// 锟斤拷时锟街凤拷
	while ((c = input.peek()) != EOF &&			// peek()锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷取一锟斤拷锟街凤拷
												// 锟斤拷锟斤拷锟斤拷指锟诫不锟斤拷
		(c = input.get()) != '\n')				// get()锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷取一锟斤拷锟街凤拷
												// 锟斤拷锟斤拷锟斤拷指锟斤拷指锟斤拷锟斤拷一锟街凤拷
	{	// 锟斤拷锟斤拷锟斤拷锟斤拷址锟阶凤拷锟斤拷锟斤拷员锟斤拷锟�
		temp.Insert(++size, c);
	}
	String answer(temp);						// 锟斤拷锟届串
	return answer;								// 锟斤拷锟截达拷
}

String Read(istream &input,char &terminalChar)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷氪拷锟斤拷锟斤拷锟絫erminalChar锟斤拷锟截达拷锟斤拷锟斤拷锟街凤拷
{
	LinkList<char> temp;						// 锟斤拷时锟斤拷锟皆憋拷
	int size = 0;								// 锟斤拷始锟斤拷锟皆憋拷锟斤拷
	char c;										// 锟斤拷时锟街凤拷
	while ((c = input.peek()) != EOF &&			// peek()锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷取一锟斤拷锟街凤拷
												// 锟斤拷锟斤拷锟斤拷指锟诫不锟斤拷
		(c = input.get()) != '\n')				// get()锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷取一锟斤拷锟街凤拷
												// 锟斤拷锟斤拷锟斤拷指锟斤拷指锟斤拷锟斤拷一锟街凤拷
	{	// 锟斤拷锟斤拷锟斤拷锟斤拷址锟阶凤拷锟斤拷锟斤拷员锟斤拷锟�
		temp.Insert(++size, c);
	}
	terminalChar=c;	// 锟斤拷terminalChar锟斤拷锟截达拷锟斤拷锟斤拷锟街凤拷
	String answer(temp);						// 锟斤拷锟届串
	return answer;								// 锟斤拷锟截达拷
}

void Write(const String &s)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
{
	cout << s.CStr() << endl;					// 锟斤拷锟斤拷锟街�
}

void Copy(String &copy, const String &original)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟給riginal锟斤拷锟狡碉拷锟斤拷copy
{
	const char *cOriginal = original.CStr();// 锟斤拷始锟斤拷
	char *cCopy = new char[strlen(cOriginal) + 1];// 锟斤拷锟斤拷娲拷占锟�
	strcpy(cCopy, cOriginal);					// 锟斤拷锟狡达拷
	copy = cCopy;								// 锟斤拷锟斤拷值
	delete []cCopy;								// 锟酵放达拷cCopy
}

void Copy(String &copy, const String &original, int n)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟給riginal锟斤拷锟斤拷n锟斤拷锟街凤拷锟斤拷锟斤拷copy 
{
	const char *cOriginal = original.CStr();// 锟斤拷始锟斤拷
	int len = (int)strlen(cOriginal) < n ? (int)strlen(cOriginal) : n;//目锟疥串锟斤拷
	char *cCopy = new char[len + 1];			// 锟斤拷锟斤拷娲拷占锟�
	strncpy(cCopy, cOriginal, n);				// 锟斤拷锟狡达拷
	cCopy[len] = '\0';							// 锟斤拷值锟斤拷'\0'锟斤拷锟斤拷
	copy = cCopy;								// 锟斤拷锟斤拷值
	delete []cCopy;								// 锟酵放达拷cCopy
}

int Index(const String &target, const String &pattern, int pos)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷匹锟斤拷晒锟斤拷锟斤拷锟斤拷锟侥Ｊ斤拷锟絧attern锟斤拷一锟斤拷锟斤拷目锟疥串target锟叫从碉拷pos
//	锟斤拷锟街凤拷锟斤拷始锟斤拷锟街碉拷位锟斤拷, 锟斤拷锟津返伙拷-1
{
	const char *cTarget = target.CStr();		// 目锟疥串
	const char *cPattern = pattern.CStr();		// 模式锟斤拷
	const char *ptr=strstr(cTarget + pos, cPattern);	// 模式匹锟斤拷
	if (ptr == NULL)
	{	// 匹锟斤拷失锟斤拷	
		return -1; 
	}
	else
	{	// 匹锟斤拷晒锟�	
		return ptr - cTarget;
	}
}

String SubString(const String &s, int pos, int len)
// 锟斤拷始锟斤拷锟斤拷锟斤拷锟斤拷s锟斤拷锟节ｏ拷0 <= pos < s.Length()锟斤拷0 <= len <= s.Length() - pos
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷卮锟絪锟侥碉拷pos锟斤拷锟街凤拷锟斤拷始锟侥筹拷锟斤拷为len锟斤拷锟接达拷
{
	if  (0 <= pos && pos < s.Length() && 0 <= len)
	{	// 锟斤拷锟截达拷s锟侥碉拷pos锟斤拷锟街凤拷锟斤拷始锟侥筹拷锟斤拷为len锟斤拷锟接达拷
		len = (len < s.Length() - pos) ? len : (s.Length() - pos);// 锟接达拷锟斤拷
		char *sub = new char[len + 1];			// 锟斤拷锟斤拷娲拷占锟�
		const char *str = s.CStr();				// 锟斤拷锟斤拷C锟斤拷锟�
		strncpy(sub, str + pos, len);			// 锟斤拷锟狡达拷
		sub[len] = '\0';						// 锟斤拷值锟斤拷'\0'锟斤拷锟斤拷
		String tem(sub);						// 锟斤拷锟缴达拷锟斤拷锟斤拷
		return tem;
	}
	else
	{	// 锟斤拷锟截空达拷
		String tem("");							// 锟斤拷锟缴空达拷锟斤拷锟斤拷
		return tem;
	}
}

bool operator ==(const String &first, const String &second)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷毓锟较碉拷锟斤拷锟斤拷==
{
	return strcmp(first.CStr(), second.CStr()) == 0;
}

bool operator <(const String &first, const String &second)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷毓锟较碉拷锟斤拷锟斤拷<
{
	return strcmp(first.CStr(), second.CStr()) < 0;
}

bool operator >(const String &first, const String &second)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷毓锟较碉拷锟斤拷锟斤拷>
{
	return strcmp(first.CStr(), second.CStr()) > 0;
}

bool operator <=(const String &first, const String &second)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷毓锟较碉拷锟斤拷锟斤拷<=
{
	return strcmp(first.CStr(), second.CStr()) <= 0;
}

bool operator >=(const String &first, const String &second)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷毓锟较碉拷锟斤拷锟斤拷>=
{
	return strcmp(first.CStr(), second.CStr()) >= 0;
}

bool operator !=(const String &first, const String &second)
// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷毓锟较碉拷锟斤拷锟斤拷!=
{
	return strcmp(first.CStr(), second.CStr()) != 0;
}


#endif