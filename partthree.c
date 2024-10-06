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