# include <stdio.h>
# include "Polynomial.h"

int main(void) {
    //建立多项式1
    printf("创建多项式1:\n");
    int m1;
    printf("请输入多项式1的项数：");
    scanf("%d", &m1);
    Polynomial *poly1 = CreatPolyn(m1);
    printf("多项式1为：");
    PrintPolyn(poly1);
    //建立多项式2
    printf("创建多项式2:\n");
    int m2;
    printf("请输入多项式2的项数：");
    scanf("%d", &m2);
    Polynomial *poly2 = CreatPolyn(m2);
    printf("多项式2为：");
    PrintPolyn(poly2);
    //多项式加法
    Polynomial *sumPoly = AddPolyn(poly1, poly2);
    printf("多项式1 + 多项式2 = ");
    PrintPolyn(sumPoly);
    //多项式减法
    Polynomial *diffPoly = SubtractPolyn(poly1, poly2);
    printf("多项式1 - 多项式2 = ");
    PrintPolyn(diffPoly);
    //多项式乘法
    Polynomial *prodPoly = MultiplyPolyn(poly1, poly2);
    printf("多项式1 * 多项式2 = ");
    PrintPolyn(prodPoly);
    //销毁多项式
    DestroyPolyn(poly1);
    DestroyPolyn(poly2);
    DestroyPolyn(sumPoly);
    DestroyPolyn(diffPoly);
    DestroyPolyn(prodPoly);
    return 0;
}
