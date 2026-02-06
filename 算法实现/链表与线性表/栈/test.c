# include "Stack.h"
# include <stdio.h>
# include <stdlib.h>

int main(void) {
    //测试数制转换
    int N, D;
    printf("Please enter the value of N: ");
    scanf("%d", &N);
    printf("Please enter the base D (2<=D<=16): ");
    scanf("%d", &D);
    char *converted = Convert(N, D);
    printf("Number %d in base %d is: %s\n", N, D, converted);
    free(converted);

    //测试表达式求值
    char expr[100];
    printf("Please enter a infix expression (e.g., 3+(4*5)-6): ");
    scanf("%s", expr);
    char *postfix = Transform(expr);
    printf("The result of the expression %s is: %d\n", postfix, result(postfix));
    free(postfix);
    return 0;
}
