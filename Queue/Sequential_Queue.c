/**** 2021.2.1 ****/
#include <stdio.h>

/**** �� �� �� ˳ �� �� �� �� �� ****/
#define MAX 8  //ʵ�ʴ洢7����Ч����

/**** �� �� �� �� ****/
int inQueue(int *a,int front,int rear,int elem);     //���
int outQueue(int *a,int front,int rear);  //����

/*
    ������ӣ�˳����У���ͷ��������β���������Ԫ�أ�
*/
int inQueue(int *a,int front,int rear,int elem){
    //���rear����MAX����ֱ�ӽ����a[0]���¿�ʼ�洢�����rear+1��front�غϣ����ʾ��������
    if ((rear+1)%MAX == front) {
        printf("�ռ�����\n");
        return rear;
    }
    printf("���%2d\n",elem);
    a[rear%MAX]=elem;
    rear++;
    return rear;
}

/*
    ���г��ӣ�˳����У�������������β������
*/
int outQueue(int *a,int front,int rear){
    //���front == rear����ʾ����Ϊ��
    if(front == rear%MAX) {
        printf("����Ϊ��\n");
        return front;
    }
    printf("%-2d����\n",a[front]);
    //front����ֱ�� +1������+1��ͬMAX���бȽϣ����=MAX����ֱ����ת�� a[0]
    front=(front+1)%MAX;
    return front;
}

/*
    ������
*/
int main(){
    int a[MAX];
    int front,rear;
    //��ʼ��˳����У���front,rear ָ��ͬһ��a[0]
    front = rear = 0;
    //���  1 2 3 4 5 6 7 
    for(int i=1;i<8;i++){
        rear = inQueue(a,front,rear,i);
    }
    // 1 ����
    front = outQueue(a,front,rear);
    // 8 ���
    rear = inQueue(a,front,rear,8);
    // 2 ����
    front = outQueue(a,front,rear);
    // 3 4 5 6 7 8 ����
    for(int j=0;j<6;j++){
        front = outQueue(a,front,rear);
    }
    // ���ն���
    front = outQueue(a,front,rear);
    // 9 ���
    rear = inQueue(a,front,rear,9);
    //�����ʱ�������
    int count = rear != 8 ? rear%MAX - front : 8 ;
    printf("�����ִ棺%-2d��Ԫ��\n",count);
    return 0;
}