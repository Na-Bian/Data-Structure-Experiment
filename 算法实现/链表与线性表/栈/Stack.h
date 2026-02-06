#ifndef STACK_STACK_H
#define STACK_STACK_H

#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10 //存储空间分配增量


typedef enum {
    CHAR, INT
} ElemTypeTag;

typedef union {
    char cdata; //字符型数据
    int idata; //整型数据
} SElemType;

typedef struct {
    SElemType *base; //栈底指针
    SElemType *top; //栈顶指针
    int stacksize; //当前已分配的存储空间，以元素为单位
    ElemTypeTag tag; //栈中元素的数据类型
} SqStack;

//函数声明
SqStack *InitStack(ElemTypeTag); //构造一个ElemTypeTag类型的空栈S
void DestroyStack(SqStack *); //销毁栈S
void ClearStack(SqStack *); //清空栈S
bool StackEmpty(SqStack *); //栈S是否为空
int StackLength(SqStack *); //栈S的元素个数
bool StackTop(SqStack *, SElemType *); //获取栈顶元素
void Push(SqStack *, SElemType); //入栈
bool Pop(SqStack *, SElemType *); //出栈
void StackTraverse(SqStack *, void (*)(SElemType)); //对栈S从栈底到栈顶依次调用函数visit()

//数制转换
char *Convert(int, int);

//表达式求值
/*后缀表达式*/
int result(char *);

/*中缀表达式转后缀表达式*/
char *Transform(char *);

#endif //STACK_STACK_H
