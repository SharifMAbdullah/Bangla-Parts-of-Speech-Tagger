#include <bits/stdc++.h>
using namespace std;

bool isPunctuation(wchar_t c)
{
    if(c == L' ')
        return 1; 
    else if (c ==  L'।')
        return 1; 
    else if (c == L'।')
        return 1; 
    else if (c == L',')
        return 1;
    else if (c == L'?')
        return 1;
return 0;
}

void tokeniser(vector<wstring> s)
{
    wstring str,temp=L"";
    wfstream f1,f2;
    //FILE *ptr = fopen("read.txt","r");
    f1.open("read.txt");
    f2.open("write.txt");

    if(!f1 || !f2)
        cout << "File not found!" << endl;
    else
    {
        getline(f1,str);
        int j=0;
        for(int i=0;i<str.size();i++)
        {
            if(isPunctuation(str[i]))
            {
                s.push_back(temp);
                temp = L"";
               
            }
        else
            {
                temp.push_back(str[i]);
                //cout << "Found delimeter\n";
            }
    }
    s.push_back(temp);
    for(int i=0;i<s.size();i++)
    f2 << s[i] << endl;
    }
}

int main()
{
    std::vector<wstring> store;
    tokeniser(store);
}
