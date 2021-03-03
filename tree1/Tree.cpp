/**** 2021.2.23 - 2021.3.2****/
/**** 3.2 后序遍历的非递归，层次遍历，递归创建二叉树 ****/
#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
int top=-1;                           //栈顶位置
int front=0,rear=0;                   //初始化队头和尾指针
/**** 结 构 体 声 明 ****/
//二叉树
typedef struct BTree{                  
    int data;
    struct BTree *lchild,*rchild;
}BiTree;
//后序遍历二叉树
typedef struct SiNode{                
    int state;
    BiTree *p;
}SiNode;
/**** 函 数 声 明 ****/
BiTree *CreateTree();                 //创建完全二叉数
void PreBiTree(BiTree *T);            //先序遍历二叉树（递归）
void InBiTree(BiTree *T);             //中序遍历二叉树（递归）
void PostBiTree(BiTree *T);           //后序遍历二叉树（递归）
void PreBiTree_Stack(BiTree *T);      //先序遍历二叉树（非递归）
void InBiTree_Stack(BiTree *T);       //中序遍历二叉树（非递归）
void PostBiTree_Stack(BiTree *T);     //后序遍历二叉树（非递归）
void LevelBiTree_Queue(BiTree *T);    //层次遍历二叉树（非递归）
void EnQueue(BiTree *a,BiTree t);     //层次遍历 队列入队
BiTree *DeQueue(BiTree *a);           //层次遍历 队列出队
void displayElem(BiTree *elem);       //对该节点的操作
void push(BiTree **a,BiTree *elem);   //进栈函数
void pop();                           //出栈函数
BiTree *getTopElem(BiTree **a);       //获取栈顶元素
void postpush(SiNode *a,SiNode s);    //后序遍历进栈函数
void CreatePreBiTree(BiTree *t);      //递归遍历创建二叉树

/*
    创建完全二叉数 1 2 3 4 5 6
*/
BiTree *CreateTree(){
    BiTree *T=(BiTree *)malloc(sizeof(BiTree));
    T->data=1;
    T->lchild=(BiTree *)malloc(sizeof(BiTree));
    T->rchild=(BiTree *)malloc(sizeof(BiTree));
    T->lchild->data=2;
    T->rchild->data=3;
    T->lchild->lchild=(BiTree *)malloc(sizeof(BiTree));
    T->lchild->rchild=(BiTree *)malloc(sizeof(BiTree));
    T->lchild->lchild->data=4;
    T->lchild->rchild->data=5;
    T->lchild->rchild->lchild=NULL;
    T->lchild->rchild->rchild=NULL;
    T->lchild->lchild->lchild=NULL;
    T->lchild->lchild->rchild=NULL;
    T->rchild->lchild=(BiTree *)malloc(sizeof(BiTree));
    T->rchild->lchild->data=6;
    T->rchild->rchild=NULL;
    T->rchild->lchild->lchild=NULL;
    T->rchild->lchild->rchild=NULL;
    return T;
}

/*
    先序遍历二叉树（递归） 1 2 4 5 3 6 先访问根节点，再访问左孩子，最后访问右孩子
*/
void PreBiTree(BiTree *T){
    if(T){
        displayElem(T);
        PreBiTree(T->lchild);
        PreBiTree(T->rchild);
    }
    return ; //为空返回
}

/*
    中序遍历二叉树（递归） 4 2 5 1 6 3 先访问左孩子，再访问根节点，最后访问右孩子
*/
void InBiTree(BiTree *T){
    if(T){
        InBiTree(T->lchild);
        displayElem(T);
        InBiTree(T->rchild);
    }
    return ; //为空返回
}

/*
    后序遍历二叉树（递归） 4 5 2 6 3 1 先访问左孩子，再访问右孩子，最后访问根节点
*/
void PostBiTree(BiTree *T){
    if(T){
        PostBiTree(T->lchild);
        PostBiTree(T->rchild);
        displayElem(T);
    }
    return ; //为空返回
}

/*
    非递归遍历二叉树 进栈函数
*/
void push(BiTree **a,BiTree *elem){
    a[++top]=elem;
}

/*
    非递归遍历二叉树 出栈函数
*/
void pop(){
    if(top==-1){
        return ;
    }
    top--;
}

/*
    非递归遍历二叉树 获取栈顶元素
*/
BiTree *getTopElem(BiTree **a){
    return a[top];
}

