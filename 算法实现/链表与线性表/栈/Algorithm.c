# include "Stack.h"
# include <stdlib.h>
# include <string.h>

//数制转换
//将十进制整数N转换为D(2<=D<=16)进制数，结果存入字符串s中
//SElemType为char
char *Convert(int N, int D) {
    if (N == 0) {
        char *s = malloc(2 * sizeof(char));
        strcpy(s, "0");
        return s;
    }
    SqStack *S = InitStack(CHAR);
    bool isNegative = false;
    unsigned int num;
    if (N < 0) {
        isNegative = true;
        num = (unsigned int) (-N);
    } else {
        num = (unsigned int) N;
    }
    //循环除基取余法
    while (num) {
        int remainder = num % D;
        SElemType e = {.cdata = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'A')}; //将余数转换为对应的字符
        Push(S, e);
        num /= D;
    }
    int len = StackLength(S) + isNegative, index = 0; //负数需要多一个字符存放负号
    //将栈中内容依次弹出存入字符串s
    char *s = malloc((len + 1) * sizeof(char));
    if (isNegative) {
        s[index++] = '-';
    }
    while (!StackEmpty(S)) {
        SElemType e;
        if (Pop(S, &e)) {
            s[index++] = e.cdata;
        }
    }
    s[len] = '\0';
    DestroyStack(S);
    return s;
}

//表达式求值
/*后缀表达式*/
//SElemType为int
int result(char *expr) {
    SqStack *s = InitStack(INT);
    //遍历表达式
    for (int i = 0; expr[i] != '\0'; i++) {
        //如果是操作数，入栈
        if (expr[i] >= '0' && expr[i] <= '9') {
            SElemType e = {.idata = expr[i] - '0'};
            Push(s, e);
        }
        //如果是运算符，弹出两个操作数进行计算，并将结果入栈
        else {
            int op1, op2;
            SElemType e;
            Pop(s, &e), op2 = e.idata; //注意后缀表达式中操作数的顺序，先弹出的操作数是op2
            Pop(s, &e), op1 = e.idata;
            switch (expr[i]) {
                case '+':
                    e.idata = op1 + op2;
                    Push(s, e);
                    break;
                case '-':
                    e.idata = op1 - op2;
                    Push(s, e);
                    break;
                case '*':
                    e.idata = op1 * op2;
                    Push(s, e);
                    break;
                case '/':
                    e.idata = op1 / op2;
                    Push(s, e);
                    break;
                default: exit(1);
            }
        }
    }
    SElemType res;
    Pop(s, &res);
    DestroyStack(s);
    return res.idata;
}

/*中缀表达式转后缀表达式*/
typedef enum {
    LEFT_PARE, RIGHT_PARE, ADD, SUB, MUL, DIV, MOD, EOS, NUM
} ContentType; //定义枚举类型ContentType表示运算符优先级

//获取符号symbol的类型
ContentType getToken(char symbol) {
    switch (symbol) {
        case '(': return LEFT_PARE;
        case ')': return RIGHT_PARE;
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        case '%': return MOD;
        case '\0': return EOS;
        default: return NUM; //数字
    }
}

//SElemType为char
char *Transform(char *infix) {
    SqStack *s = InitStack(CHAR);
    //定义优先级
    //注意'('在栈内和栈外的优先级不同，'('在栈内优先级最低，在栈外优先级最高
    int in_stack[] = {0, 19, 12, 12, 13, 13, 13, 0}; //栈内优先级
    int out_stack[] = {20, 19, 12, 12, 13, 13, 13, 0}; //栈外优先级
    //预先放入一个优先级最低的运算符EOS
    SElemType e = {.cdata = '\0'}; //EOS
    Push(s, e);
    char *postfix = (char *) malloc((strlen(infix) + 1) * sizeof(char));
    int index = 0; //后缀表达式的索引
    //遍历中缀表达式
    for (int i = 0; infix[i] != '\0'; i++) {
        int token = getToken(infix[i]);
        //如果是操作数，直接添加到后缀表达式中
        if (token == NUM) {
            postfix[index++] = infix[i];
        } else {
            //运算符
            //如果是右括号，弹出栈顶运算符直到遇到左括号
            if (token == RIGHT_PARE) {
                while (s->top[-1].cdata != '(') {
                    Pop(s, &e);
                    postfix[index++] = e.cdata;
                }
                Pop(s, &e); //左括号也弹出
            }
            //栈外优先级高于栈顶优先级，入栈
            else if (out_stack[token] > in_stack[getToken(s->top[-1].cdata)]) {
                e.cdata = infix[i];
                Push(s, e);
            }
            //否则先出栈保存栈顶运算符，再将当前运算符入栈
            else {
                Pop(s, &e);
                postfix[index++] = e.cdata;
                e.cdata = infix[i];
                Push(s, e);
            }
        }
    }
    //将栈中剩余的运算符依次弹出保存，栈底EOS添加到后缀表达式末尾
    while (!StackEmpty(s)) {
        Pop(s, &e);
        postfix[index++] = e.cdata;
    }
    return postfix;
}
