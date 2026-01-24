#include "slink.h"
bool check(char* str)
{
    //在这里补全代码
    /****begin*****/
	//定义一个顺序栈并初始化
	sqstack s;
    initstack(s);
    char x, * p = str;
    bool flag = true;
	while (*p != '\0') {   //循环遍历字符串
        //左括号入栈
		if (*p == '{' || *p == '[' || *p == '(') { 
            push(s, *p);
        }
		//右括号出栈
        else {
			flag = pop(s, x);	//如果栈空，pop函数无法执行，返回false
			//如果栈顶元素是左括号，判断右括号是否匹配,如果不匹配，赋flag为false
			if (x == '(' && *p != ')') {  
                flag = false;
            }
            if (x == '[' && *p != ']') { 
                flag = false;
            }
            if (x == '{' && *p != '}') {
                flag = false;
            }
			if (!flag) return false;  //如果flag为false，说明没有左括号与之匹配
        }
        p++;
    }
    return true;
    /****end******/
}
