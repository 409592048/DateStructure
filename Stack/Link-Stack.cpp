/******* 2021.1.27 *******/
#include <iostream>
#include <malloc.h>
using namespace std;
/******* �� �� �� �� �� �� �� �� *******/
typedef struct lineStack{
    int date;
    struct lineStack *next;
}lineStack;
/******* �� �� �� �� *******/
lineStack *push(lineStack *stack,int elem); //stackΪ��ջ��elemΪ��ջԪ��
lineStack *pop(lineStack *stack);           //ջ��Ԫ�س�ջ

/*
    ��ջ-��ջ��elemΪ��ջԪ��
*/
lineStack *push(lineStack *stack,int elem){
    //����������Ԫ�صĽڵ�
    lineStack *newLine = (lineStack *)malloc(sizeof(lineStack));
    newLine->date = elem;
    //�½ڵ���ͷ�ڵ㽨���߼���ϵ
    newLine->next = stack;
    //����ͷָ��
    stack = newLine;
    //������ջ��
    return stack;
}

/*
    ��ջ-��ջ��stackΪջ��
*/
lineStack *pop(lineStack *stack){
    //���һ��ʼ��Ϊ��ջ��û��Ԫ��
    if(stack){
        //����һ����ָ��ָ��ջ��
        lineStack *top = stack;
        //����ͷָ��
        stack = stack->next;
        cout<<"��ջԪ��Ϊ��"<<top->date<<"  ";
        //��ʱ�ж��Ƿ�Ϊ��ջ������������ջ��Ϊ
        if(stack){
            cout<<"��ջ��Ԫ��Ϊ��"<<stack->date<<endl;
        }else{
            cout<<"ջ�ѿգ�"<<endl;
        }
        //�ͷų�ջԪ�ؽڵ�
        free(top);
    }else{
        cout<<"ջ��û��Ԫ��"<<endl;
    }
    return stack; //������ջ��
}

/*
    ������
*/
int main(){
    lineStack *stack = NULL;
    for(int i=1;i<5;i++){  //��ջ 1 2 3 4 
        stack = push(stack,i);
    }
    for(int j=1;j<6;j++){
        stack = pop(stack);  //��ջ 1 2 3 4 NULL
    }
    return 0;
}