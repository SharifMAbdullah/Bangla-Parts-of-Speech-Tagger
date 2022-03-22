#include <iostream>
#include <ctype.h>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
#define N 1000

string strings[N];
string tokenizedWords[N];
string stemmedWords[N];
string NotStemmed_suffix[N];
string Bivokti_suffix[N];
string Bochon_suffix[N];
string Other_suffix[N];

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
        cout << "length bochon : " << lenStringArray(Bochon_suffix) << endl;
        f.close();
        }
    else if(choice == 2)
        {
            f.open("Bivokti_suffix.txt");
            while(getline(f,s))
                {
                    Bivokti_suffix[i] = s;
                    i++;
                }
        cout << "length bivokti : " << lenStringArray(Bivokti_suffix) << endl;
        f.close();
        }
    else if(choice == 3)
        {
            f.open("Other_suffix.txt");
            while(getline(f,s))
                {
                    Other_suffix[i] = s;
                    i++;
                }
        cout << "length other : " << lenStringArray(Other_suffix) << endl;
        f.close();
        }
    else if(choice == 4)
        {
            f.open("NotStemmed_suffix.txt");
            while(getline(f,s))
                {
                    NotStemmed_suffix[i] = s;
                    i++;
                }
        cout << "length not stemmed : " << lenStringArray(NotStemmed_suffix) << endl;
        f.close();
        }
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
        if(find != string::npos) 
            {
                strings[i].replace(find,3,"#");
            }

        int find1 = strings[i].find(DARI2);
        if(find1 != string::npos) 
            {
                strings[i].replace(find1,3,"#");
            }

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

string trimmer(string og_string, string to_be_split_string)
{
        int find = og_string.find(to_be_split_string);
        string c = "";
		c = og_string.substr(0,find);
		return c;
}

void stemmer()
{
    fstream f;
    f.open("write.txt");
    for(int i=0;i<lenStringArray(tokenizedWords);i++)
    {
        string alpha = "";
        int n = len(tokenizedWords[i]);
        alpha = tokenizedWords[i];
        
	    for (int len = n-1; len >=0; len--)
		{
	        string beta = "";
			beta +=  alpha.substr(len);
		
            if(binary_search(NotStemmed_suffix, NotStemmed_suffix+lenStringArray(NotStemmed_suffix), beta))
                continue;
        
            else if(binary_search(Bivokti_suffix, Bivokti_suffix+lenStringArray(Bivokti_suffix), beta))
            {
                stemmedWords[i] = trimmer(tokenizedWords[i], beta);
                f<<stemmedWords[i]<<endl;
                continue;
            }
            
            else if(binary_search(Bochon_suffix, Bochon_suffix+lenStringArray(Bochon_suffix), beta))
            {
                stemmedWords[i] = trimmer(tokenizedWords[i], beta);
                f<<stemmedWords[i]<<endl;
                continue;
            }
            
            else if(binary_search(Other_suffix, Other_suffix+lenStringArray(Other_suffix), beta))
            {
                stemmedWords[i] = trimmer(tokenizedWords[i], beta);
                f<<stemmedWords[i]<<endl;
                continue;
            }
        }
    }
f.close();
}

int main()
{
    storeStrings();
    storeSuffixFromTextFile(1);
    storeSuffixFromTextFile(2);
    storeSuffixFromTextFile(3);
    storeSuffixFromTextFile(4);

    tokeniser();
    stopWordRemover();
    stemmer();
    cout << "length stemmed words : " << lenStringArray(stemmedWords) << endl;

}