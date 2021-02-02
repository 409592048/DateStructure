/**** 2021.1.31 ****/
#include <iostream>
#include <malloc.h>
using namespace std;

/**** 结 构 体 声 明 ****/
typedef struct scStack{
    struct scStack *next;
    int elem;
}scStack;

/**** 函 数 声 明 ****/
scStack *sysConvert(int num,int system,scStack *sys); //进制转换函数，num为10进制数，system为转换目标进制，sys为栈空间
scStack *push(scStack *stack,int elem);               //入栈
void pop(scStack *stack);                             //出栈

/*
    进制转换
*/
scStack *sysConvert(int num,int system,scStack *sys){
    int q = num / system;//商
    int r = num % system;//余
    scStack *syS = push(sys,r); 
    while(q!=0){
        r = q % system;
        q = q / system;
        syS = push(syS,r);
    }
    return syS;
}

/*
    余数入栈
*/
scStack *push(scStack *stack,int elem){
    scStack *newStack = (scStack *)malloc(sizeof(scStack));
    newStack->elem = elem;
    newStack->next = stack;
    stack = newStack;
    return stack;
}

/*
   余数出栈
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
    cout<<endl<<"转换完毕！"<<endl;
}

/*
    主函数
*/
int main(){
    scStack *stack = NULL; //初始化栈
    int num,system;
    cout<<"请输入一个10进制数：";
    cin>>num;
    cout<<"请输入想要转换为多少进制：";
    cin>>system;
    stack = sysConvert(num,system,stack);
    pop(stack);
    return 0;
}