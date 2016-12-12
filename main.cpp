#include<iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
//#include<conio.h>
#define maxsize 20


using namespace std;
typedef struct Node{
    char data[10];
    struct Node *firstchild, *nextsibling;
}Node,*Tree;


typedef struct Queue{
    Tree *base;
    int front, rear;
}Queue;


void Init(Queue &Q){
    Q.base = (Tree *) malloc( sizeof(Tree) * maxsize );
    Q.front = 0;
    Q.rear = 0;
    if(!Q.base){exit(1);}
}


int EmptyQueue(Queue &Q)
{
    if(Q.front == Q.rear)
    {
        return 1;
    }
    else return 0;
}
void EnQueue(Queue &Q,Node *&p)
{
    if((Q.rear+1)%maxsize == Q.front)
        exit(1);
    else {
        Q.base[Q.rear] = p;
        Q.rear = (Q.rear+1) % maxsize;
    }
}
void DeQueue(Queue &Q,Node *&p)
{
    if(EmptyQueue(Q))
        exit(1);
    else {
        p = Q.base[Q.front];
        Q.front = (Q.front+1) % maxsize;
    }
}
void gethead(Queue &Q,Node *&p)
{
    if(!EmptyQueue(Q)){
        p = Q.base[Q.front];
    }
    else exit(1);
}
void CreatTree(Tree &T)
{
    Queue Q;
    Init(Q);
    Node *p,*q,*r;
    char f[10],c[10];   //以父亲孩子的形式输入
    T = NULL;
    cout<<"请以父亲、孩子的形式输入节点讯息:"<<endl;
    cin>>f>>c;
    char star[] = "*";
    while(strcmp(c,star)!=0)
    {
        p = (Node *)malloc(sizeof(Node));
        p -> firstchild = NULL;
        p -> nextsibling = NULL;
        strcpy(p->data,c);
        EnQueue(Q,p);
        if(strcmp(f,star)==0) T=p;
        else{
            gethead(Q,q);
            while(strcmp(q->data,f)!=0)
            {
                DeQueue(Q,q);
                gethead(Q,q);
            }
            if(!(q -> firstchild))
                q -> firstchild = p;
            else
            {
                r = q -> firstchild;
                while( r -> nextsibling)
                {
                    r = r -> nextsibling;
                }
                r -> nextsibling = p;
            }
        }
        cin>>f>>c;
    }
}

void preordertree(Node *T)
{
    Node *p = T;
    if(p == NULL){
//        cout<<"该树为空"<<endl;
//        exit(1);
        return;
    }
    else{
        cout<<p->data<<endl;
        preordertree(p->firstchild);
        preordertree(p->nextsibling);
    }
}
void leveltree(Node *T)
{
    Queue Q;
    Node *p = T,*q;
    Init(Q);
    cout<<"对该树进行层次遍历："<<endl;
    if(!T)
        return;
    else
    {
        EnQueue(Q,p);
        cout<<p->data<<endl;
        while(!EmptyQueue(Q))
        {
            DeQueue(Q,p);
            if(p -> firstchild)
            {
                q = p -> firstchild;
                while(q)
                {
                    EnQueue(Q,q);
                    cout<<q->data<<endl;
                    q = q -> nextsibling;
                }
            }
        }
    }

}
void menu(Node *&T)
{
    system("cls");
    int n;
    printf("1：采用树的孩子兄弟链表存储创建的树\n");
    printf("2：通过深度优先遍历搜索该树\n");
    printf("3: 采用层次优先遍历搜索该树\n");
    printf("4: 退出\n");
    printf(" 请回复编号选择功能：\n");
    scanf("%d",&n);
    while(n!=1&&n!=2&&n!=3&&n!=4)
    {
        printf("输入错误！！请重试！\n");
        scanf("%d",&n);
    }
    switch (n)
    {
        case 1:CreatTree(T);
            break;
        case 2:printf("对域名进行深度优先遍历如下：\n");
            preordertree(T);
            break;
        case 3:leveltree(T);
            break;
        case 4:printf("谢谢使用");
            exit(-1);break;
    }
    menu(T);
}


int main()
{
    Node *T;
    menu(T);
    return 0;
}















