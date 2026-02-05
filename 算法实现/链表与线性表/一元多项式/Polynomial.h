#ifndef POLYNOMIAL_POLYNOMIAL_H
#define POLYNOMIAL_POLYNOMIAL_H


//定义多项式结点结构体
typedef struct Polynomial {
    int degree;
    double coefficient;
    struct Polynomial *next;
} Polynomial;

//函数声明

//有序插入多项式结点
void OrderInsert(Polynomial *, Polynomial *);

//初始化多项式结点
Polynomial *InitNode(int, double);

//创建一元多项式
Polynomial *CreatPolyn(int);

//销毁一元多项式
void DestroyPolyn(Polynomial *);

//打印一元多项式
void PrintPolyn(Polynomial *);

//计算多项式的项数
int PolynLength(Polynomial *);

//多项式加法
Polynomial *AddPolyn(Polynomial *, Polynomial *);

//多项式减法
Polynomial *SubtractPolyn(Polynomial *, Polynomial *);

//多项式乘法
Polynomial *MultiplyPolyn(Polynomial *, Polynomial *);

#endif //POLYNOMIAL_POLYNOMIAL_H
