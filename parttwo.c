#include <stdio.h>
#include <stdlib.h>

typedef struct Node                                  //定义结构体，同 part 1
{
    int data;
    struct Node* next;
}NODE;

NODE* CreateNode(int data)                           //定义创建新节点的函数，同 part 1
{
    NODE* newnode;
    newnode = malloc(sizeof(NODE));
    newnode -> data = data;
    newnode -> next = NULL;
return newnode;
}

NODE* Tcreate(NODE* head, int data)                 //定义插入节点的函数，同 part 1
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

NODE* CompleteCircle(NODE* head)                   //定义使单链表成环的函数
{
    int numbers[33]={2,1,1,1,1,1,1,1,2,2,2,1,2,2,1,1,2,2,2,1,1,1,1,2,1,2,2,1,1,2,1,2,1};    //以数组的形式将节点数据写入到链表中，为了减小创建链表的难度，将第一个数字 3 作为头节点在主函数里创建，这里只插入剩余元素
    for(int i = 0 ; i <= 32 ; i++)                 //利用 for 循环为节点数据赋值
    {
        head = Tcreate(head,numbers[i]);
    }

    NODE* helper = head;                           //引入辅助节点使链表成环
    while (helper -> next != NULL)                 //利用 while 循环，一直找到单链表的末尾节点
    {
        helper = helper->next;
    }
    helper->next = head;                           //使单链表首尾相连
return head;                                       //返回头节点
}

NODE* PrintAndDelete(NODE* head, int num ,FILE* file)    //创建用于打印并删除报到目标数字的节点的函数，使用文件指针来把数据直接写入文件里
{
    NODE* helper = head;                                 //引入两个辅助节点用于操作
    NODE* helper2 = head;

    int NumInList = 1;                                   //统计链表中节点的数量
    while (helper2 -> next != head) 
    {
        NumInList++;
        helper2 = helper2->next;
    }

    if (num == 1)                                       //如果要删除的是头节点的情况
    {  
        fprintf(file, "%d ", head->data);               //将目标数字写入文件
        helper = head->next;
        helper2 -> next = helper;                       //使最后一个节点指向新的头节点
        free(head);                                     //删除目标节点
        head = helper;                                  //建立新的头结点
    return head;                                        //返回新的头节点
    }

    if (NumInList == 1)                                //如果只剩下最后一个数
    {
        fprintf(file, "%d ", head->data);
        free(head);
    return NULL;                                       //返回空指针结束循环
    }

    for (int i = 1; i < num - 1; i++)                  //在非特殊情况下，利用 for 循环定位到要删除节点的前一个
    {  
        helper = helper->next;
    }
    NODE* bedeleted = helper->next;
    helper -> next = helper-> next -> next;           //连接被删除节点的前后两个节点
    fprintf(file, "%d ", bedeleted->data);
    free(bedeleted);
    head = helper->next;
return head;                                          //返回被删除节点的下一个节点作为新的头节点
}

int main()
{
    FILE* file = fopen("Josephus.out", "w");          //创建文件指针，以写入的模式打开文件
    NODE* head = CreateNode(3);                       //创建头节点3
    CompleteCircle(head);                             //创建题目要求的环形链表
 
    int i = 1;                                        //当前要删除的第 i 个数
    while(head != NULL)                               //如果链表中节点未全部被删除，循环操作来报数
    {    
    head = PrintAndDelete(head, i, file);             //第 i 轮删除第 i 个
    i++;
    }
    fclose(file);                                     //关闭文档
return 0;
}