/**** 2021.2.23 - 2021.3.2****/
/**** 3.2 ��������ķǵݹ飬��α������ݹ鴴�������� ****/
#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
int top=-1;                           //ջ��λ��
int front=0,rear=0;                   //��ʼ����ͷ��βָ��
/**** �� �� �� �� �� ****/
//������
typedef struct BTree{                  
    int data;
    struct BTree *lchild,*rchild;
}BiTree;
//�������������
typedef struct SiNode{                
    int state;
    BiTree *p;
}SiNode;
/**** �� �� �� �� ****/
BiTree *CreateTree();                 //������ȫ������
void PreBiTree(BiTree *T);            //����������������ݹ飩
void InBiTree(BiTree *T);             //����������������ݹ飩
void PostBiTree(BiTree *T);           //����������������ݹ飩
void PreBiTree_Stack(BiTree *T);      //����������������ǵݹ飩
void InBiTree_Stack(BiTree *T);       //����������������ǵݹ飩
void PostBiTree_Stack(BiTree *T);     //����������������ǵݹ飩
void LevelBiTree_Queue(BiTree *T);    //��α������������ǵݹ飩
void EnQueue(BiTree *a,BiTree t);     //��α��� �������
BiTree *DeQueue(BiTree *a);           //��α��� ���г���
void displayElem(BiTree *elem);       //�Ըýڵ�Ĳ���
void push(BiTree **a,BiTree *elem);   //��ջ����
void pop();                           //��ջ����
BiTree *getTopElem(BiTree **a);       //��ȡջ��Ԫ��
void postpush(SiNode *a,SiNode s);    //���������ջ����
void CreatePreBiTree(BiTree *t);      //�ݹ��������������

/*
    ������ȫ������ 1 2 3 4 5 6
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
    ����������������ݹ飩 1 2 4 5 3 6 �ȷ��ʸ��ڵ㣬�ٷ������ӣ��������Һ���
*/
void PreBiTree(BiTree *T){
    if(T){
        displayElem(T);
        PreBiTree(T->lchild);
        PreBiTree(T->rchild);
    }
    return ; //Ϊ�շ���
}

/*
    ����������������ݹ飩 4 2 5 1 6 3 �ȷ������ӣ��ٷ��ʸ��ڵ㣬�������Һ���
*/
void InBiTree(BiTree *T){
    if(T){
        InBiTree(T->lchild);
        displayElem(T);
        InBiTree(T->rchild);
    }
    return ; //Ϊ�շ���
}

/*
    ����������������ݹ飩 4 5 2 6 3 1 �ȷ������ӣ��ٷ����Һ��ӣ������ʸ��ڵ�
*/
void PostBiTree(BiTree *T){
    if(T){
        PostBiTree(T->lchild);
        PostBiTree(T->rchild);
        displayElem(T);
    }
    return ; //Ϊ�շ���
}

/*
    �ǵݹ���������� ��ջ����
*/
void push(BiTree **a,BiTree *elem){
    a[++top]=elem;
}

/*
    �ǵݹ���������� ��ջ����
*/
void pop(){
    if(top==-1){
        return ;
    }
    top--;
}

/*
    �ǵݹ���������� ��ȡջ��Ԫ��
*/
BiTree *getTopElem(BiTree **a){
    return a[top];
}

/*
    ����������������ǵݹ飩
*/
void PreBiTree_Stack(BiTree *T){
    BiTree *a[10];
    BiTree *p=NULL;
    push(a,T); //���ڵ��Ƚ�ջ
    while(top!=-1){
        p=getTopElem(a);
        pop();
        while(p){
            displayElem(p); //ջ����Ϊ����չʾ
            if(p->rchild){
                push(a,p->rchild); //�Һ��ӽ�ջ
            }
            p=p->lchild;    //���ӽ�ջ
        }
    }
}

/*
    ����������������ǵݹ飩
*/
void InBiTree_Stack(BiTree *T){
    BiTree *a[10];
    BiTree *p=NULL;
    push(a,T); //���ڵ��ջ
    while(top!=-1){
        while((p=getTopElem(a)) && p){
            push(a,p->lchild);
        }
        pop();//�����ӵ���պ���NULL����
        if(top!=-1){
            p=getTopElem(a);
            displayElem(p);
            pop();
            push(a,p->rchild);//p�������ӱ����꣬��ʼ�����Һ���
        }
    }
}

/*
    ���������ջ����
*/
void postpush(SiNode *a,SiNode s){
    a[++top]=s;
}

/*
    ����������������ǵݹ飩
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
    ��α��� �������
*/
void EnQueue(BiTree **a,BiTree *t){
    a[rear++]=t;
}

/*
    ��α��� ���г���
*/
BiTree *DeQueue(BiTree **a){
    return a[front++];
}

/*
    ��α���
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
    �Ըý��Ĳ���
*/
void displayElem(BiTree *elem){
    cout<<elem->data<<" ";
}

/*
    ������� ����������
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
	if (ch[i] == '*'){//�������*��Ϊ��
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
    ������
*/
int main(){
    BiTree *BTree=CreateTree();
    cout<<"����������ݹ飩��  ";
    PreBiTree(BTree);
    cout<<endl<<"����������ݹ飩��  ";
    InBiTree(BTree);
    cout<<endl<<"����������ݹ飩��  ";
    PostBiTree(BTree);
    cout<<endl<<"����������ǵݹ飩��";
    PreBiTree_Stack(BTree);
    cout<<endl<<"����������ǵݹ飩��";
    InBiTree_Stack(BTree);
    cout<<endl<<"����������ǵݹ飩��";
    PostBiTree_Stack(BTree);
    cout<<endl<<"��α������ǵݹ飩��";
    LevelBiTree_Queue(BTree);
    cout<<endl<<"�����򣩴���һ��������(*��ʾ�ýڵ�Ϊ��)��";
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