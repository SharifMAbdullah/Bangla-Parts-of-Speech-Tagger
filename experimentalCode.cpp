#include <iostream>
#include <ctype.h>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
#define N 1000

string strings[N];
string tokenizedWords[N];
NotStemmed_suffix[N];
Bivokti_suffix[N];
Bochon_suffix[N];
Other_suffix[N];

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

void storeSuffixFromTextFile(int choice)
{
    fstream f;
    string s;
    int i = 0;
    
    if(choice==1)
        {
            f.open("Bochon_suffix.txt");
                while(getline(f,s))
                {
                    Bochon_suffix[i] = s;
                    i++;
                }
        }
    else if(choice == 2)
        {
            f.open("Bivokti_suffix.txt");
            while(getline(f,s))
                {
                    Bivokti_suffix[i] = s;
                    i++;
                }
        }
    else if(choice == 3)
        {
            f.open("Other_suffix.txt");
            while(getline(f,s))
                {
                    Other_suffix[i] = s;
                    i++;
                }
        }
            

f.close();
}

void stopWordRemover()
{
    string temp,t[10000];
    fstream f1,f2;
    f1.open("stop_words.txt");
    f2.open("a.txt");
    long int j = 0;
    int n = lenStringArray(tokenizedWords);
    while(getline(f1,temp))
    {
        t[j] = temp;
        j++;
    }

    for(long int i=0; i<n; i++)
        {
            for(long int k=0; k<j; k++)
            {
                if(tokenizedWords[i] == t[k])
                    {
                        tokenizedWords[i].erase();
                        break;
                    }
                    
                else 
                    {
                        f2 << tokenizedWords[i] << endl;
                        break;
                    }
            }        
        }    
    f1.close();
    f2.close();
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
        string DARI1 = "।";
        string DARI2 = "৷";

        int find = strings[i].find(DARI1);
        cout << i <<" " << find << " "  << " "<<strings[i].size() << endl;
        
        if(find != string::npos) 
            {
                strings[i].replace(find,3,"#");
                f2 << strings[i] << endl;
            }
        else cout << "NOT FOUND first dari" << endl;

        int find1 = strings[i].find(DARI2);
        cout << i <<" " << find1 << " "  << " "<<strings[i].size() << endl;
        
        if(find1 != string::npos) 
            {
                strings[i].replace(find1,3,"#");
                f2 << strings[i] << endl;
            }
        else cout << "NOT FOUND second dari" << endl;

        //looks for punctuations in string, if not punctuation, stores it 
        int id = 0;
        for (int j = 0; j < strings[i].size(); j++)
        {
            if (!ispunct(strings[i][j]) && strings[i][j]!='#')
                updatedStr[id++] = strings[i][j];
        }
        
        for(int j = 0; j < id; j++) 
            tokenizedWords[k].push_back(updatedStr[j]);
            
        k++;
    }
    
f.close();
}

void stemmer()
{
    for(int i=0;i<lenStringArray(tokenizedWords);i++)
    {
        string alpha = NULL;
        int l = length(tokenizedWords[i]);
        int k = 0;
        
        for(int j=l-1; j>=0; j++)
        {
            alpha = tokenizedWords[i][j];
            
            if(!strcmp(alpha,NotStemmed_suffix[k]))
                {
                    k++;
                    break;
                }
            
            else if(!strcmp(alpha,Bivokti_suffix[k]))
            {
                stemmedWords[i] = trim(tokenizedWords[i],alpha);
                k++;
                break;
            }
            
            else if(!strcmp(alpha,Bochon_suffix[k]))
            {
                stemmedWords[i] = trim(tokenizedWords[i],alpha);
                k++;
                break;
            }
            
            else if(!strcmp(alpha,Other_suffix))
            {
                stemmedWords[i] = trim(tokenizedWords[i],alpha);
                k++;
                break;
            }
        }
    }
}

int main()
{
    storeStrings();
    storeSuffixFromTextFile(1);
    storeSuffixFromTextFile(2);
    storeSuffixFromTextFile(3);
    tokeniser();
    stopWordRemover();
}

