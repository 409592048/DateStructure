/******** 2021.1.27 ********/
#include <iostream>
using namespace std;
/******** 声 明 函 数 ********/
int push(int *a,int top,int elem); //元素elem进栈
int pop(int *a,int top);           //数据元素出栈

/*
    元素elem进栈，a为数组，top值为当前栈的栈顶位置
*/
int push(int *a,int top,int elem){
    a[++top]=elem;
    return top;
}

/*
    数据元素出栈
*/
int pop(int *a,int top){
    if(top == -1){
        cout<<"空栈"<<endl;
        return -1;
    }
    cout<<"出栈元素："<<a[top]<<endl;
    top--;       //每出栈一个元素栈顶-1
    return top;  //返回现在栈顶
}

/*
    主函数
*/
int main(){
    int a[20];
    int top = -1;
    for(int i=1;i<5;i++){  //进栈 1 2 3 4 
        top = push(a,top,i);
    }
    for(int j=1;j<6;j++){
        top = pop(a,top);  //出栈 1 2 3 4 NULL
    }
    return 0;
}