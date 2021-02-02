/**** 2021.2.1 ****/
#include <stdio.h>

/**** 宏 定 义 顺 序 队 列 长 度 ****/
#define MAX 8  //实际存储7个有效数据

/**** 函 数 声 明 ****/
int inQueue(int *a,int front,int rear,int elem);     //入队
int outQueue(int *a,int front,int rear);  //出队

/*
    队列入队（顺序队列，队头索引，队尾索引，入队元素）
*/
int inQueue(int *a,int front,int rear,int elem){
    //如果rear超过MAX，则直接将其从a[0]重新开始存储，如果rear+1和front重合，则表示数组已满
    if ((rear+1)%MAX == front) {
        printf("空间已满\n");
        return rear;
    }
    printf("入队%2d\n",elem);
    a[rear%MAX]=elem;
    rear++;
    return rear;
}

/*
    队列出队（顺序队列，出队索引，队尾索引）
*/
int outQueue(int *a,int front,int rear){
    //如果front == rear，表示队列为空
    if(front == rear%MAX) {
        printf("队列为空\n");
        return front;
    }
    printf("%-2d出队\n",a[front]);
    //front不再直接 +1，而是+1后同MAX进行比较，如果=MAX，则直接跳转到 a[0]
    front=(front+1)%MAX;
    return front;
}

/*
    主函数
*/
int main(){
    int a[MAX];
    int front,rear;
    //初始化顺序队列，即front,rear 指向同一个a[0]
    front = rear = 0;
    //入队  1 2 3 4 5 6 7 
    for(int i=1;i<8;i++){
        rear = inQueue(a,front,rear,i);
    }
    // 1 出队
    front = outQueue(a,front,rear);
    // 8 入队
    rear = inQueue(a,front,rear,8);
    // 2 出队
    front = outQueue(a,front,rear);
    // 3 4 5 6 7 8 出队
    for(int j=0;j<6;j++){
        front = outQueue(a,front,rear);
    }
    // 出空队列
    front = outQueue(a,front,rear);
    // 9 入队
    rear = inQueue(a,front,rear,9);
    //输出此时队列情况
    int count = rear != 8 ? rear%MAX - front : 8 ;
    printf("队列现存：%-2d个元素\n",count);
    return 0;
}