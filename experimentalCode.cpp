#include <iostream>
#include <ctype.h>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
#define N 1000

string strings[N];
string tokenizedWords[N];
pair<string,string> wordWithRoot[N];
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
                    //cout << "ok bochon" <<endl;
                    Bochon_suffix[i] = s;
                    i++;
                    //cout << Bochon_suffix[i-1] << endl;
                }
        cout << "length bochon : " << lenStringArray(Bochon_suffix) << endl;
        f.close();
        }
    else if(choice == 2)
        {
            f.open("Bivokti_suffix.txt");
            while(getline(f,s))
                {
                    //cout << "ok bivokti" <<endl;
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
                    //cout << "ok other" <<endl;
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
                    //cout << "ok not stem" <<endl;
                    NotStemmed_suffix[i] = s;
                    i++;
                }
        cout << "length not stemmed : " << lenStringArray(NotStemmed_suffix) << endl;
        f.close();
        }
}

// void stopWordRemover()
// {
//     string temp,t[10000];
//     fstream f1,f2;
//     f1.open("stop_words.txt");
//     f2.open("a.txt");
//     long int j = 0;
//     int n = lenStringArray(tokenizedWords);
//     while(getline(f1,temp))
//     {
//         t[j] = temp;
//         j++;
//     }

//     for(long int i=0; i<n; i++)
//         {
//             for(long int k=0; k<j; k++)
//             {
//                 if(tokenizedWords[i] == t[k])
//                     {
//                         tokenizedWords[i].erase();
//                         break;
//                     }
                    
//                 else 
//                     {
//                         f2 << tokenizedWords[i] << endl;
//                         break;
//                     }
//             }        
//         }    
//     f1.close();
//     f2.close();
// }

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
        int find1 = strings[i].find(DARI2);
        
        if(find != string::npos || find1 != string::npos) 
            {
                if(find!=-1)
                    strings[i].replace(find,3,"#");
                else
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
    
        //for(int i=0;i<lenStringArray(tokenizedWords);i++)
            //cout << tokenizedWords[i] << endl;
f.close();
f2.close();
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
    int k =0;
    fstream f,f2;
    f2.open("test.txt");
    f.open("write.txt");
    for(int i=0;i<size(tokenizedWords);i++)
    {
        string alpha = "";
        int n = tokenizedWords[i].size();
        alpha = tokenizedWords[i];
        
        if(binary_search(NotStemmed_suffix, NotStemmed_suffix+380, alpha))
            {
                cout << " outer loop" << endl;
                f2 << "found NotStemmed_suffix where alpha is " << alpha << endl;
                wordWithRoot[k].first = alpha;
                wordWithRoot[k].second = "";
                f<<wordWithRoot[k].first << " " << wordWithRoot[k].second<<endl; 
                continue;
            }
                
	    for (int len = n-1; len >=0; len--)
		{
	        string beta = "";
			beta +=  alpha.substr(len);
		    f2 << " beta at " << i <<"th word at position " << len << " is "<<beta << " where alpha " <<alpha<<endl; 
       
            if(binary_search(Bochon_suffix, Bochon_suffix+36, beta))
            {
                f2 << "found Bochon_suffix" << endl;
                wordWithRoot[k].first = alpha;
                wordWithRoot[k].second = trimmer(tokenizedWords[i], beta);
                f<<wordWithRoot[k].first << " " << wordWithRoot[k].second<<endl;
                break;
            }
            
            else if(binary_search(Bivokti_suffix, Bivokti_suffix+112, beta))
            {
                f2 << "found Bivokti_suffix" << endl;
                wordWithRoot[k].first = alpha;
                wordWithRoot[k].second = trimmer(tokenizedWords[i], beta);
                f<<wordWithRoot[k].first << " " << wordWithRoot[k].second<<endl;
                break;
            }

            else if(binary_search(Other_suffix, Other_suffix+12, beta))
            {                
                wordWithRoot[k].first = alpha;
                wordWithRoot[k].second = trimmer(tokenizedWords[i], beta);
                f<<wordWithRoot[k].first << " " << wordWithRoot[k].second<<endl;
                break;
            } 
        }
        wordWithRoot[k].first = alpha;
        wordWithRoot[k].second = alpha;
        f<<wordWithRoot[k].first << " " << wordWithRoot[k].second<<endl;
        //break;
    }
f.close();
f2.close();
}

void bangla_POS_tagger(string word, string root)
{
    string tag = getTagFromRule(root);
    if(tag == tagList)
        continue;
    if(isQuantifierMarker(word,quantifierList))
        continue;
    if(word!=root && isQuantifierMarker(word,quantifierList))
        continue;
    if(word == dictionary)
        tag = getTag(word,dictionary);
    else
        {
            if(word!=root)
            {
                if(root == dictionary)
                {
                    tag = getTag(root,dictionary);
                    if(tag == "Adjective")
                        tag = "Noun";
                    else if(getFromVerbDataSet(word,vset) && !isWrongVerbSuffixes(word))
                        tag = "Verb";
                    else
                        tag = "Noun";
                }
                else
                {
                    if(getFromVerbDataSet(word,vset))
                        tag = "Verb";
                    else
                        tag = "Noun";
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
    storeSuffixFromTextFile(4);

    sort(Bochon_suffix, Bochon_suffix+36 );
    sort(Bivokti_suffix, Bivokti_suffix+112 );
    sort(Other_suffix,Other_suffix+12);
    sort(NotStemmed_suffix,NotStemmed_suffix+380);

    tokeniser();
    //stopWordRemover();
    stemmer();
    
}
