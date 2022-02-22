#include <bits/stdc++.h>
#include <codecvt>
#include <locale>
#include <fcntl.h>
#include<uchar.h>
using namespace std;

bool isDari(wstring c)
{
    //std::locale::global(std::locale(""));
    wstring ch = L"\u0964";
    if (c == ch)
    return 1;
return 0;
}

void replaceDari()
{
    wstring str;
    wfstream f1;
    f1.open("read.txt");

    if(!f1)
        cout << "File not found!" << endl;
    else
    {
        while(getline(f1,str))
        {
                    if(isDari(str))
                    {
                        str = L" ";
                    }
        }
    }
f1.close();
}

bool isPunctuation(wchar_t c)
{
    //std::locale::global(std::locale(""));
    wchar_t ch = L'\u0964';
    //if (c == ch)
    //if(isDari(c))
        //return 1;
    //if(iswspace(c))
        //return 1;    
    //if(iswblank(c))
        //return 1;
    //if(iswpunct(c))
        //return 1;
    if(c == L' ')
        return 1; 
    //else if (u_isalpha(।))
        //return 1; 
    //else if (c == L'।')
        //return 1; 
    else if (c ==  L'\r' || c ==  L'\n')
        return 1;
    else if (c == L',')
        return 1;
    else if (c == L'?')
        return 1;    
return 0;
}

void tokeniser(vector<wstring> s)
{

    //std::locale::global(std::locale(""));
    wstring str,temp=L"";
    wfstream f1,f2;
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
                    if(temp.size()>0)
                        {
                            s.push_back(temp);
                            temp = L"";
                        }
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
f1.close();
f2.close();
}

int main()
{
    //setlocale(LC_ALL, "en_US.utf8");
    std::vector<wstring> store;
    replaceDari();
    tokeniser(store);
}
