/******** 2021.1.27 ********/
#include <iostream>
using namespace std;
/******** �� �� �� �� ********/
int push(int *a,int top,int elem); //Ԫ��elem��ջ
int pop(int *a,int top);           //����Ԫ�س�ջ

/*
    Ԫ��elem��ջ��aΪ���飬topֵΪ��ǰջ��ջ��λ��
*/
int push(int *a,int top,int elem){
    a[++top]=elem;
    return top;
}

/*
    ����Ԫ�س�ջ
*/
int pop(int *a,int top){
    if(top == -1){
        cout<<"��ջ"<<endl;
        return -1;
    }
    cout<<"��ջԪ�أ�"<<a[top]<<endl;
    top--;       //ÿ��ջһ��Ԫ��ջ��-1
    return top;  //��������ջ��
}

/*
    ������
*/
int main(){
    int a[20];
    int top = -1;
    for(int i=1;i<5;i++){  //��ջ 1 2 3 4 
        top = push(a,top,i);
    }
    for(int j=1;j<6;j++){
        top = pop(a,top);  //��ջ 1 2 3 4 NULL
    }
    return 0;
}