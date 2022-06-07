#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "BPlusTree.h"
#include "stringOperations.h"
using namespace std;
#define N 1000
#define M 70000

string strings[N];
string tokenizedWords[N];

pair <string, pair<string,string>> wordWithRootAndSuffix[N];
string NotStemmed_suffix[N];
string Bivokti_suffix[N];
string Bochon_suffix[] = {"ইতেছি","ও","টাই","টার","তে","তেই","দের","বার","লেম","ের","েরই","য়ে"};
string Other_suffix[N];

string adverbSuffix[2] = {"ভাবে","ভাবেই"};
string nounSuffix[11] = {"শীল","োয়ান","োয়ালা","খানা","গিরি","দানি","নবিশ","বন্দি","বাজি","ানো","ায়ন"};
string adjectiveSuffix[5] = {"জনক","মূলক","ব্যাপী","যোগ্য","কেন্দ্রিক"};
string quantifierList[N];
string Verb[M];
string dictionary[M];

string tags[N];

void storeNonVerbsInBPlusTree()
{
    string banglaWord,tag;
    ifstream ifile;
    ifile.open("NonVerbDataset.csv");
    if(!ifile) 
        {
            cout<< "File not found!" << endl;
            return;
        }
    while(getline(ifile,tag))
    {
        banglaWord = tag.substr(banglaWord.find(",")+1);
    	tag = tag.substr(0,tag.find(","));
    	insertLeaf(tag,banglaWord);
    }
    cout<< "storing er sheshe" <<endl;
    ifile.close();
}

void storeVerbsInBPlusTree()
{
    string banglaWord,tag;
    ifstream ifile;
    ifile.open("VerbDataset.csv");
    if(!ifile) 
        {
            cout<< "File not found!" << endl;
            return;
        }
    while(getline(ifile,tag))
    {
        banglaWord = tag.substr(banglaWord.find(",")+1);
    	tag = tag.substr(0,tag.find(","));
        cout << tag << " " << banglaWord << endl;
    	insertLeaf(tag,banglaWord);
    }

    ifile.close();
}

