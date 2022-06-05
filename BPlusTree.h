#include<iostream>
using namespace std;
int n,mx; //number of child;
struct mystruct
{
    int currentNode;
    mystruct *parent,*next;
    string *english,*bangla;
    bool lf;
    mystruct **point;
} ;
mystruct *rootNonVerb,*rootVerb,*firstLeaf;

mystruct* createNode()
{
    mystruct *m=new mystruct();


    m->point = new mystruct *[n+1];
    m->english=new string[n];
    m->bangla=new string[n];

    m->currentNode = 0;
    m->parent = NULL;
    m->next = NULL;
    m->lf = true;
    return m;
}
mystruct *findLeaf(mystruct *tempRt,string english)
{

    cout << "Address of root in findleaf : " << *tempRt <<endl;
    while(tempRt->lf==false)
    {
        int i;
        for(i=0; i<tempRt->currentNode; i++) if(english<tempRt->english[i]) break;
        tempRt = tempRt->point[i];
    }
    return tempRt;

}

void insertValueAndPoint(mystruct *parent,string value,mystruct *right)
{
    int i=parent->currentNode-1;
    for(;i>=0; i--)
    {
        if(parent->english[i]<=value) break;
        else
        {
            parent->english[i+1] = parent->english[i];
            parent->point[i+2] = parent->point[i+1];
        }
    }
    parent->english[i+1] = value;
    parent->point[i+2] = right;
    parent->currentNode++;
}

void insertMiddle(mystruct *parent,string value,mystruct *left,mystruct *right,int c)
{
    if(parent==NULL)
    {
        parent = createNode();
        parent->english[0] = value;
        parent->point[0] = left;
        parent->point[1] = right;
        parent->currentNode++;
        parent->lf = false;
        if(c==1) rootNonVerb = parent;
        else rootVerb = parent;
        left->parent = parent;
        right->parent = parent;
        return;
    }
    right->parent = parent;
    insertValueAndPoint(parent,value,right);
    if(parent->currentNode==mx)
    {
        mystruct *splitNode = createNode();
        splitNode->lf = false;
        int j=0;
        for(int i=parent->currentNode-(n-1)/2;i<mx; i++)
        {
            splitNode->english[j] = parent->english[i];
            if(j==0)
            {
                splitNode->point[0] = parent->point[i];
                splitNode->point[0]->parent = splitNode;
            }
            splitNode->point[j+1] = parent->point[i+1];
            splitNode->point[j+1]->parent = splitNode;
            j++;
        }
        parent->currentNode-=(n-1)/2+1;
        splitNode->currentNode = (n-1)/2;
        insertMiddle(parent->parent,parent->english[parent->currentNode],parent,splitNode,c);
    }

}

void insertLeaf(string english,string bangla,int choice)
{
    if(choice==1)
    {
        mystruct *leaf= findLeaf(rootNonVerb,english);
        //cout <<"k";
        int i = leaf->currentNode-1;
        if(i>-1) 
        {
            for(; i>=0; i--)
            {
    	        if(english<leaf->english[i])
    	        {
    		        leaf->english[i+1] = leaf->english[i];
    		        leaf->bangla[i+1] = leaf->bangla[i];
    	        }
    	        else break;
            }
        }
        
        leaf->english[i+1] = english;
        leaf->bangla[i+1] = bangla;
        leaf->currentNode++;

        if(leaf->currentNode==mx)
        {
            mystruct *splitNode = createNode();
            int j=0;
            for(int i=leaf->currentNode-n/2;i<mx; i++)
            {
                splitNode->english[j] = leaf->english[i];
                splitNode->bangla[j] = leaf->bangla[i];
                j++;
            }
            
            leaf->currentNode -= n/2;
            splitNode->currentNode = n/2;
            splitNode->next = leaf->next;
            leaf->next = splitNode;
            insertMiddle(leaf->parent,splitNode->english[0],leaf,splitNode,choice);
        }
    }
    else
    {
        mystruct *leaf= findLeaf(rootVerb,english);
        //cout <<"k";
        int i = leaf->currentNode-1;
        if(i>-1) 
        {
            for(; i>=0; i--)
            {
    	        if(english<leaf->english[i])
    	        {
    		        leaf->english[i+1] = leaf->english[i];
    		        leaf->bangla[i+1] = leaf->bangla[i];
    	        }
    	        else break;
            }
        }
        
        leaf->english[i+1] = english;
        leaf->bangla[i+1] = bangla;
        leaf->currentNode++;

        if(leaf->currentNode==mx)
        {
            mystruct *splitNode = createNode();
            int j=0;
            for(int i=leaf->currentNode-n/2;i<mx; i++)
            {
                splitNode->english[j] = leaf->english[i];
                splitNode->bangla[j] = leaf->bangla[i];
                j++;
            }
            
            leaf->currentNode-=n/2;
            splitNode->currentNode = n/2;
            splitNode->next = leaf->next;
            leaf->next = splitNode;
            insertMiddle(leaf->parent,splitNode->english[0],leaf,splitNode,choice);
        }
    }
}

string searchInTree(string searchEnglish, int choice)
{
	n =3;
	mx=n;
    if(choice == 1)
        rootNonVerb = createNode();
        cout << "address of root : " << &rootNonVerb << endl;
    else 
        rootVerb = createNode();
    mystruct *leaf;
    int i=0;
    string english,bangla;
    ifstream ifile;

    if(choice==1)
    {
        ifile.open("NonVerbDataset.csv");
        if(!ifile) 
            return "problem";

        while(getline(ifile,english))
        {
            cout << i <<endl;
            istringstream iss;
            iss.clear();
            iss.str(english);
            while(iss.good())
            {
                iss>>english;
                bangla = english.substr(english.find(",")+1);
    	        english = english.substr(0,english.find(","));
    	        insertLeaf(english,bangla,1);
            }
        }
    ifile.close();
    }
    
    else
    {
        ifile.open("VerbDataset.csv");
        if(!ifile) 
            return "problem";

        while(getline(ifile,english))
        {
            cout << i <<endl;
            istringstream iss;
            iss.clear();
            iss.str(english);
            while(iss.good())
            {
                iss>>english;
                bangla = english.substr(english.find(",")+1);
    	        english = english.substr(0,english.find(","));
    	        insertLeaf(english,bangla,1);
            }
        }
    ifile.close();
        
    }
    
    	if(choice==1) 
    	    leaf = findLeaf(rootNonVerb,searchEnglish);
    	else 
    	    leaf= findLeaf(rootVerb,searchEnglish);
    	    
    	for(i=0; i<leaf->currentNode; i++) 
    	    {
    	        if(searchEnglish==leaf->english[i]) 
    	        break;
    	    }
    	    
    	if(i==leaf->currentNode) 
    	    return "unknown";
    	else 
    	    return leaf->bangla[i];
}