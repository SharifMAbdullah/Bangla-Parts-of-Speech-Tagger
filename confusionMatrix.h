#include <iostream>
#include<fstream>
#include"stringOperations.h"
using namespace std;
#define NN 0
#define PRO 1
#define VRB 2
#define ADV 3
#define ADJ 4
#define PRE 5
#define CON 6
#define INTJ 7
int matrix[8][8];                            
    //      NN  PRO VRB ADV ADJ PRE CON INTJ
    //  NN  2   0   0   0   0   0   0   1
    //  PRO 1   0   0   0   0   0   0   0
    //  VRB 0   0   1   0   0   0   1   0
    //  ADV 0   0   0   0   0   0   0   0
    //  ADJ 0   0   0   0   1   0   0   0
    //  PRE 0   0   0   0   0   0   0   0
    //  CON 0   0   0   0   0   0   0   0
//  INTJ    0   0   0   0   0   0   0   0
void checkNN(string actual, string test)
{
    if(stringFind(actual,"noun")!=-1)
    {
        if(stringFind(test,"pronoun") != -1)
            matrix[NN][PRO]++;
        else if( stringFind(test,"verb") != -1)
            matrix[NN][VRB]++;
        else if( stringFind(test, "adverb") !=  -1)
            matrix[NN][ADV]++;
        else if( stringFind(test,"adjective")!=  -1)
            matrix[NN][ADJ]++;
        else if(  stringFind(test,"preposition")!=  -1)
            matrix[NN][PRE]++;
        else if( stringFind(test,"conjunction")!=  -1)
            matrix[NN][CON]++;
        else if( stringFind(test,"interjection")!=  -1)
            matrix[NN][INTJ]++;
    }    
}

void checkPRO(string actual, string test)
{
    if(stringFind(actual,"pronoun") != -1)
    {
        if( stringFind(test,"noun")!=  -1)
            matrix[PRO][NN]++;
        else if( stringFind(test,"verb")!=  -1)
            matrix[PRO][VRB]++;
        else if( stringFind(test,"adverb")!=  -1)
            matrix[PRO][ADV]++;
        else if( stringFind(test,"adjective")!=  -1)
            matrix[PRO][ADJ]++;
        else if( stringFind(test,"preposition")!=  -1)
            matrix[PRO][PRE]++;
        else if( stringFind(test,"conjunction")!=  -1)
            matrix[PRO][CON]++;
        else if( stringFind(test,"interjection")!=  -1)
            matrix[PRO][INTJ]++;    
    }   
}

void checkVRB(string actual, string test)
{
    if(stringFind(actual,"verb") != -1)
    {
        if(stringFind(test,"noun")!=  -1)
            matrix[VRB][NN]++;
        else if(stringFind(test,"pronoun")!=  -1)
            matrix[VRB][PRO]++;
        else if(stringFind(test,"adverb")!=  -1)
            matrix[VRB][ADV]++;
        else if(stringFind(test,"adjective")!=  -1)
            matrix[VRB][ADJ]++;
        else if(stringFind(test,"preposition")!=  -1)
            matrix[VRB][PRE]++;
        else if(stringFind(test,"conjunction")!=  -1)
            matrix[VRB][CON]++;
        else if(stringFind(test,"interjection")!=  -1)
            matrix[VRB][INTJ]++;    
    }
}

void checkADV(string actual, string test)
{
    if(stringFind(actual,"adverb")!=-1)
    {
        if(stringFind(test,"noun")!=  -1)
            matrix[ADV][NN]++;
        else if(stringFind(test,"pronoun")!=  -1)
            matrix[ADV][PRO]++;
        else if(stringFind(test,"verb")!=  -1)
            matrix[ADV][VRB]++;
        else if(stringFind(test,"adjective")!=  -1)
            matrix[ADV][ADJ]++;
        else if(stringFind(test,"preposition")!=  -1)
            matrix[ADV][PRE]++;
        else if(stringFind(test,"conjunction")!=  -1)
            matrix[ADV][CON]++;
        else if(stringFind(test,"interjection")!=  -1)
            matrix[ADV][INTJ]++;    
    }
}

void checkADJ(string actual, string test)
{
    if(stringFind(actual,"adjective") != -1)
    {
        if(stringFind(test,"noun")!=  -1)
            matrix[ADJ][NN]++;
        else if(stringFind(test,"pronoun")!=  -1)
            matrix[ADJ][PRO]++;
        else if(stringFind(test,"verb")!=  -1)
            matrix[ADJ][VRB]++;
        else if(stringFind(test,"adverb")!=  -1)
            matrix[ADJ][ADV]++;
        else if(stringFind(test,"preposition")!=  -1)
            matrix[ADJ][PRE]++;
        else if(stringFind(test,"conjunction")!=  -1)
            matrix[ADJ][CON]++;
        else if(stringFind(test,"interjection")!=  -1)
            matrix[ADJ][INTJ]++;    
    }
}

