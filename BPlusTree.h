#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include<algorithm>
#include<string>
using namespace std;
int MAX = 3;

class Node {
    bool IS_LEAF;
    string *key;
    string *value;
    int size;
    Node** ptr;
    friend class BPTree;

public:
    Node();
};

class BPTree {
    Node* root;
    void insertInternal(string, string, Node*, Node*);
    Node* findParent(Node*, Node*);

public:
    BPTree();
    void search(string);
    void insert(string, string);
    void display(Node*);
    Node* getRoot();
};

Node::Node()
{
    key = new string[MAX];
    ptr = new Node*[MAX + 1];
    value = new string[MAX];
}


BPTree::BPTree()
{
    root = NULL;
}

void BPTree::search(string x)
{
    if (root == NULL)
    {
        cout << "Tree is empty\n";
    }

    else
    {
        Node* cursor = root;

        while (cursor->IS_LEAF == false)
        {
            for (int i = 0;i<cursor->size;i++)
			{
				//cout << x << " " << cursor->key[i] << "\n";
                if (x < cursor->key[i])
                {
                    cursor = cursor->ptr[i];
                    break;
                }

                if (i == cursor->size - 1)
                {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }

        for (int i=0;i<cursor->size;i++)
		{
			//cout << x << " " << cursor->key[i] << " " << cursor->value[i] << "\n";
            if (cursor->key[i] == x)
            {
                cout << cursor->key[i] << " " << cursor->value[i] << "\n";
                return;
            }
        }
        cout << "Not found\n";
    }
}

void BPTree::insert(string x, string y)
{
    if (root == NULL)
    {
        root = new Node;
        root->key[0] = x;
        root->value[0]=y;
        root->IS_LEAF = true;
        root->size = 1;
    }

    else
    {
        Node* cursor = root;
        Node* parent;

        while (cursor->IS_LEAF==false)
        {
            parent = cursor;
            for (int i=0;i<cursor->size;i++)
            {
                if (x<cursor->key[i])
                {
                    cursor=cursor->ptr[i];
                    break;
                }

                if (i==cursor->size - 1)
                {
                    cursor=cursor->ptr[i + 1];
                    break;
                }
            }
        }

        if (cursor->size<MAX)
        {
            int i = 0;
            while (x>cursor->key[i] && i<cursor->size)
            {
                i++;
            }

            for (int j=cursor->size;j > i; j--)
            {
                cursor->key[j]= cursor->key[j-1];
                cursor->value[j]=cursor->value[j-1];
            }

            cursor->key[i] = x;
            cursor->value[i]=y;
            //cout << x << " " << y << " " << cursor->key[i] << " "
            //<< cursor->value[i] << " " << i << "\n";
            cursor->size++;

            cursor->ptr[cursor->size]= cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size-1] = NULL;
        }

        else
        {
            Node* newLeaf = new Node;

            string virtualNode[MAX + 1];
            string virtualValue[MAX+1];

            for (int i=0;i< MAX;i++)
            {
                virtualNode[i]=cursor->key[i];
                virtualValue[i]=cursor->value[i];
            }
            int i = 0, j;

            // Traverse to find where the new
            // node is to be inserted
            while (x>virtualNode[i] && i<MAX)
            {
                i++;
            }

            for (int j=MAX;j>i;j--)
            {
                virtualNode[j]=virtualNode[j-1];
                virtualValue[j]=virtualValue[j-1];
            }

            virtualNode[i]=x;
            virtualValue[i]=y;
            newLeaf->IS_LEAF=true;

            cursor->size = (MAX+1)/2;
            newLeaf->size=MAX+1-(MAX + 1)/2;

            cursor->ptr[cursor->size]=newLeaf;

            newLeaf->ptr[newLeaf->size]=cursor->ptr[MAX];

            cursor->ptr[MAX]=NULL;

            for (i = 0;i<cursor->size;i++)
            {
                cursor->key[i]=virtualNode[i];
                cursor->value[i]=virtualValue[i];
            }

            for (i=0,j=cursor->size;i<newLeaf->size;i++,j++)
            {
                newLeaf->key[i]=virtualNode[j];
                newLeaf->value[i]=virtualValue[j];
            }

            if (cursor==root)
            {
                Node* newRoot = new Node;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->value[0]=newLeaf->value[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            }
            else
            {
                insertInternal(newLeaf->key[0], newLeaf->value[0] ,parent,newLeaf);
            }
        }
    }
}


void BPTree::insertInternal(string x, string y,Node* cursor,Node* child)
{
	//cout << x << " " << y << endl;
    if (cursor->size<MAX)
    {
        int i=0;

        while (x>cursor->key[i] && i<cursor->size)
        {
            i++;
        }

        for (int j=cursor->size;j>i;j--)
        {
            cursor->key[j]=cursor->key[j-1];
            cursor->value[j]=cursor->value[j-1];
        }

        for (int j=cursor->size+1;j>i+1;j--)
        {
            cursor->ptr[j]=cursor->ptr[j - 1];
        }
        cursor->key[i]=x;
        cursor->value[i]=y;
        cursor->size++;
        cursor->ptr[i+1]=child;
    }

    else
    {
        Node* newInternal = new Node;
        string virtualKey[MAX + 1];
        string virtualValue[MAX+1];
        Node* virtualPtr[MAX + 2];

        for (int i=0;i<MAX;i++)
        {
            virtualKey[i]=cursor->key[i];
            virtualValue[i]=cursor->value[i];
        }

        for (int i=0;i<MAX+1; i++)
        {
            virtualPtr[i] = cursor->ptr[i];
        }

        int i = 0, j;

        while (x>virtualKey[i] && i<MAX)
        {
            i++;
        }

        for (int j=MAX;j>i; j--)
        {
            virtualKey[j]=virtualKey[j-1];
            virtualValue[j]=virtualValue[j-1];
        }

        virtualKey[i]=x;
        virtualValue[i]=y;

        for (int j=MAX+1;j>i+1;j--)
        {
            virtualPtr[j]=virtualPtr[j - 1];
        }

        virtualPtr[i+1]=child;
        newInternal->IS_LEAF = false;

        cursor->size=(MAX + 1)/2;

        newInternal->size=MAX+1-(MAX + 1)/2;

        for (i=0,j=cursor->size;i<newInternal->size;i++,j++)
        {
            newInternal->key[i]=virtualKey[j];
            newInternal->value[i]=virtualValue[j];
        }

        for (i=0,j=cursor->size;i<newInternal->size+1;i++,j++)
        {
            newInternal->ptr[i]=virtualPtr[j];
        }

        if (cursor==root)
        {
            Node* newRoot=new Node;

            newRoot->key[0]=cursor->key[cursor->size];
            newRoot->value[0]=cursor->value[cursor->size];
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
        }

        else
        {
            insertInternal(cursor->key[cursor->size], cursor->value[cursor->size],
            findParent(root,cursor), newInternal);
        }
    }
}


Node* BPTree::findParent(Node* cursor, Node* child)
{
    Node* parent;

    if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF)
    {
        return NULL;
    }

    for(int i=0;i<cursor->size+1;i++)
    {
        if (cursor->ptr[i] == child)
        {
            parent = cursor;
            return parent;
        }

        else
        {
            parent=findParent(cursor->ptr[i], child);

            if (parent!=NULL) return parent;
        }
    }

    return parent;
}

Node* BPTree::getRoot()
{
    return root;
}

#endif