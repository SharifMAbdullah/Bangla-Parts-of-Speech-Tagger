#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int n=3,MAX=n; //number of child;
struct BPTnode
{
    int currentNode;
    BPTnode *parent,*next;
    string *word,*part_of_speech;
    bool lf;
    BPTnode **point;
} ;
BPTnode *root,*firstLeaf;

BPTnode* createNode()
{
    BPTnode *m=new BPTnode();


    m->point = new BPTnode *[n+1];
    m->word=new string[n];
    m->part_of_speech=new string[n];

    m->currentNode = 0;
    m->parent = NULL;
    m->next = NULL;
    m->lf = true;
    return m;
}
BPTnode *findLeaf(BPTnode *tempRt,string word)
{

    while(tempRt->lf==false)
    {
        int i;
        for(i=0; i<tempRt->currentNode; i++) 
            if(word<tempRt->word[i]) 
                break;
        tempRt = tempRt->point[i];
    }
    return tempRt;

}

void insertValueAndPoint(BPTnode *parent,string value,BPTnode *right)
{
    int i=parent->currentNode-1;
    for(;i>=0; i--)
    {
        if(parent->word[i]<=value)
            break;
        else
        {
            parent->word[i+1] = parent->word[i];
            parent->point[i+2] = parent->point[i+1];
        }
    }
    parent->word[i+1] = value;
    parent->point[i+2] = right;
    parent->currentNode++;
}

void insertMiddle(BPTnode *parent,string value,BPTnode *left,BPTnode *right)
{
    if(parent==NULL)
    {
        parent = createNode();
        parent->word[0] = value;
        parent->point[0] = left;
        parent->point[1] = right;
        parent->currentNode++;
        parent->lf = false;
        root = parent;
        left->parent = parent;
        right->parent = parent;
        return;
    }
    right->parent = parent;
    insertValueAndPoint(parent,value,right);
    if(parent->currentNode==MAX)
    {
        BPTnode *splitNode = createNode();
        splitNode->lf = false;
        int j=0;
        for(int i=parent->currentNode-(n-1)/2;i<MAX; i++)
        {
            splitNode->word[j] = parent->word[i];
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
        insertMiddle(parent->parent,parent->word[parent->currentNode],parent,splitNode);
    }

}

void insertLeaf(string word,string part_of_speech)
{
    BPTnode *leaf = findLeaf(root,word);
    int i= leaf->currentNode-1;
    if(i>-1) 
    {
        for(; i>=0; i--)
        {
    	    if(word<leaf->word[i])
    	    {
    		    leaf->word[i+1] = leaf->word[i];
    		    leaf->part_of_speech[i+1] = leaf->part_of_speech[i];
    	    }
    	    else break;
        }
    }
    leaf->word[i+1] = word;
    leaf->part_of_speech[i+1] = part_of_speech;
    leaf->currentNode++;

    if(leaf->currentNode==MAX)
    {
        BPTnode *splitNode = createNode();
        int j=0;
        for(int i=leaf->currentNode-n/2;i<MAX; i++)
        {
            splitNode->word[j] = leaf->word[i];
            splitNode->part_of_speech[j] = leaf->part_of_speech[i];
            j++;
        }
        leaf->currentNode-=n/2;
        splitNode->currentNode = n/2;
        splitNode->next = leaf->next;
        leaf->next = splitNode;
        insertMiddle(leaf->parent,splitNode->word[0],leaf,splitNode);
    }
}

string searchInTree(string searchEnglish)
{
    root = createNode();
    BPTnode *leaf;
    int i=0;
    string word,part_of_speech;
    ifstream ifile;
    ifile.open("postags.txt");
    if(!ifile) 
        return "problem";

    while(ifile>>word)
    {
    	getline(ifile,part_of_speech);
    	insertLeaf(word,part_of_speech);
    }
    
    leaf= findLeaf(root,searchEnglish);
    for(i=0; i<leaf->currentNode; i++) 
        if(searchEnglish==leaf->word[i]) 
            break;

    if(i==leaf->currentNode) 
        return "unknown";

ifile.close();
return leaf->part_of_speech[i];
}

#endif