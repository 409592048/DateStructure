# Stack

## 一、顺序栈及基本操作

用顺序表实现栈存储结构。栈的储存结构操作必须遵循”先进后出的“的原则。

若用顺序表即数组a来存储数据。

![image-20210127150841505](https://i.loli.net/2021/01/27/DqZS1QdnWEIVByC.png)

即可用a[0],a[1],a[2],a[3]来分别取出数据，那么我们用一个整型top,来表示索引（初始值为-1即空栈），每次增加一个数据top++；每次减少一个数据top--；可以模拟出栈的储存结构”先进后出“的原则。

![image-20210127150743080](https://i.loli.net/2021/01/27/j6SJ5vXlzHAKGN8.png)

### 1.顺序栈-入栈

1）模拟空栈的情况，即数组为空，top = -1。

![image-20210127151251625](https://i.loli.net/2021/01/27/zBXk42xbDH9qog7.png)

2）首先添加一个元素1，即入栈元素1，top++。

![image-20210127151400120](https://i.loli.net/2021/01/27/yKvXVcogirGmh3O.png)

3）延续2）方法入栈2，3，4。

![image-20210127151520901](https://i.loli.net/2021/01/27/wj9pRbPYVzho4IN.png)

代码如下：

```c++
/*
    元素elem进栈，a为数组，top值为当前栈的栈顶位置
*/
int push(int *a,int top,int elem){
    a[++top]=elem;
    return top;
}
```

### 2.顺序栈-出栈

例如，我们需要将元素2出栈，即需要先将4元素出栈，再将3元素出栈，随后才能使2元素出栈，在顺序表模拟的栈出栈，元素并没有摘掉，为了方便理解，先将元素摘掉。

![image-20210127151800847](https://i.loli.net/2021/01/27/AmMk4tuXVBLZUQv.png)

![image-20210127151823467](https://i.loli.net/2021/01/27/zIGWqTOQEcewCRM.png)

代码如下：

```c++
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
```

### 3.顺序栈-总结

顺序栈只是模拟栈的出栈入栈过程，即”先进后出“，

并不能很好的体现栈的储存结构。

实现结果：![image-20210127160701203](https://i.loli.net/2021/01/27/GZ2XvIPfA7pHcbk.png)



## 二、链栈及基本操作

链栈与顺序栈类似，顺序栈是以数组的头为 栈底，另一头为栈顶；

链栈则是以单向链的头为栈顶，链尾为栈底，实现栈的储存结构，如图；

![image-20210127153122380](https://i.loli.net/2021/01/27/GboRXpVhtWxvUB5.png)

1）将链表头部作为栈顶的一端，可以避免在实现数据”入栈“和”出栈“操作时做大量的遍历链表；

2）在实现数据”入栈“操作时，需要将数据从链表的头部插入；

3）在实现数据”出栈“操作时，需要删除链表头部的首元节点；

<u>**因此，链栈实际上就是一个只能采用头插法插入或删除数据的链表。**</u>

### 1.链栈-入栈

例如，将元素1、2、3、4依次入栈，即是用头插法将各个元素依次插入添加到链表中，过程如下；

a)空栈：       head  **→**  **NULL**

b)1入栈：     head  **→**  **1**  **→**  NULL

c)2入栈：      head  **→**  **2**  **→**  1  **→**  NULL

d)3入栈：      head  **→**  **3**  **→**  2  **→**  1  **→**  NULL

e)4入栈：      head  **→**  **4**  **→**  3  **→**  2  **→**  1  **→**  NULL

代码如下：

```c++
/******* 创 建 链 表 节 点 结 构 *******/
typedef struct lineStack{
    int date;
    struct lineStack *next;
}lineStack;
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
```

### 2.链栈-出栈

例如，我们需要将元素2出栈，那么根据”先进后出“的原则，我们则需要先将元素4出栈，再将元素3出栈，随后才能时元素2出栈，整个操作如下；

a)初始链栈：      head  **→**  4  **→**  3  **→**  2  **→**  1  **→**  NULL

b)4出栈：           head  **→**  3  **→**  2  **→**  1  **→**  NULL                 **4出**

c)3出栈：            head  **→**  2  **→**  1  **→**  NULL                           **3出**

d)2出栈：            head  **→**  1  **→**  NULL                                     **2出**

代码如下：

```c++
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
        cout<<"出栈元素为："<<top->date<<endl;
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
```

### 3.链栈-总结

链栈即采用了单向链表的头插法实现，严格遵循”先进后出“的原则。

实现结果：![image-20210127160614437](https://i.loli.net/2021/01/27/9Tv4SD65PNrWnyZ.png)

## 三、栈-10进制任意转换

### 设计思路

例如讲10进制转换为2进制计算思路为：

![image-20210131141702802](https://i.loli.net/2021/01/31/CFM4QvapeXmg6Rl.png)

利用循环将每一个余数都压入栈中，再遍历出栈

转换代码：

```c++
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
    return syS;   //返回栈顶
}
```

如果10进制转换成16进制则10->a \ 11->b \ 12->c \ 13->d \ 14->e \ 15->f

则在出栈的时候判断一下是否为大于等于10的数

```c++
/*
   余数出栈
*/
void pop(scStack *stack){
    while(stack){
        scStack *top = stack;
        if(top->elem >= 10){
            printf("%c",top->elem + 'a' - 10);//10->a  11->b  12->c  13->d  14->e  15->f
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
```

### 运行结果

10->2

![image-20210131142205331](https://i.loli.net/2021/01/31/q4IQMOoWbx21DVc.png)

10->16

![image-20210131142247262](https://i.loli.net/2021/01/31/Ga46clpPETzteOw.png)