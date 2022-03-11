#include <iostream>
#include <ctype.h>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
#define N 1000

string strings[N];
string tokenizedWords[N];

void storeStrings()
{
    fstream f;
    string s;
    int i = 0;
    
    f.open("read.txt");
    while(getline(f,s,' '))
    {
        strings[i] = s;
        i++;
    }
f.close();
}

int lenStringArray(string str[])
{
    size_t i = 0;
    while (!str[i].empty())
        ++i;

return i;
}

void tokeniser() 
{

    char ch;
    string tp;
    fstream f,f2;
    f.open("a.txt");
    f2.open("write.txt");
    int k = 0;

    for (int i = 0; i < lenStringArray(strings); i++)
    {
        char* updatedStr = new char[N];
        string subs = "।";
        string DARI1 = "।";

        int find = strings[i].find(DARI1);
        cout << i <<" " << find << " "  << " "<<strings[i].size() << endl;
        
        if(find != string::npos) 
            {
                strings[i].replace(find,3,"#");
                f2 << strings[i] << endl;
            }
        else cout << "NOT FOUND first dari" << endl;

        //looks for punctuations in string, if not punctuation, stores it 
        int id = 0;
        for (int j = 0; j < strings[i].size(); j++)
        {
            if (!ispunct(strings[i][j]) && strings[i][j]!='#')
                updatedStr[id++] = strings[i][j];
        }
        
        for(int j = 0; j < id; j++) 
            tokenizedWords[k].push_back(updatedStr[j]);
            
        f << "tokenized words: "  << tokenizedWords[k] << endl;
        k++;
    }
    
f.close();
}

int main()
{
    storeStrings();
    tokeniser();
}