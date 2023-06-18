#include <stdio.h>

#define _mBeginASM 	__asm__ __volatile__ (
#define _mEndASM	);

int main(int argc, char *argv[]) {
    int a = 44, b = 33, c;

    _mBeginASM "addl		%%ebx,%%eax"
        : "=a"(c) /* 说明了调用'函数体'之后，应该把eax中的值赋值该变量c */
        : "b"(b),
          "a"(a) /* 表明了在调用'函数体'之前，应该把变量a复制到eax中,b复制到ebx中
                  */
          _mEndASM

              printf("%d\n", c);
    return 0;
}