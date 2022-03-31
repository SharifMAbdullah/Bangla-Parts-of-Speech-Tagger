#include <iostream>
#include <fstream>
#include<vector>
#include <cstring> 
#define max 300

using namespace std;

string strings[max];
string wordWithRoot[max];
//int counter = 0;

bool isPunctuation(char c)
{
     if(c == ' ')
         return 1; 
     else if (c ==  '?')
         return 1; 
     else if (c == '#')
         return 1; 
     else if (c == ',')
         return 1;
     else if (c == '-')
         return 1;        

return 0;
}

int lenStringArray(string str[])
{
    size_t i = 0;
    while (!str[i].empty())
        ++i;

return i;
}

int len(string str)  
{  
    int length = 0;  
    for (int i = 0; str[i] != '\0'; i++)  
    {  
        length++;  
        // cout<<str[i]<<endl;
        // cout<<(int)str[i]<<endl;  
    }  
    return length;     
}

int split (string str, char seperator)  
{  
    int  currentIndex=0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= len(str))  
    {  
        if (str[i] == seperator || i == len(str))  
        {  
            endIndex = i;  
            string subStr = "";  
            subStr.append(str, startIndex, endIndex - startIndex);  
            strings[currentIndex] = subStr;  
            currentIndex += 1;  
            startIndex = endIndex + 1;  
        }  
        i++;  
        
        }
    return currentIndex;     
} 


void tokeniser() //vector<string> s
{
    string str,temp= "";
    fstream f1,f2;
    //FILE *ptr = fopen("read.txt","r");
    f1.open("read.txt", ios::in);
    f2.open("write.txt", ios::out);

    if(!f1 || !f2)
        cout << "File not found!" << endl;
    else
    {
        char ch;
        int i = 0;
		
        string tp;
        while(getline(f1, tp))
        { 
            //read data from file object and put it into string.
            //int currentIndex = 0;

            string str1 = "৷";
            int currentIndex = split(tp, ' ');

            for(int i=0; i<=currentIndex;i++)
            {
                size_t found = strings[i].find(str1);
                if (found != string::npos)
                {
                    cout << "First occurrence is " << found << endl;
        
                    strings[i].replace(found,3,"###");
                    cout<<strings[i]<<endl;
                }

                for(int j=0; j<len(strings[i]); j++)
                {
                    if (isPunctuation(strings[i][j]))
                    {
                        cout<<100<<endl;
                        //strings[i][j] = '\0'; //ALERT!!!
                        //f2<<endl;
                    }

                    else
                    {
                        f2<<strings[i][j];
                        cout<<120<<endl;
                        //counter++;
                    }
                }

            //strings[i].clear();
            f2 << endl;
                
            }
  
        }

      f1.close();
      f2.close();
    }
    
}

void stopWordRemover()
{
    string temp;
    fstream f1,f2;
    f1.open("stop_words.txt",ios::in);
    f2.open("write2.txt",ios::out);
    int n = sizeof(strings)/sizeof(strings[0]);
    while(getline(f1,temp))
    {
        for(long int i=0; i<lenStringArray(strings); i++)
            {
                if(strings[i] == temp)
                strings[i].erase();
                else 
                f2 << strings[i];
            }
    }

    f1.close();
    f2.close();
}

bool compareBochon(string alpha)
{

return 0;
}

bool compareBivokti(string alpha)
{

return 0;
}

void trim(string str, string alpha)
{

}

//EXPERIMENTAL CODE, PROCEED WITH CAUTION
void stemmer()
{
    int n = sizeof(strings)/sizeof(strings[0]);
    for(int i=0;i<n;i++)
    {
        //string alpha = NULL;
        string alpha = "aaa";
        int length = len(strings[i]);

        for(int j = length-1; j>0; j--)
        {
            alpha = strings[i];
            //if(strcmp(α, NotSteamed_suffix)==0) break; -->ALERT<--
            /*if( compareBochon(alpha) )
            {
                wordWithRoot[i] = trim(strings[i],alpha);
                break;
            }

            if( compareBivokti(alpha) )
            {
                wordWithRoot[i] = trim(strings[i],alpha);
                break;
            }

            if( compareBochon(alpha) )
            {
                wordWithRoot[i] = trim(strings[i],alpha);
                break;
            }*/
        }
    }
}

int main()
 {
    //vector<string> s;
    tokeniser(); //s
    stopWordRemover();
	//printf("counter value %d",counter);
}