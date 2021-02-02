/**** 2021.1.31 ****/
#include <iostream>
#include <malloc.h>
using namespace std;

/**** �� �� �� �� �� ****/
typedef struct scStack{
    struct scStack *next;
    int elem;
}scStack;

/**** �� �� �� �� ****/
scStack *sysConvert(int num,int system,scStack *sys); //����ת��������numΪ10��������systemΪת��Ŀ����ƣ�sysΪջ�ռ�
scStack *push(scStack *stack,int elem);               //��ջ
void pop(scStack *stack);                             //��ջ

/*
    ����ת��
*/
scStack *sysConvert(int num,int system,scStack *sys){
    int q = num / system;//��
    int r = num % system;//��
    scStack *syS = push(sys,r); 
    while(q!=0){
        r = q % system;
        q = q / system;
        syS = push(syS,r);
    }
    return syS;
}

/*
    ������ջ
*/
scStack *push(scStack *stack,int elem){
    scStack *newStack = (scStack *)malloc(sizeof(scStack));
    newStack->elem = elem;
    newStack->next = stack;
    stack = newStack;
    return stack;
}

/*
   ������ջ
*/
void pop(scStack *stack){
    while(stack){
        scStack *top = stack;
        if(top->elem >= 10){
            printf("%c",top->elem + 'a' - 10); ////10->a  11->b  12->c  13->d  14->e  15->f
            stack = stack->next;
            free(top);
            continue;
        }
        cout<<top->elem;
        stack = stack->next;
        free(top);
    }
    cout<<endl<<"ת����ϣ�"<<endl;
}

/*
    ������
*/
int main(){
    scStack *stack = NULL; //��ʼ��ջ
    int num,system;
    cout<<"������һ��10��������";
    cin>>num;
    cout<<"��������Ҫת��Ϊ���ٽ��ƣ�";
    cin>>system;
    stack = sysConvert(num,system,stack);
    pop(stack);
    return 0;
}