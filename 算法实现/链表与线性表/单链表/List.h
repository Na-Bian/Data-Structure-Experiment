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

Node *find_last_k_node(List, int); //查找链表中倒数第k个节点
Node *find_start_of_common_suffix(List, List); //查找具有相同后缀的两个单词，共同后缀的起始位置
void delete_middle_node(List); //删除链表中间的节点（长度为奇数且大于2）
List reverse_list(List, DataType); //反转链表（元素个数>2）
Node *find_entry_of_loop(List); //判断链表是否有环并找到环的入口
void remove_duplicate_nodes(List, int); //将链表中data绝对值相等的节点仅保留第一次出现的节点，已知|data| <= n

# endif //LIST_LIST_H
