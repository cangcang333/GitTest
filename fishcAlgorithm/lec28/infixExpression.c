/*************************************************************************
	> File Name: infixExpression.c
	> Author: 
	> Mail: 
	> Created Time: 一  1/14 21:32:22 2019
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT  10

typedef char ElemType;
typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
}sqStack;

void InitStack(sqStack *s)
{
    s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if (NULL == s->base)
    {
        exit(0);
    }
    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE;
}


void Push(sqStack *s, ElemType e)
{
    // If stack is empty, then add space
    if (s->top - s->base >= s->stackSize)
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
        s->top = s->base + s->stackSize;
        s->stackSize = s->stackSize + STACKINCREMENT;
    }
    *(s->top) = e;
    s->top++;
}

void Pop(sqStack *s, ElemType *e)
{
    // If stack is empty, then pop nothing
    if (s->top == s->base)
    {
        return ;
    }
    *e = *--(s->top);
}

int StackLen(sqStack s)
{
    return (s.top - s.base);
}


// Input example: 1+(2-3)*4+10/5
// Output: 123-4*+105/+
// Output: 1 2 3 - 4 * + 10 5 / +

int main()
{
    sqStack s;
    char c, e;

    InitStack(&s);

    printf("Please input infix expression, end with '#': ");
    scanf("%c", &c);

    while (c != '#')
    {
        while (c >= '0' && c <= '9')
        {
            printf("%c", c);
            scanf("%c", &c);
            if (c < '0' || c > '9')
            {
                printf(" ");
            }
        }

        if (')' == c)
        {
            Pop(&s, &e);
            while (e != '(')
            {
                printf("%c ", e);
                Pop(&s, &e);
            }
        }
        else if ('+' == c || '-' == c)
        {
            if (!StackLen(s))
            {
                Push(&s, c);
            }
            else
            {
                do
                {
                    Pop(&s, &e);
                    if ('(' == e)
                    {
                        Push(&s, e);
                    }
                    else
                    {
                        printf("%c ", e);

                    }
				// Next line is important, try to comment
                } while (StackLen(s) && '(' != e);
                
                Push(&s, c);
            }
        }
        else if ('*' == c || '/' == c || '(' == c)
        {
            Push(&s, c);
        }
        else if ('#' == c)
        {
            break;             
        }
        else
        {
            printf("\nInput error\n");
            return -1;
        }

        scanf("%c", &c);
    }

    while (StackLen(s))
    {
        Pop(&s, &e);
        printf("%c ", e);
    }
    printf("\n");

    return 0;
}


