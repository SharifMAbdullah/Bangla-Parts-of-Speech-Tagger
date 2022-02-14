#include<bits/stdc++.h>
using namespace std;

void tokeniser(fstream *f2)
{
	char s;
	do
	{
		s = fscanf("%c",*f2);
		cout << c << "\n";
		
	}while(*f2)
}

int main() 
{
    fstream file1, file2;
	file1.open("read.txt", ios::out);
	if(!file1)
	{
		cout<<"File not found!\n";	
	}
	else
	{
		file1 << "হম দেখা যাক। কি, হয়।";
		file1.close();		
	}
	
	file1.open("read.txt", ios::in);
	file2.open("write.txt", ios::out);
	if(!file2)
	{
		cout<<"File not found!\n";
	}else
	{
		char ch;
		file1 >> noskipws;
		while (file1)
		{
			file1 >> ch;
			file2 << ch;
		}
		
	}
	tokeniser(&file2);
	file2.close();
	file1.close();
	return 0;
	
}