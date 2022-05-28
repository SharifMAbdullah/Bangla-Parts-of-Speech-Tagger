#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H
#include<iostream>
#include<algorithm>

using namespace std;

int len(string str)  
{  
    int length = 0;  
    for (int i = 0; str[i] != '\0'; i++)  
    {  
        length++;  
    }  
    return length;     
}

int lenStringArray(string str[])
{
    size_t i = 0;
    while (!str[i].empty())
        ++i;

return i;
}

//pie table calculation for kmp algorithm
int *pre_kmp(string pattern)
{
	int size = pattern.size();
	int *pie=new int [size];
	pie[0] = 0;
	int k=0;
	for(int i=1;i<size;i++)
	{
		while(k>0 && pattern[k] != pattern[i] )
		{
			k=pie[k-1];
		}
		if( pattern[k] == pattern[i] )
		{
			k=k+1;
		}
		pie[i]=k;
	}
	
	return pie;
}

//uses kmp algorithm for pattern matching
int stringFind(string text,string pattern)
{
	int temp = -1;
	int* pie=pre_kmp(pattern);
	int matched_pos=0;
	for(int current=0; current< text.length(); current++)
	{
		while (matched_pos > 0 && pattern[matched_pos] != text[current] )
			matched_pos = pie[matched_pos-1];
			
		if(pattern[matched_pos] == text[current])
			matched_pos = matched_pos+1;
			
		if( matched_pos == (pattern.length()) )
		{
			temp = current - (pattern.length() -1 );
			matched_pos = pie[matched_pos-1];
		}
	}
return temp;
}


string stringReplace(string mainText, string targetText, string replaceText)
{
    string result = "";
    //int range = targetText.length();
    int start = stringFind(mainText, targetText);
    for(int i=0;i<start;i++)
    result += mainText[i];
    
    int temp = 1 + mainText.length() - result.length() - targetText.length();

    for(int i=0;i<replaceText.length();i++)
    result += replaceText[i];

    for(int i = mainText.length() - temp;i<mainText.length()-1;i++)
    result += mainText[i];

    return result;
}

string stringErase()
{
    string temp;

    return temp;
}

//divides a string in two parts
string trimmer(string og_string, string to_be_split_string)
{
        int find = stringFind(og_string,to_be_split_string);
        string c = "";
		c = og_string.substr(0,find);
		return c;
}

// string stringInsert()
// {
    
// }

#endif