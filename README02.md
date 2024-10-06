### 一、常用数据结构类型
#### **Q1：什么是随机存取？这个性质属于哪种线性表的特征？**
1）随机存取允许某个程序直接访问储存在计算机内存中任意位置的数据，不需要遍历或搜索数据结构中除了目标数据以外的多余元素。

2）随机存取主要属于线性表结构中的顺序表（又被称作数组）的特征

#### **Q2：什么是指针？如何在C语言中定义指针变量？指针变量的大小是固定的吗？**
1）指针是存储内存地址的特殊的变量。它并不直接存储数据的值，而是存储某个目标对象在计算机内存中的地址，程序可以通过指针直接访问和修改存储在该内存地址中的数据。

2）要在Ｃ语言中定义一个指针变量，需要在最前面声明指针指向的数据类型，然后写出变量名并在前面加上星号。假设要定义不同类型的指针变量p，举例做以下声明：
```c
        int* p  //整数类型的指针p
       char* p  //字符类型的指针p
      float* p  //浮点类型的指针p
srtuct node* p  //结构体类型的指针p
```

3）在确定的系统环境下指针变量的大小是固定的，如64位系统上指针的大小为8字节
#### **Q3：你能为不同的数据结构设想出适用的具体情况吗？**
**1）线性表**
- **顺序表**通过连续的存储空间来存储数据元素，每个元素占据相同的存储空间，相邻的元素在内存中的物理位置上也相邻，支持随机存取
根据这个性质，顺序表可以用于创建统计人员个人信息的信息管理系统
- **链表**通过非连续的存储空间来存储数据元素，每个元素除了存储数据本身外，还包含指向下一个元素的指针。链表的节点更加动态，因此更改元素时灵活性更高，但不支持随机存取
根据这个性质，链表可以用于创建某仓库的货物管理系统

**2）栈**
栈是限定仅在一端进行插入和删除操作的特殊线性表（有“后进先出”的特点）
根据这个性质，栈可以用于记事本等文本软件

**3）队列**
队列是只允许在一端插入, 在另一端删除的特殊线性表（有“先进先出”的特点）
根据这个性质，队列可以用在日程表等软件上

**4）图**
图用于表示对象之间的关系或连接，通常由一组表示对象的**顶点**和表示对象之间的关系的**边**组成
根据这个性质，图可以用在有多个站点的火车、汽车等交通工具的运营管理系统上

#### **Q4：如何使用C语言保存一张图的信息？**
边较少的图称为稀疏图，边较多的图成为稠密图，可以根据边的多少选择保存一张图的最佳方法
&nbsp;
- 边较多的稠密图适合用**邻接矩阵**表示，这种方法借助二维数组来表示顶点之间的连接关系。对于一个有 V 个顶点的图，用一个 V 阶方阵表示图的边，如果两个顶点之间有边，则矩阵中的值为1，如果没有边，则对应值为0

