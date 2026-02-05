# include "Polynomial.h"
# include <stdlib.h>
# include <stdio.h>


//有序插入多项式结点
//保证多项式按指数从大到小排列
void OrderInsert(Polynomial *poly, Polynomial *newNode) {
    if (!poly || !newNode) return;
    Polynomial *prev = poly, *curr = poly->next;
    //找到正确的插入位置
    while (curr && curr->degree > newNode->degree) {
        prev = curr;
        curr = curr->next;
    }
    //插入新结点
    if (curr && curr->degree == newNode->degree) {
        //指数相同，直接相加系数
        curr->coefficient += newNode->coefficient;
        //若系数为0，删除该结点
        if (curr->coefficient == 0) {
            prev->next = curr->next;
            free(curr);
        }
        free(newNode); //释放新结点内存
    } else {
        //否则插入到prev和curr之间
        newNode->next = curr;
        prev->next = newNode;
    }
}


//初始化多项式结点
Polynomial *InitNode(int degree, double coefficient) {
    Polynomial *node = malloc(sizeof(*node));
    node->degree = degree;
    node->coefficient = coefficient;
    node->next = nullptr;
    return node;
}

//创建一元多项式
//参数m表示多项式的项数
Polynomial *CreatPolyn(int m) {
    Polynomial *poly = InitNode(-1, 0.0); //创建头结点
    int count = 0; //成功创建的项数
    //循环创建多项式的每一项
    while (count < m) {
        printf("请输入第%d项的系数和指数：", count + 1);
        double coef;
        int deg;
        scanf("%lf %d", &coef, &deg);
        if (coef == 0) {
            //系数为0，跳过该项
            count++;
            continue;
        }
        if (deg < 0) {
            //指数为负，跳过该项
            printf("指数不能为负，跳过该项输入。\n");
            continue;
        }
        Polynomial *newNode = InitNode(deg, coef);
        OrderInsert(poly, newNode);
        count++;
    }
    return poly;
}

//销毁一元多项式
void DestroyPolyn(Polynomial *poly) {
    if (!poly) return;
    Polynomial *p = poly;
    while (p) {
        //循环释放每一个结点
        Polynomial *temp = p;
        p = p->next;
        free(temp);
    }
}

//打印一元多项式
void PrintPolyn(Polynomial *poly) {
    if (!poly) return;
    for (Polynomial *p = poly->next; p; p = p->next) {
        if (p != poly->next && p->coefficient > 0) {
            //不是第一项且系数为正，打印加号
            printf("+");
        }
        //打印系数和指数
        if (p->degree != 0) {
            printf("%gx^%d ", p->coefficient, p->degree);
        } else {
            printf("%g", p->coefficient);
        }
    }
    printf("\n");
}

//计算多项式的项数
int PolynLength(Polynomial *poly) {
    if (!poly) return -1;
    int length = 0;
    Polynomial *p = poly->next;
    while (p) {
        length++;
        p = p->next;
    }
    return length;
}
