# include "Stack.h"
# include <stdlib.h>

// 构造一个空栈S
SqStack *InitStack(ElemTypeTag tag) {
    SqStack *S = malloc(sizeof(*S));
    //初始分配STACK_INIT_SIZE个存储单元
    S->base = (SElemType *) malloc(STACK_INIT_SIZE * sizeof(SElemType));
    S->top = S->base; //栈顶指针指向栈底
    S->stacksize = STACK_INIT_SIZE; //当前已分配的存储空间
    S->tag = tag; //栈中元素的数据类型
    return S;
}

//销毁栈S
void DestroyStack(SqStack *S) {
    if (!S) return;
    free(S->base);
    free(S);
}

//清空栈S
void ClearStack(SqStack *S) {
    if (!S) return;
    S->top = S->base;
}

//栈S是否为空
bool StackEmpty(SqStack *S) {
    if (!S) return true;
    return S->top == S->base;
}

//栈S的元素个数
int StackLength(SqStack *S) {
    if (!S) return '\0';
    return S->top - S->base;
}

bool StackTop(SqStack *S, SElemType *e) {
    if (!S || StackEmpty(S)) {
        //栈空或栈不存在，无法获取栈顶元素，返回空元素
        return false;
    }
    *e = *(S->top - 1);
    return true;
}

//入栈
void Push(SqStack *S, SElemType e) {
    if (!S) return;
    if (S->top - S->base >= S->stacksize) {
        //栈满，追加存储空间
        S->base = (SElemType *) realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    if (S->tag == CHAR) {
        S->top->cdata = e.cdata;
    } else {
        S->top->idata = e.idata;
    }
    S->top++;
}

//出栈
bool Pop(SqStack *S, SElemType *e) {
    if (!S || StackEmpty(S)) {
        //栈空或栈不存在，无法出栈
        return false;
    }
    *e = *--S->top;
    return true;
}

//对栈S从栈底到栈顶依次调用函数visit()
void StackTraverse(SqStack *S, void (*visit)(SElemType)) {
    if (!S) return;
    for (SElemType *p = S->base; p < S->top; p++) {
        visit(*p);
    }
}
