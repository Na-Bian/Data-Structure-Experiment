# ifndef LIST_LIST_H
# define LIST_LIST_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

//定义数据类型
typedef union Data {
    int int_data;
    char char_data;
} Data;

//定义链表节点类型
typedef struct Node {
    Data data;
    struct Node *next;
} Node, *List;


//定义枚举类型DataType，标识链表数据类型
typedef enum DataType {
    INT,
    CHAR
} DataType;

List init_list(DataType); //初始化链表
void print_list(List, DataType); //遍历输出链表
void build_list(List, int, DataType); //建立长度为n的链表

# endif //LIST_LIST_H
