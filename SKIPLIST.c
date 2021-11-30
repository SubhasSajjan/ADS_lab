#include<bits/stdc++.h>
using namespace std;

class Node{
  public:
  int  key;
  Node **foward;
  Node(int,int);
};


Node::Node(int key , int level)
{
    this->key=key;
    foward=new Node*[level+1];
    memset(foward , 0 , sizeof(Node*)*(level+1));
}


class SkipList
{
    int MAXLVL;
    float p;
    int level;
    Node  *header;
    public:
    SkipList(int,float);
    int randomLevel();
    Node *createNode(int , int);
    void insertElement(int);
    void displayList();
    void deleteElement(int);
    void searchElement(int);
};

SkipList::SkipList(int MAXLVL , float p )
{
    this->MAXLVL = MAXLVL;
    this->p=p;
    level=0;


    header = new Node(-1 , MAXLVL);
};

int SkipList::randomLevel()
{
    float r = (float)rand()/RAND_MAX;
    int lvl = 0;
    while( r < p && lvl<MAXLVL)
    {
        lvl++;
        r = (float) rand()/RAND_MAX;

    }
    return lvl;
};


Node* SkipList::createNode(int key , int level)
{
    Node *n = new Node(key , level);
    return n;
};


void SkipList::insertElement(int key)
{
    Node *current = header;
    Node *update[MAXLVL+1];
    memset(update , 0 , sizeof(Node*)*(MAXLVL+1));

    for(int i = level ; i >= 0 ; i--)
    {
        while(current->foward[i] != NULL && current->foward[i]->key < key)
        current=current->foward[i];
        update[i]=current;
    }

    current = current->foward[0];

    if(current == NULL || current->key != key)
    {
        int rlevel = randomLevel();
        if(rlevel > level)
        {
            for(int i=level+1 ; i < rlevel+1 ; i++)
            update[i] = header;

            level = rlevel;
        }
        Node *n = createNode(key , rlevel);

        for(int i =0 ; i <=rlevel ; i++)
        {
            n->foward[i] = update[i]->foward[i];
            update[i]->foward[i] = n;
        }
        cout<<"Successfully inserted Element"<<key<<"\n";

    }
};


void SkipList::deleteElement(int key)
{
    Node *current = header;

    Node  *update[MAXLVL+1];
    memset(update , 0 , sizeof(Node*)*(MAXLVL+1));
    for(int i=level ; i>= 0 ; i--)
    {
        while(current->foward[i] != NULL && current->foward[i]->key < key)
        current = current->foward[i];
        update[i] = current;
    }

    current = current->foward[0];

    if(current != NULL and current->key == key)
    {
        for(int i = 0 ; i <= level ; i++)
        {
            if(update[i]->foward[i]!= current)
            break;

            update[i]->foward[i] != current->foward[i];
        }
        while(level > 0  && header->foward[level]==0)
        level--;
        cout<<"Successfully deleted key"<<key<<"\n";
    }
};


void SkipList::searchElement(int key)
{
    Node *current = header;

    for(int i=level ; i>= 0 ; i--)
    {
        while(current->foward[i] && current->foward[i]->key<key)
        current = current->foward[i];
    }

    current=current->foward[0];

    if(current and current->key == key)
    cout<<"Found key:"<<key<<"\n";
};
void SkipList::displayList()
{
    for(int i=0 ; i <= level ; i++)
    {
        Node *node = header->foward[i];
        cout<<"Level "<<i<<" : ";
        while(node != NULL)
        {
            cout<<node->key<<" ";
            node = node->foward[i];
        }
        cout<<"\n";
    }
};
int main()
{
    // Seed random number generator
    srand((unsigned)time(0));

    // create SkipList object with MAXLVL and P
    SkipList lst(6, 0.5);

    lst.insertElement(10);
    lst.insertElement(20);
    lst.insertElement(30);
    lst.insertElement(40);
    lst.insertElement(50);
    lst.insertElement(60);
    lst.insertElement(70);
    lst.insertElement(80);
    lst.insertElement(90);
    lst.insertElement(100);
    lst.displayList();


    lst.searchElement(90);


    lst.deleteElement(90);
    lst.displayList();
}
