#include <stdio.h>
#include <stdlib.h>

typedef struct Node    //定义出节点的结构体，包含存储的数据和下一个节点的指针两部分
{
    int data;
    struct Node* next;
} NODE;

NODE* CreateNode(int data)   //创建节点的函数，为新的节点动态分配内存，获取输入和数据并初始化指针为空
{
    NODE* newnode;
    newnode = malloc(sizeof(NODE));
    newnode -> data = data;
    newnode -> next = NULL;
return newnode;
}

NODE* Hcreate(NODE* head, int data)   //创建H操作的函数
{
    NODE* newnode;
    newnode = CreateNode(data);       //获取新节点存储的数据
    newnode -> next = head;           //H操作创建出的节点指向原来链表的头节点
return newnode;                       //创建的新节点作为头结点，返回新的头结点
}

NODE* Tcreate(NODE* head, int data)   //创建T操作的函数
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

NODE* Delete(NODE* head, int num)     //创建D操作的函数
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