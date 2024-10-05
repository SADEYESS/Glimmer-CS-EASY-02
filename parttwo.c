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