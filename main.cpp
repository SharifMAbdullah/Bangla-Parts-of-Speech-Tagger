#include <bits/stdc++.h>
#include <codecvt>
#include <locale>
#include <fcntl.h>
using namespace std;

bool isPunctuation(char16_t c)
{
    if(c == u' ')
        return 1; 
    else if (c ==  u'।')
        return 1; 
    else if (c == u'।')
        return 1; 
    else if (c ==  u'\r')
        return 1;
    else if (c ==  u'\n')
        return 1;
    else if (c == u',')
        return 1;
    else if (c == u'?')
        return 1;    
return 0;
}

void tokeniser(vector<string> s)
{
 
    string str,temp="";
    fstream f1,f2;
    /*f1.imbue(utf16_locale);
    f2.imbue(utf16_locale);
    _setmode(_fileno(stdout), _O_U16TEXT);*/
    //FILE *ptr = fopen("read.txt","r");
    f1.open("read.txt");
    f2.open("write.txt");

    if(!f1 || !f2)
        cout << "File not found!" << endl;
    else
    {
        while(getline(f1,str))
        {
            //getline(f1,str);
            int j=0;
            for(int i=0;i<str.size();i++)
                {
                    if(isPunctuation(str[i]))
                    {
                    s.push_back(temp);
                    temp = "";
               
                    }
                    else
                    {
                    temp.push_back(str[i]);
                //cout << "Found delimeter\n";
                    }
                }
            s.push_back(temp);
        }
        
    for(int i=0;i<s.size();i++)
    f2 << s[i] << endl;
    }
}

int main()
{
    std::vector<string> store;
    tokeniser(store);
}
