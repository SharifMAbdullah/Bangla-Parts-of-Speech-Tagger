#include <bits/stdc++.h>
using namespace std;
int main()
{
    wstring str,temp=L"";
    std::vector<wstring> store;
    wfstream f1,f2;
    //FILE *ptr = fopen("read.txt","r");
    if(!f1 && !f2)
        cout << "File not found!" << endl;
    else
    {
    f1.open("read.txt");
    f2.open("write.txt");
    getline(f1,str);
    int j=0;
    for(int i=0;i<str.size();i++)
    {
        if(str[i] == ' ' || str[i] ==  L'।' || str[i] == L'।' || str[i] == ',')
            {
                store.push_back(temp);
                temp = L"";
               
            }
        else
            {
                temp.push_back(str[i]);
                //cout << "Found delimeter\n";
            }
    }
    store.push_back(temp);
    for(int i=0;i<str.size();i++)
    f2 << store[i] << endl;
    }
}
