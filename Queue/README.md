# Queue

队列与栈结构不同的是，队列两头都是“开口”，数据只能从一段进入然后从另一端出去，中间不可存在“插队”一说。如图所示：

![image-20210201212004082](https://i.loli.net/2021/02/01/uydQEfS6zO9c724.png)

我们通常把进队列的一段叫做“队尾”，把出队列的一段叫做“队头”，把进数据叫做”入队“，把出数据叫做”出队“，与栈结构不同的是，队列遵循“先进先出”的原则，这好比我们排队买票也是遵循”先进先出“的原则来的。例如图一中1入队后想要出队，则需先让3出队，然后2出队，方可1出队。

队列的存储结构的实现可以有两种方式：

1.顺序队列：在顺序表的基础上的队列实现；

2.链式队列：在链表的基础上的队列实现；

两种实现方式的区别在于顺序表与链表，存储物理结果上，顺序表是数据集中顺序结构，链表则是分散存储数据。在生活上面有很多地方都用到队列结构，排队买票，停车场停车登记等，扑克牌游戏的开发也可以用到。

## 顺序队列

顺序队列是在数组的基础上完成的，因此需要数组、头指针、尾指针，当队列处于空时，头指针与尾指针则指向同一个索引下的数据。如图：

![image-20210201213656033](https://i.loli.net/2021/02/01/C9wZfj7lmXWbiQ5.png)

更具队列的结构特点，“先进先出”的原则，我们要让一个元素入队，那么rear++，当需要队头元素出队时，只需要top++即可。在此基础上我们先让 `{1,2,3,4}` 入队

![image-20210201214058432](C:\Users\HP\AppData\Roaming\Typora\typora-user-images\image-20210201214058432.png)

元素1出队，如图：

![image-20210201214255534](https://i.loli.net/2021/02/01/jg8AmEdnl34FW9y.png)

当所有元素都出队完之后，头指针与尾指针又重新指向同一个索引了，如图：

![image-20210201214402719](https://i.loli.net/2021/02/01/qlxpAtfLJz3ICMT.png)

那么一个队列的入队和出队就简单模拟完成了，这个时候就存在了一个问题，虽然top与rear重新重合了，但是他们指向的是a[4]而不再是a[0]了，前面的空间就以及浪费掉了，顺序队列必定是有限的，那么如果继续入队，有可能造成队列的溢出，程序崩溃，所以我们改良一下顺序队列让他成为一个环，那么当队列入队出队之后top与rear还能指向最初的位置（又回到最初的起点0.0,记忆中你....）

![image-20210201220001970](https://i.loli.net/2021/02/01/C8cHIamYSZoUPVD.png)

与前面顺序队列无异，入队`{1,2,3,4,5,6,7}`出队如图所示：

![](https://i.loli.net/2021/02/01/D7qrgdEwHUkf4RZ.png)

![image-20210201220325884](https://i.loli.net/2021/02/01/6UicfZhTpSmDEb4.png)

完善之后的代码如下：（测试代码详见 **[Sequential_Queue.c](https://github.com/409592048/DateStructure/blob/master/Queue/Sequential_Queue.c)**）

```c
/*
    队列入队（顺序队列，队头索引，队尾索引，入队元素）
*/
int inQueue(int *a,int front,int rear,int elem){
    //如果rear+1和front重合，则表示数组已满
    if ((rear+1)%MAX == front) {
        printf("空间已满\n");
        return rear;
    }
    printf("入队%2d\n",elem);
    //rear余MAX表示存储的数据一直都在MAX“环”中
    a[rear%MAX]=elem;
    rear++;
    return rear;
}

/*
    队列出队（顺序队列，出队索引，队尾索引）
*/
int outQueue(int *a,int front,int rear){
    //如果front==rear，表示队列为空
    if(front == rear%MAX) {
        printf("队列为空\n");
        return front;
    }
    printf("%-2d出队\n",a[front]);
    //front+1之后余MAX得到是在MAX这个“环”中的值
    front=(front+1)%MAX;
    return front;
}
```

测试如图：

![image-20210201230451345](https://i.loli.net/2021/02/01/lhepdXPRFD5q8vj.png)

## 链式队列

链队列即使使用链表实现的队列存储结构，其特点“先进先出”，它与顺序队列的思路类似，创建top与rear指针分别指向队头和队尾，如图：

![image-20210202111139615](https://i.loli.net/2021/02/02/Ro7zwVui2l5CtkW.png)

### 链队列->入队

队列入队形如链表添加新节点，分为三步骤：

a. 封装数据    b. 连接新节点    c. rear移向新节点

![image-20210202114211370](https://i.loli.net/2021/02/02/7XO1Q53ZmVvhfrS.png)

代码如下：

```c
/*
    链队列->入队
*/
QNODE *inQueue(QNODE *rear,int date){
    //a.封装数据于一个节点中
    QNODE *inElem = (QNODE *)malloc(sizefo(QNODE));
    inElem->date = date;
    inElem->next = NULL;
    //b.把这个新节点于rear节点建立逻辑关系
    rear->next = inElem;
    rear = inElem;
    //c.返回新队尾，inCount++
    inCount++;
    return rear;
}
```

### 链队列->出队

出队遵循“先进先出”原则，所以出队节点永远都是head的下一个节点，它也可以分为三步骤：

a. 创建outElem指针指向top的下一个节点，也就是要出队的节点；

b. top的下一个节点与outElem的下一个节点建立逻辑关系；

c. 释放outElem所指向的节点，节约空间；

![image-20210202121004647](https://i.loli.net/2021/02/02/NWS8Qwoegi35cUH.png)

特殊情况：如果出队节点为队尾，则rear重新指回head

![image-20210202121652060](https://i.loli.net/2021/02/02/xo2YV4Xnlic9DSW.png)

代码如下：

```c
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
```

测试如下：（测试代码详见 **[Chain_Queue.c](https://github.com/409592048/DateStructure/blob/master/Queue/Chain_Queue.c)**）

![image-20210202123543000](https://i.loli.net/2021/02/02/rwiXmu47qAbOl8x.png)

## 总结

无论是顺序队列还是链队列，都遵循“先进先出”的原则，只不过链队列比顺序队列的优势在于空间利用率高，灵活性强（顺序队列不可因用户需求增大空间），在于不知道用户需要多大的队列空间时，当然选择链队列，在知道用户需要多大的队列空间时，我们选择顺序队列，例如停车场的容量等等。