/*
    先序遍历二叉树（非递归）
*/
void PreBiTree_Stack(BiTree *T){
    BiTree *a[10];
    BiTree *p=NULL;
    push(a,T); //根节点先进栈
    while(top!=-1){
        p=getTopElem(a);
        pop();
        while(p){
            displayElem(p); //栈顶不为空则展示
            if(p->rchild){
                push(a,p->rchild); //右孩子进栈
            }
            p=p->lchild;    //左孩子进栈
        }
    }
}

/*
    中序遍历二叉树（非递归）
*/
void InBiTree_Stack(BiTree *T){
    BiTree *a[10];
    BiTree *p=NULL;
    push(a,T); //根节点进栈
    while(top!=-1){
        while((p=getTopElem(a)) && p){
            push(a,p->lchild);
        }
        pop();//把左孩子的左空孩子NULL弹出
        if(top!=-1){
            p=getTopElem(a);
            displayElem(p);
            pop();
            push(a,p->rchild);//p结点的左孩子遍历完，开始遍历右孩子
        }
    }
}

/*
    后序遍历进栈函数
*/
void postpush(SiNode *a,SiNode s){
    a[++top]=s;
}

/*
    后序遍历二叉树（非递归）
*/
void PostBiTree_Stack(BiTree *T){
    SiNode a[10];
    BiTree *p=T;
    SiNode s;
    int state;
    while(p || top!=-1){
        while(p){
            s.p=p;
            s.state=0;
            postpush(a,s);
            p=p->lchild;
        }
        s=a[top];
        pop();
        p=s.p;
        state=s.state;
        if(state==0){
            s.p=p;
            s.state=1;
            postpush(a,s);
            p=p->rchild;
        }else{
            displayElem(p);
            p=NULL;
        }
    }
}

/*
    层次遍历 队列入队
*/
void EnQueue(BiTree **a,BiTree *t){
    a[rear++]=t;
}

/*
    层次遍历 队列出队
*/
BiTree *DeQueue(BiTree **a){
    return a[front++];
}

/*
    层次遍历
*/
void LevelBiTree_Queue(BiTree *T){
    BiTree *p;
    BiTree *a[20];
    EnQueue(a,T);
    while(front<rear){
        p=DeQueue(a);
        displayElem(p);
        if(p->lchild){
            EnQueue(a,p->lchild);
        }
        if(p->rchild){
            EnQueue(a,p->rchild);
        }
    }
}

/*
    对该结点的操作
*/
void displayElem(BiTree *elem){
    cout<<elem->data<<" ";
}

/*
    先序遍历 创建二叉树
*/
BiTree *a;
BiTree *returnFather(BiTree *t,int state){
    if(state==1){
        return a;
    }else{
        a=t;
    }
}
int i=0;
void CreatePreBiTree(BiTree *t,char ch[]){
	if (ch[i] == '*'){//如果输入*则为空
		t = NULL;
        i++;
        CreatePreBiTree(returnFather(t,1),ch);
	}else if(ch[i] == '@'){
        return;
    }else{
		t = (BiTree *)malloc(sizeof(BiTree));
		t->data = ch[i];
        returnFather(t,0);
        i++;
		CreatePreBiTree(t->lchild,ch);
		CreatePreBiTree(t->rchild,ch);
	}
}

/*
    主函数
*/
int main(){
    BiTree *BTree=CreateTree();
    cout<<"先序遍历（递归）：  ";
    PreBiTree(BTree);
    cout<<endl<<"中序遍历（递归）：  ";
    InBiTree(BTree);
    cout<<endl<<"后序遍历（递归）：  ";
    PostBiTree(BTree);
    cout<<endl<<"先序遍历（非递归）：";
    PreBiTree_Stack(BTree);
    cout<<endl<<"中序遍历（非递归）：";
    InBiTree_Stack(BTree);
    cout<<endl<<"后序遍历（非递归）：";
    PostBiTree_Stack(BTree);
    cout<<endl<<"层次遍历（非递归）：";
    LevelBiTree_Queue(BTree);
    cout<<endl<<"（先序）创建一个二叉树(*表示该节点为空)：";
    BiTree **t=NULL;
    char ch[20];
    char c;
    int j=0;
    while(c!='@'){
        if((c=getchar())!=' '){
            ch[j++]=c;
        }
    }
    ch[j]=0;
    CreatePreBiTree(*t,ch);
    PreBiTree(*t);
    return 0;
}