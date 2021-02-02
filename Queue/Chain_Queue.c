/**** 2021.02.02 ****/
#include <stdio.h>
#include <malloc.h>

/**** ȫ �� �� �� ****/
int outCount = 0;   //�Ѿ����Ӷ���elem
int inCount = 0;    //�Ѿ���Ӷ���elem

/**** �� �� �� �� �� �� �� ****/
typedef struct Queue{
    int date;
    struct Queue *next;
}QNODE;

/**** �� �� �� �� ****/
QNODE *initQueue();                    //����һ��������
QNODE *inQueue(QNODE *rear,int date);  //���
QNODE *outQueue(QNODE *top,QNODE *rear); //����

/*
    ����һ��������
*/
QNODE *initQueue(){
    QNODE *queue = (QNODE *)malloc(sizeof(QNODE));
    queue->next = NULL;
    return queue;
}

/*
    ������->���
*/
QNODE *inQueue(QNODE *rear,int date){
    //a.��װ������һ���ڵ���
    QNODE *inElem = (QNODE *)malloc(sizeof(QNODE));
    inElem->date = date;
    inElem->next = NULL;
    //b.������½ڵ���rear�ڵ㽨���߼���ϵ
    rear->next = inElem;
    rear = inElem;
    //c.�����¶�β��inCount++
    inCount++;
    printf("���%2d\n",inElem->date);
    return rear;
}

/*
    ������->����
*/
QNODE *outQueue(QNODE *top,QNODE *rear){
    if(top->next == NULL){
        printf("����ĿǰΪ��\n");
        return rear;
    }
    QNODE *outElem = top->next;
    printf("%-2d����\n",outElem->date);
    top->next = outElem->next;
    //�����ж�һ���������Ƕ�β����ôrear��topΪ��ʼ״̬
    if(rear == outElem){
        rear = top;
    }
    //�ͷ��ѳ��ӽڵ㣬��ʡ�ռ�
    free(outElem);
    outCount++;
    return rear;
}

/*
    ������
*/
int main(){
    QNODE *top=NULL,*rear=NULL;
    int i;
    top=rear=initQueue();
    //��� 1 2 3 4 5
    for(i=1;i<6;i++){
        rear = inQueue(rear,i);
    }
    // 1 ����
    rear = outQueue(top,rear);
    // 2 ����
    rear = outQueue(top,rear);
    //����Ŀǰ״��
    printf("����Ŀǰ�����ݣ�%-2d��\n",inCount - outCount);
    //3 4 5 ����
    for(i=3;i<6;i++){
        rear = outQueue(top,rear);
    }
    //����Ŀǰ״��
    printf("����Ŀǰ�����ݣ�%-2d��\n",inCount - outCount);
    // 6 ���
    rear = inQueue(rear,6);
    // 7 ���
    rear = inQueue(rear,7);
    //����Ŀǰ״��
    printf("����Ŀǰ�����ݣ�%-2d��\n",inCount - outCount);
    return 0;
}