void checkPRE(string actual, string test)
{
    if(stringFind(actual,"preposition") != -1)
    {
        if(stringFind(test,"noun")!=  -1)
            matrix[PRE][NN]++;
        else if(stringFind(test,"pronoun")!=  -1)
            matrix[PRE][PRO]++;
        else if(stringFind(test,"verb")!=  -1)
            matrix[PRE][VRB]++;
        else if(stringFind(test,"adverb")!=  -1)
            matrix[PRE][ADV]++;
        else if(stringFind(test,"adjective")!=  -1)
            matrix[PRE][ADJ]++;
        else if(stringFind(test,"conjunction")!=  -1)
            matrix[PRE][CON]++;
        else if(stringFind(test,"interjection")!=  -1)
            matrix[PRE][INTJ]++;    
    }
}

void checkCON(string actual, string test)
{
    if(stringFind(actual,"conjunction") != -1)
    {
        if(stringFind(test,"noun")!=  -1)
            matrix[CON][NN]++;
        else if(stringFind(test,"pronoun")!=  -1)
            matrix[CON][PRO]++;
        else if(stringFind(test,"verb")!=  -1)
            matrix[CON][VRB]++;
        else if(stringFind(test,"adverb")!=  -1)
            matrix[CON][ADV]++;
        else if(stringFind(test,"adjective")!=  -1)
            matrix[CON][ADJ]++;
        else if(stringFind(test,"preposition")!=  -1)
            matrix[CON][PRE]++;
        else if(stringFind(test,"interjection")!=  -1)
            matrix[CON][INTJ]++;    
    }
}

void checkINTJ(string actual, string test)
{
    if(stringFind(actual,"interjection") != -1)
    {
        if(stringFind(test,"noun")!=  -1)
            matrix[INTJ][NN]++;
        else if(stringFind(test,"pronoun")!=  -1)
            matrix[INTJ][PRO]++;
        else if(stringFind(test,"verb")!=  -1)
            matrix[INTJ][VRB]++;
        else if(stringFind(test,"adverb")!=  -1)
            matrix[INTJ][ADV]++;
        else if(stringFind(test,"adjective")!=  -1)
            matrix[INTJ][ADJ]++;
        else if(stringFind(test,"preposition")!=  -1)
            matrix[INTJ][PRE]++;
        else if(stringFind(test,"conjunction")!=  -1)
            matrix[INTJ][CON]++;    
    }
}

void checkMatch(string actual)
{
    if(stringFind(actual,"pronoun")!=  -1) 
        matrix[1][1]++;
    else if(stringFind(actual,"noun")!=  -1) 
        matrix[0][0]++;
    else if(stringFind(actual,"verb")!=  -1) 
        matrix[2][2]++;
    else if(stringFind(actual,"adverb")!=  -1) 
        matrix[3][3]++;
    else if(stringFind(actual,"adjective")!=  -1) 
        matrix[4][4]++;
    else if(stringFind(actual,"preposition")!=  -1) 
        matrix[5][5]++;
    else if(stringFind(actual,"conjunction")!=  -1) 
        matrix[6][6]++;
    else if(stringFind(actual,"interjection")!=  -1) 
        matrix[7][7]++;
}

void printMatrix()
{
    string s[8]  = {"NN",  "PRO", "VRB", "ADV", "ADJ", "PRE", "CON", "INTJ"};
    printf("\tNN\tPRO\tVRB\tADV\tADJ\tPRE\tCON\tINTJ\n");
    for(int j=0;j<8;j++)
    {
    cout << s[j] <<"\t";
        for(int k=0;k<8;k++)
        {
            printf("%d\t",matrix[j][k]);
        }
    printf("\n");
    }
}

int calculateTotalElements()
{
    int result = 0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            {
                result += matrix[i][j];
            }

return (float)result;
}

int calculateAccurateResult()
{
    int result = 0;
    for(int i=0;i<8;i++)
        result += matrix[i][i];

cout << "Total true positive results " << result <<"\n";
return (float)result;
}

int calculateFalseNegative()
{
    int result = 0;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(i==j) continue;
            result += matrix[i][j];
        }
    }
cout << "Total false negative results " << result <<"\n";
return (float)result;
}


float calculateAccuracyRate()
{
    return 100*calculateAccurateResult()/calculateTotalElements();
}

float calculateMisClassificationRate()
{
    return 100*calculateFalseNegative()/calculateTotalElements();
}
//checks if produced outputs are same as actual outputs
void POSchecker()
{
    fstream f1,f2;

    for(int x = 1; x <= 10; x++)
    {
        string A = to_string(x);
        string output_file = "testOutputs/testOutput" + A + ".txt";
        string actual_file = "accurateOutputs/accurateOutput" + A + ".txt";
        f1.open(output_file);
        f2.open(actual_file);
        if(!f1) cout << "testOutput file " << A <<  "could not be opened\n";
        else if(!f2) cout << "accurateOutput file "<< A << "could not be opened\n";
        else   cout <<"Test files opened correctly\n";
        
        while(f1.peek()!=EOF)
        {
            string actual = "";
            string test = "";
            f1.clear();
            f2.clear();
            getline(f1,actual);
            getline(f2,test);
            
            if(actual==test)
                checkMatch(actual);
                
            else
                {
                    checkNN(actual,test);
                    checkPRO(actual,test);
                    checkADV(actual,test);
                    checkADJ(actual,test);
                    checkPRE(actual,test);
                    checkCON(actual,test);
                    checkINTJ(actual,test);
                }
        }
    f1.close();
    f2.close();
    }
}