void storeStrings()
{
    fstream f;
    istringstream iss;
    string s;
    int i = 0;
    
    f.open("read.txt");
    string word,line;
    while(getline(f,line,' '))
        {
            if(f.good())
            {
                iss.clear();
                iss.str(line);
                while(iss.good())
                {
                    iss >> word;
                    strings[i] = word;
                    i++;
                }
            }
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
            f.open("Quantifiers.txt");
            while(getline(f,s))
                {
                    //cout << "ok other" <<endl;
                    quantifierList[i] = s;
                    i++;
                }
        cout << "length quantifiers : " << lenStringArray(quantifierList) << endl;
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
    fstream f,f2;
    f2.open("write.txt");
    int k = 0;

    int n = lenStringArray(strings);
    for (int i = 0; i < lenStringArray(strings); i++)
    {
        char* updatedStr = new char[N];
        string DARI1 = "।";
        string DARI2 = "৷";

        int find = stringFind(strings[i],DARI1);
        int find1 = stringFind(strings[i],DARI2);
        
        if(find != -1 || find1 != -1) 
            {
                if(find!=-1)
                    strings[i] = stringReplace(strings[i],DARI1,"#");
                else
                    strings[i] = stringReplace(strings[i],DARI2,"#");
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
    
f2.close();
}

void storeIntoWordsWithRoots(string alpha, string beta, bool *is_true, int index)
{
    *is_true = true;
    wordWithRootAndSuffix[index].first = alpha;
    wordWithRootAndSuffix[index].second.first = trimmer(alpha, beta);
    wordWithRootAndSuffix[index].second.second = beta;
}

void storeIntoWordsWithRoots(string alpha, string beta, int index)
{
    wordWithRootAndSuffix[index].first = alpha;
    wordWithRootAndSuffix[index].second.first = beta;
    wordWithRootAndSuffix[index].second.second = "";
}

void stemmer()
{
    int k =0;
    fstream f;
    f.open("test.txt");
    int n = lenStringArray(strings);
    for(int i=0;i<n;i++) 
    {
        string alpha = "";
        int n = tokenizedWords[i].size();
        alpha = tokenizedWords[i];
        
        bool is_bochon = false, is_bivokti = false, is_other = false;
        bool is_noun = false, is_adj = false, is_adv = false;

        if(binary_search(NotStemmed_suffix, NotStemmed_suffix+380, alpha)) 
            {
                f << "found NotStemmed_suffix where alpha is " << alpha << endl;
                storeIntoWordsWithRoots(alpha,alpha,k);
                f<<wordWithRootAndSuffix[k].first << " = " << wordWithRootAndSuffix[k].second.first <<" + " << wordWithRootAndSuffix[k].second.second<<endl;
                continue;
            }
                
	    for (int len = n-1; len >=0; len--)
		{
	        string beta = "";
			beta +=  alpha.substr(len);
            f << " beta at " << i <<"th word at position " << len << " is "<<beta << " where alpha " <<alpha<<endl;
            if(binary_search(nounSuffix, nounSuffix+36, beta)) 
            {
                f << "found noun suffix" << endl;
                storeIntoWordsWithRoots(alpha, beta, &is_noun, k);
                f<<wordWithRootAndSuffix[k].first << " = " << wordWithRootAndSuffix[k].second.first <<" + " << wordWithRootAndSuffix[k].second.second<<endl; 
                break;
            }

            else if(binary_search(adverbSuffix, adverbSuffix+2, beta)) 
            {
                f << "found adverb suffix" << endl;
                storeIntoWordsWithRoots(alpha, beta, &is_adv, k);
                f<<wordWithRootAndSuffix[k].first << " = " << wordWithRootAndSuffix[k].second.first <<" + " << wordWithRootAndSuffix[k].second.second<<endl; 
                break;
            }

            else if(binary_search(adjectiveSuffix ,adjectiveSuffix+36, beta)) 
            {
                f << "found adjective suffix" << endl;
                storeIntoWordsWithRoots(alpha, beta, &is_adj, k);
                f<<wordWithRootAndSuffix[k].first << " = " << wordWithRootAndSuffix[k].second.first <<" + " << wordWithRootAndSuffix[k].second.second<<endl; 
                break;
            }

            else if(binary_search(Bochon_suffix, Bochon_suffix+36, beta)) 
            {
                f << "found bochon suffix" << endl;
                storeIntoWordsWithRoots(alpha, beta, &is_bochon, k);
                f<<wordWithRootAndSuffix[k].first << " = " << wordWithRootAndSuffix[k].second.first <<" + " << wordWithRootAndSuffix[k].second.second<<endl; 
                break;
            }
            
            else if(binary_search(Bivokti_suffix, Bivokti_suffix+112, beta)) 
            {
                f << "found bivokti suffix" << endl;
                storeIntoWordsWithRoots(alpha, beta, &is_bivokti, k);
                f<<wordWithRootAndSuffix[k].first << " = " << wordWithRootAndSuffix[k].second.first <<" + " << wordWithRootAndSuffix[k].second.second<<endl; 
                break;
            }

            else if(binary_search(Other_suffix, Other_suffix+13, beta)) 
            {   
                f << "found other suffix" << endl;
                storeIntoWordsWithRoots(alpha, beta, &is_other, k);
                f<<wordWithRootAndSuffix[k].first << " = " << wordWithRootAndSuffix[k].second.first <<" + " << wordWithRootAndSuffix[k].second.second<<endl; 
                break;
            } 
        }
        
        if(is_other || is_bivokti || is_bochon || is_adj || is_adv || is_noun)
            {
                k++;
                continue;
            }
            
        storeIntoWordsWithRoots(alpha, alpha, k);
        k++;
    }
}

string getTagFromRule(string suffix)
{
    for(int i=0;i<2;i++)
        {
            if(adverbSuffix[i] == suffix)
                return "adverb";
        }
        
    for(int i=0;i<11;i++)
        {
            if(nounSuffix[i] == suffix)
                return "noun";
        }
        
    for(int i=0;i<5;i++)
        {
            if(adjectiveSuffix[i] == suffix)
                return "adjective";
        }
return "unknown";
}

bool isQuantifierMarker(string word, string *temp)
{
    if(binary_search(quantifierList, quantifierList+36, word)) 
        {
            *temp = "noun";
            return true;
        }
        
    else return false;
}

void bangla_POS_tagger(int index, string word, string root, string suffix)
{
    tags[index] = getTagFromRule(suffix); //detects noun,adj,adv
    if(tags[index] != "unknown")
        {
            cout << tags[index] << endl;
            return;
        }
            

    string temp;
    if(isQuantifierMarker(word, &temp)) //detects quantifiers as nouns
        tags[index] = temp; 

    if(tags[index] == "noun") //checks if a word is noun then whether it's predecessors are adjective or not
        {
            tags[index-1] = "adjective";
            if(index>1)
                {
                    if(tags[index-2] == "adjective")
                    tags[index-1] = "noun";
                }
            cout << tags[index] << endl;
            return;
        }

    temp = "";
    if(word!=root && isQuantifierMarker(root,&temp))  //if a word is not found in quantifier list, checks if it's root word exists in the list
        {
            tags[index] = temp;
            cout << tags[index] << endl;
            return;
        }
    temp = searchInTree(word);
    if(temp != "unknown")
        {
            tags[index] = temp;
            cout << tags[index] << endl;
        }
    else
        {
            temp = "";
            if(word!=root)
            {
                temp = searchInTree(root);
                if(temp != "unknown")
                {
                    tags[index] = temp;
                    if(tags[index] == "adjective")
                        tags[index] = "noun";

                    else if( temp == "verb")
                        tags[index] = temp;
                    else
                        tags[index] = "noun";
                    cout << tags[index] << endl;
                }
                else
                {
                    temp = searchInTree(root);
                    if(temp != "unknown")
                        tags[index] = "verb";
                    else
                        tags[index] = "noun";
                }
            }
        }
}

void reCheck()
{
    fstream f;
    f.open("test.txt");
    int n = lenStringArray(tags);
    // for(int i=0;i< n - 1;i++)
    //     {
    //         if(wordWithRootAndSuffix[i].first==wordWithRootAndSuffix[i+1].first)
    //         {
    //             tags[i] = "adjective";
    //             tags[i+1] = "adjective";
    //         }
    //     }
    for(int i=0;i<n;i++)
    {
        if(tokenizedWords[i]=="সে" || !(tokenizedWords[i].rfind("এমনি",0)) ||!(tokenizedWords[i].rfind("এই",0)) 
            || !(tokenizedWords[i].rfind("সেট",0)) || !(tokenizedWords[i].rfind("এত",0)))
            tags[i] = "pronoun";
        if(tokenizedWords[i]=="কিন্তু" || tokenizedWords[i] == "এবং" || tokenizedWords[i] == "তবে")
            tags[i] = "conjunction";
        if( !(tokenizedWords[i].rfind("যাওয়া",0)) || !(tokenizedWords[i].rfind("বল",0)) || tokenizedWords[i]=="যায়" )
            tags[i] = "verb";        
    }
    for(int i=0;i<n;i++)
    {
        if(tags[i]== "unknown")
            tags[i] = "noun";
    }

}

int main()
{
    storeStrings();
    storeSuffixFromTextFile(1);
    storeSuffixFromTextFile(2);
    storeSuffixFromTextFile(3);
    storeSuffixFromTextFile(4);
    //storeNonVerbsInBPlusTree();
    //storeVerbsInBPlusTree();

    sort(Bochon_suffix, Bochon_suffix+36 );         
    sort(Bivokti_suffix, Bivokti_suffix+112 );      
    sort(quantifierList, quantifierList+34);        
    sort(NotStemmed_suffix,NotStemmed_suffix+380);  
    sort(nounSuffix, nounSuffix+11);                
    sort(adverbSuffix, adverbSuffix+2);             
    sort(adjectiveSuffix, adjectiveSuffix+5);       
    
    tokeniser();
    //stopWordRemover();
    stemmer();
    int n = lenStringArray(strings);
    cout << n;
    for(int i=0;i<n;i++)
        bangla_POS_tagger(i,wordWithRootAndSuffix[i].first, wordWithRootAndSuffix[i].second.first, 
                        wordWithRootAndSuffix[i].second.second);
    reCheck();

    fstream f;
    f.open("write.txt");
    for(int i=0;i<n;i++)
        f << tokenizedWords[i] + "_" + tags[i] << endl;
    f.close();
}