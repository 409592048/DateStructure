/**** 2021.02.02 ****/
#include <stdio.h>
#include <malloc.h>

/**** 全 局 变 量 ****/
int outCount = 0;   //已经出队多少elem
int inCount = 0;    //已经入队多少elem

/**** 链 队 列 节 点 结 构 ****/
typedef struct Queue{
    int date;
    struct Queue *next;
}QNODE;

/**** 函 数 声 明 ****/
QNODE *initQueue();                    //创建一个链队列
QNODE *inQueue(QNODE *rear,int date);  //入队
QNODE *outQueue(QNODE *top,QNODE *rear); //出队

/*
    创建一个链队列
*/
QNODE *initQueue(){
    QNODE *queue = (QNODE *)malloc(sizeof(QNODE));
    queue->next = NULL;
    return queue;
}

/*
    链队列->入队
*/
QNODE *inQueue(QNODE *rear,int date){
    //a.封装数据于一个节点中
    QNODE *inElem = (QNODE *)malloc(sizeof(QNODE));
    inElem->date = date;
    inElem->next = NULL;
    //b.把这个新节点于rear节点建立逻辑关系
    rear->next = inElem;
    rear = inElem;
    //c.返回新队尾，inCount++
    inCount++;
    printf("入队%2d\n",inElem->date);
    return rear;
}

/*
    链队列->出队
*/
QNODE *outQueue(QNODE *top,QNODE *rear){
    if(top->next == NULL){
        printf("队列目前为空\n");
        return rear;
    }
    QNODE *outElem = top->next;
    printf("%-2d出队\n",outElem->date);
    top->next = outElem->next;
    //这里判断一下如果这个是队尾，那么rear与top为初始状态
    if(rear == outElem){
        rear = top;
    }
    //释放已出队节点，节省空间
    free(outElem);
    outCount++;
    return rear;
}

/*
    主函数
*/
int main(){
    QNODE *top=NULL,*rear=NULL;
    int i;
    top=rear=initQueue();
    //入队 1 2 3 4 5
    for(i=1;i<6;i++){
        rear = inQueue(rear,i);
    }
    // 1 出队
    rear = outQueue(top,rear);
    // 2 出队
    rear = outQueue(top,rear);
    //队列目前状况
    printf("队列目前有数据：%-2d个\n",inCount - outCount);
    //3 4 5 出队
    for(i=3;i<6;i++){
        rear = outQueue(top,rear);
    }
    //队列目前状况
    printf("队列目前有数据：%-2d个\n",inCount - outCount);
    // 6 入队
    rear = inQueue(rear,6);
    // 7 入队
    rear = inQueue(rear,7);
    //队列目前状况
    printf("队列目前有数据：%-2d个\n",inCount - outCount);
    return 0;
}