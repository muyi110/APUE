/*
利用longjmp和setjmp函数实现跨栈跳转
*/
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

jmp_buf jmpbuffer;
void test_func1(void);
void test_func2(void);

int main(int argc, char *argv[])
{
    int res;

    res = setjmp(jmpbuffer);
    if(res != 0)
    {
        printf("function res: %d\n", res);
        exit(0);
    }
    else
    {
        printf("main res: %d\n", res);
    }
    test_func1();
    return 0;
}

void test_func1(void)
{
    printf("test func1\n");
    test_func2();
}

void test_func2(void)
{
    printf("test func2\n");
    longjmp(jmpbuffer, 2);
}
