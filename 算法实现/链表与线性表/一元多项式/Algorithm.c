# include "Polynomial.h"
# include <stdlib.h>


//多项式加法
Polynomial *AddPolyn(Polynomial *p1, Polynomial *p2) {
    if (!p1 || !p2) return nullptr;
    Polynomial *result = CreatPolyn(0), *p = result;
    Polynomial *pa = p1->next, *pb = p2->next;
    //遍历两个多项式
    while (pa != nullptr && pb != nullptr) {
        if (pa->degree > pb->degree) {
            //pa的指数更大，直接插入结果多项式
            Polynomial *newNode = InitNode(pa->degree, pa->coefficient);
            p->next = newNode;
            pa = pa->next;
            p = p->next;
        } else if (pa->degree < pb->degree) {
            //pb的指数更大，直接插入结果多项式
            Polynomial *newNode = InitNode(pb->degree, pb->coefficient);
            p->next = newNode;
            pb = pb->next;
            p = p->next;
        } else {
            //指数相同，系数相加
            double sumcoef = pa->coefficient + pb->coefficient;
            if (sumcoef != 0) {
                //创建新结点插入结果多项式
                Polynomial *newNode = InitNode(pa->degree, sumcoef);
                p->next = newNode;
                p = p->next;
            }
            pa = pa->next;
            pb = pb->next;
        }
    }
    //将剩余项直接插入结果多项式
    pa = pa ? pa : pb;
    while (pa) {
        Polynomial *newNode = InitNode(pa->degree, pa->coefficient);
        p->next = newNode;
        p = p->next;
        pa = pa->next;
    }
    return result;
}

//多项式减法
Polynomial *SubtractPolyn(Polynomial *p1, Polynomial *p2) {
    if (!p1 || !p2) return nullptr;
    //创建p2的相反数多项式
    Polynomial *negp2 = CreatPolyn(0), *curr = negp2;
    for (Polynomial *p = p2->next; p; p = p->next) {
        Polynomial *newNode = InitNode(p->degree, -p->coefficient); //系数取相反数
        curr->next = newNode; //插入新结点
        curr = curr->next;
    }
    //调用加法函数实现减法
    Polynomial *result = AddPolyn(p1, negp2);
    DestroyPolyn(negp2); //销毁临时多项式
    return result;
}

//多项式乘法
Polynomial *MultiplyPolyn(Polynomial *p1, Polynomial *p2) {
    if (!p1 || !p2) return nullptr;
    Polynomial *result = CreatPolyn(0);
    for (Polynomial *pa = p1->next; pa; pa = pa->next) {
        for (Polynomial *pb = p2->next; pb; pb = pb->next) {
            //用p2的每一项乘以p1的每一项
            int newDegree = pa->degree + pb->degree;
            double newCoefficient = pa->coefficient * pb->coefficient;
            Polynomial *newNode = InitNode(newDegree, newCoefficient);
            OrderInsert(result, newNode); //插入结果多项式
        }
    }
    return result;
}
