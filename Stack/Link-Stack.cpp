/******* 2021.1.27 *******/
#include <iostream>
#include <malloc.h>
using namespace std;
/******* 创 建 链 表 节 点 结 构 *******/
typedef struct lineStack{
    int date;
    struct lineStack *next;
}lineStack;
/******* 声 明 函 数 *******/
lineStack *push(lineStack *stack,int elem); //stack为链栈，elem为入栈元素
lineStack *pop(lineStack *stack);           //栈顶元素出栈

/*
    链栈-入栈，elem为入栈元素
*/
lineStack *push(lineStack *stack,int elem){
    //创建储存新元素的节点
    lineStack *newLine = (lineStack *)malloc(sizeof(lineStack));
    newLine->date = elem;
    //新节点与头节点建立逻辑关系
    newLine->next = stack;
    //更新头指针
    stack = newLine;
    //返回新栈顶
    return stack;
}

/*
    链栈-出栈，stack为栈顶
*/
lineStack *pop(lineStack *stack){
    //如果一开始就为空栈即没有元素
    if(stack){
        //声明一个新指针指向栈顶
        lineStack *top = stack;
        //更新头指针
        stack = stack->next;
        cout<<"出栈元素为："<<top->date<<"  ";
        //此时判断是否为空栈，若不是则新栈顶为
        if(stack){
            cout<<"新栈顶元素为："<<stack->date<<endl;
        }else{
            cout<<"栈已空！"<<endl;
        }
        //释放出栈元素节点
        free(top);
    }else{
        cout<<"栈内没有元素"<<endl;
    }
    return stack; //返回新栈顶
}

/*
    主函数
*/
int main(){
    lineStack *stack = NULL;
    for(int i=1;i<5;i++){  //进栈 1 2 3 4 
        stack = push(stack,i);
    }
    for(int j=1;j<6;j++){
        stack = pop(stack);  //出栈 1 2 3 4 NULL
    }
    return 0;
}