使用邻接矩阵保存图的例子如下：
```c
#include <stdio.h>
#define V 5 
// 假设有一个5阶方阵
//使用宏定义来定义顶点数量便于后面修改

void printMatrix(int graph[V][V]) 
//定义一个用来打印矩阵的函数 printMatrix
//graph 是一个内含 V 个元素的数组，这里的每个元素也都是含 V 个 int 类型元素的数组，从而构成了一个二维数组
{
    int i,j;

    for (i = 0; i < V; i++) //利用 for 循环，外层循环打印不同行
    {
        for (j = 0; j < V; j++) //内层循环打印每一行中不同列的元素
        {
            printf("%d ", graph[i][j]);
        }
      printf("\n"); //打印完一行中的元素后换行
    }
}

int main() 
{
    int graph[V][V] = //输入想要表示的图的内容，拿以下方阵举例
      {
          {0, 1, 0, 1 , 0},
          {0, 1, 0, 1 , 0},
          {0, 1, 0, 1 , 0},
          {0, 1, 0, 1 , 0},
          {0, 1, 0, 1 , 0}
      };
    printMatrix(graph);
return 0;
}
```
&nbsp;
运行结果如下：
![](https://s3.bmp.ovh/imgs/2024/10/02/e95e8b248d4a524b.png)
&nbsp;
- 边较少的稀疏图适合用**邻接表**来表示，这种方法通过一个数组表示图的顶点，数组中的元素是一个链表，链表中的节点为与该顶点连接的其他顶点，有表示边的意义

使用邻接表保存图的例子如下：
```c
#include <stdio.h>
#include <stdlib.h>             //引入 stdlib 头文件来使用 malloc 函数为链表的创建动态地分派内存

typedef struct EdgeNode         //创建边节点的结构体，并用 typedef 简化名称，方便输入使用
{
    int adjvertex;              //创建与边节点存储的所连接的顶点的编号
    struct EdgeNode* next;      //创建指向下一个边节点的指针
}EdgeNode;

                                
typedef struct VertexNode       //创建顶点节点的结构体，同样简化名称
{
    int HeadVertex;             //创建顶点的编号
    EdgeNode* firstone;            //创建从顶点节点指向第一个边节点的指针
}VertexNode;

typedef struct AdjList          //创建邻接表的总框架，同样简化名称
{
    VertexNode vertex[5];       //创建顶点节点数组，假设最多可以保存5个顶点
    int vertexnum, edgenum;     //创建顶点数和边数的变量
}AdjList;


void CreatAdjlist(AdjList* graph, int vertexnum, int edgenum)    //建立一个创建邻接表的函数并对邻接表进行初始化操作
{
    graph->vertexnum = vertexnum;          //为新建的邻接表获取顶点的数目
    graph->edgenum = edgenum;              //为新建的邻接表获取边的数目
    for (int i = 0; i < vertexnum; i++)    //通过 for 循环初始化每个顶点节点
    {
        graph->vertex[i].HeadVertex = i;   //vertex 是顶点结构体 struct VertexNode 类型的数组，通过循环为n个顶点编从 0 到 n-1 的号
        graph->vertex[i].firstone = NULL;     //使顶点节点的指针初始化指向为空，如果有边则可以从空添加
    }
}

void CreatEdge(AdjList* graph, int begin, int dest)    //建立一个创建边节点的函数，获取边节点及其指向的节点
{
    EdgeNode* newNode = (EdgeNode*)malloc(sizeof(EdgeNode));   //创建边节点结构体 newnode
    newNode->adjvertex = dest;                         //获取指向 newnode 的顶点的编号
    newNode->next = graph->vertex[begin].firstone;        //如果对应的节点已经有指向的边，将新建的边节点的指针指向原有的第一个边节点
    graph->vertex[begin].firstone = newNode;              //使新建的边成为对应顶点指向的第一个边节点
}

void PrintAdjList(AdjList* graph)           //创建打印邻接表的函数
{
    for (int i = 0; i < graph->vertexnum; i++) //通过遍历顶点节点及其指向的边节点
    {
        printf("Vertex %d: ", graph->vertex[i].HeadVertex);
        EdgeNode* edge = graph->vertex[i].firstone;
        while (edge)    //使用 while 循环，不断打印出 edge 及其指向的下一个边节点中的内容，直到 edge 为空指针
        {
            printf("-> %d ", edge->adjvertex);
            edge = edge->next;
        }
        printf("\n");
    }
}

int main() 
{
    AdjList graph;                 //创建邻接表 AdjList 类型的结构体 graph
    CreatAdjlist(&graph, 5, 5);    //创建5个顶点和5条边

    CreatEdge(&graph, 0, 1);       //添加节点关系，拿以下内容举例
    CreatEdge(&graph, 1, 2);
    CreatEdge(&graph, 2, 3);
    CreatEdge(&graph, 3, 4);
    CreatEdge(&graph, 0, 2);

    PrintAdjList(&graph);

return 0;
}
```
&nbsp;
运行结果如下：
![](https://s3.bmp.ovh/imgs/2024/10/02/5bf0c3bb6f483839.png)
&nbsp;
&nbsp;
### 二、数据结构的应用
#### **Part 1.圈圈圆圆圈圈**
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node    //定义链表节点的结构体，包含存储的数据和下一个节点的指针两部分
{
    int data;
    struct Node* next;
}NODE;

NODE* CreateNode(int data)   //创建用于新建节点的函数，为新的节点动态分配内存，获取输入和数据并初始化指针为空
{
    NODE* newnode;
    newnode = malloc(sizeof(NODE));
    newnode -> data = data;
    newnode -> next = NULL;
return newnode;
}

NODE* Hcreate(NODE* head, int data)   //创建进行H操作的函数
{
    NODE* newnode;
    newnode = CreateNode(data);       //获取新节点存储的数据
    newnode -> next = head;           //H操作创建出的节点指向原来链表的头节点
return newnode;                       //创建的新节点作为头结点，返回新的头结点
}

NODE* Tcreate(NODE* head, int data)   //创建进行T操作的函数
{
    NODE* newnode = CreateNode(data);
    NODE* helper = head;              //引入一个结构体指针来辅助操作
    while (helper -> next != NULL)    //利用循环到找到链表的末尾
    {
        helper = helper->next;
    }
    helper -> next = newnode;         //将新节点插入到原链表最后一个节点的后面
return head;                          //返回创建完毕后的新链表的头节点
}

NODE* Delete(NODE* head, int num)     //创建进行D操作的函数
{
    NODE* helper = head;

    if (num == 1)                     //当要删除的是当前的头节点的情况
    {
        head = head -> next;
        free(helper);
return head;
    }

    for(int i = 2; i < num; i++)      //如果要删除的节点非头节点，根据输入的数字执行一定次数的操作，通过 i 控制循环的次数，定位到被删除节点的前一个节点
    {
        helper = helper -> next;
    }

    NODE* bedeleted = helper -> next;         //定位到被删除节点
    helper -> next = helper -> next -> next;  //连接被删除节点的前一个与后一个节点
    free(bedeleted);                          //释放被删除的节点
return head;
}

NODE* Circle(NODE* head)             //创建C操作的函数
{
    NODE* helper = head;
    while (helper -> next != NULL)   //通过循环定位到最后一个节点
    {
        helper = helper->next;
    }
    helper->next = head;             //使尾节点的指针指向头节点
return head;
}

void printList(NODE* head)           //创建打印链表内容的函数
{
    NODE* helper = head;
    while (helper != NULL)           //通过循环遍历打印链表的节点存储的数据
    {
        printf("%d -> ", helper->data);
        helper = helper->next;
    }
    printf("NULL\n");                //最后一个节点后打印NULL
}


int stack[10];        //为了实现H操作的要求，借用栈的结构来实现先对后读取的数据进行插入链表的操作
int top = -1;         //定义数组的下标序号
void push(int num)    //构建一个入栈的函数
{
    top++;
    stack[top] = num;
}

int pop()             //构造一个出栈的函数
{
    int num = stack[top];  
    top--; 
return num;
}


int main() 
{
    NODE* head = CreateNode(1);                  //初始化链表的头节点，存储数据为1
    FILE* file = fopen("CS-EASY-02-1.txt", "r"); //利用fopen函数读取题目文档的内容
    char input[10];                              //建立一个用于存储读取到的文档中每行内容的字符串数组

    while (fgets(input, 10, file) != NULL)       //不断使用 fgets 函数读取文档中的一行，将内容存储到数组中
    {      
        int i = 0;

        while (input[i] != '\0')                 //使用 while 读取数组中的内容
        {
            char operation;
            operation = input[i];                //将读取的第一个字母存储到新变量中作为操作代号

            if (input[i] == 'C')                 //如果读取到C，进行C函数的操作
            {
                head = Circle(head);             // 将链表变为环形链表
                printf("Created circle list");
            return 0;                            //如果创建了环形链表，结束程序防止打印无限循环
            }

            if (input[i] == 'T' || input[i] == 'D')       //为简化代码，把T操作与D操作在一起表示      
            {                
                while (input[i] != '\0')         //如果读取到了操作字母，开始遍历字母后的数字
                {
                    if (input[i] >= '0' && input[i] <= '9')  //如果读取到了字符串中存储的的数字
                    {                       
                        int num = 0;                                              
                        while (input[i] >= '0' && input[i] <= '9') //在D操作中有对于两位数的操作，使用 while 循环读取两位数
                        {
                            num = num * 10 + (input[i] - '0');     //将字符串内的数字转换为正常类型的数字，如果遇到两位数，将十位数字乘10并加上个位数                      
                            i++;
                        }

                        if (operation == 'T')              //读取到T，进行T函数的操作
                        {
                            head = Tcreate(head, num);     
                        } 

                        if (operation == 'D')              //读取到D，进行D函数的操作
                        {
                            head = Delete(head, num); 
                        }                                       
                    }       
                i++;               
                }                           
            }

            if (operation == 'H')                    //如果读取到H操作的情况
            {
                while (input[i] != '\0')             //使用 while 循环读取每一个数字 
                {
                    if (input[i] >= '0' && input[i] <= '9')   
                    { 
                        int num = 0;
                        while (input[i] >= '0' && input[i] <= '9')
                        { 
                            num = input[i] - '0';
                            i++;
                        }
                        push(num);     //将读取到的数字存入栈中
                    } 
                    else 
                    {
                        i++;          //如果读取到的非数字，找到下一个字符
                    }
                }
              
                while (top != -1)      //利用栈内数字输出到H操作的函数中
                {        
                    head = Hcreate(head, pop());
                }
            }
        i++;
        }
    printList(head);      //每一次用 while 循环完成对一行命令的读取，打印链表的内容
    }
    fclose(file);         //读取完后关闭文件
return 0;
}
```

程序的运行结果如图：
![](https://s3.bmp.ovh/imgs/2024/10/04/eaca1329666429df.png)

由此得到的结果为：
```
1 -> 1 -> 1 -> 1 -> 2 -> 1 -> 2 -> 2 -> 1 -> 1 -> 2 -> 1 -> 2 -> 1 -> 3 -> 2 -> 1 -> 1 -> 1 -> 1 -> 1 -> 1 -> 1 -> 2 -> 2 -> 2 -> 1 -> 2 -> 2 -> 1 -> 1 -> 2 -> 2 -> 2 -> NULL
```
&nbsp;
#### **Part 2.我和约瑟夫有个约会**
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
}NODE;

NODE* CreateNode(int data)
{
    NODE* newnode;
    newnode = malloc(sizeof(NODE));
    newnode -> data = data;
    newnode -> next = NULL;
return newnode;
}

NODE* Tcreate(NODE* head, int data)   
{
    NODE* newnode = CreateNode(data);
    NODE* helper = head;

    while (helper -> next != NULL)    
    {
        helper = helper->next;
    }
    helper -> next = newnode;         
return head;                          
}

NODE* CompleteCircle(NODE* head)
{
    int numbers[33]={2,1,1,1,1,1,1,1,2,2,2,1,2,2,1,1,2,2,2,1,1,1,1,2,1,2,2,1,1,2,1,2,1};
    for(int i = 0 ; i <= 32 ; i++)
    {
        head = Tcreate(head,numbers[i]);
    }

    NODE* helper = head;                  //使链表成环
    while (helper -> next != NULL)   
    {
        helper = helper->next;
    }
    helper->next = head;
return head;
}

NODE* DeleteAndPrint(NODE* head, int num ,FILE* file) 
{
    NODE* helper = head;
    NODE* helper2 = head;

    int NumInList = 1;  // 用来计算链表中节点的数量
    while (helper2 -> next != head) 
    {
        NumInList++;
        helper2 = helper2->next;
    }

    if (num == 1)     // 如果要删除的是头节点
    {  
        //printf("%d ", head -> data);
        fprintf(file, "%d ", head->data);
        helper = head->next;
        helper2 -> next = helper;  // 更新最后一个节点的 next 指向新的头节点
        free(head);
        head = helper;
    return head;  // 返回新的头节点
    }

    if (NumInList == 1) 
    {
        //printf("%d ", head->data);
        fprintf(file, "%d ", head->data);
        free(head);
    return NULL;  // 当只剩最后一个节点时，删除后返回 NULL 以终止循环
    }

    for (int i = 1; i < num - 1; i++)    //定位到要删除节点的前一个
    {  
        helper = helper->next;
    }
    NODE* bedeleted = helper->next;
    helper -> next = helper-> next -> next;      //连接被删除节点的前后两个
    //printf("%d ", bedeleted->data);
    fprintf(file, "%d ", bedeleted->data);
    free(bedeleted);
    head = helper->next;
return head;  // 返回被删除节点的下一个节点作为新的 head
}

int main()
{
    FILE* file = fopen("Josephus.out", "w");
    NODE* head = CreateNode(3);
    CompleteCircle(head);
 
    int i = 1;           //要删除的第 i 个数
    while(head != NULL)
    {    
    head = DeleteAndPrint(head, i, file);       //第 i 轮删除第 i 个
    i++;
    }
    fclose(file);
return 0;
}
```

程序的运行结果如图：
![](https://s3.bmp.ovh/imgs/2024/10/05/9605a82fbf413aa7.png)
![](https://s3.bmp.ovh/imgs/2024/10/05/02f0e463b18478bc.png)

结果为
```
3 1 1 2 2 1 2 1 1 2 1 2 2 1 1 2 2 1 1 2 2 1 1 2 2 1 1 2 1 1 1 1 1 2 
```
&nbsp;
#### **Part 3.栈个痛快**
```c
#include <stdio.h>
#include <string.h>


int top = -1;       //初始化栈中元素的下标为 -1
char stack[30];     //初始化栈中存储的字符最多为30个

void push(char letter)    //创建入栈函数
{
    top++;                //有字符入栈就对字符进行编号
    stack[top] = letter;  //把字符存入栈中
}

char pop()                //创建出栈函数
{
    char letter = stack[top];  //出栈的为当前栈顶字符
    top--;                     //更新字符出栈后栈顶的位置
return letter;                 //返回要出栈的字符的值
}

int main() 
{ 
    int letternum = 0;         //定义待处理的密文串的下标
    char letters[] = "kiglnmrmeiahenrteof4ardar";     //输入密文串
    int  numbers[] = {3,1,1,2,2,1,2,1,1,2,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,1,1,1,1,1,2};    //输入数字串

    for (int i = 1; i <= 35; i++)       //遍历数字串中的内容
    {
        if (i % 2 == 1)    //如果数字串的位置为奇数，执行压入操作
        {         
            for (int j = 0; j < numbers[i-1]; j++)  //判断完位置后，利用数字串的值通过 for 循环进行入栈操作
            {
                push(letters[letternum]);           //将密文串的内容压入栈中
                letternum++;
            }
        } 
        else               //如果数字串的位置为奇数，执行弹出操作 
        {           
            for (int j = 0; j < numbers[i-1]; j++) 
            {
                printf("%c", pop());  //打印通过栈输出的内容
            }
        }
    }
return 0;
}
```

程序的运行结果如图：
![](https://s3.bmp.ovh/imgs/2024/10/05/81e2f8ac3a5b88a1.png)

最终答案为：
```
glimmerinheartnofear4dark
```

也就是    
**Glimmer in heart no fear for dark**   
心有微光，不惧黑暗  

&nbsp;
&nbsp;
好一场浪漫 ~~且痛苦~~的解谜