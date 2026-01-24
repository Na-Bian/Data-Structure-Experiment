//Your code begin.
//示例仅供参考，你也可以自行修改设计
#include<stdio.h>
#include<stdlib.h>
#define MAX_CHAR 4096   //字符集的最大长度

typedef struct ListNode            //结点结构，哈夫曼树与频度链表共用
{
    char      c;                    //结点的字符
    int      frequency;            // 字符的频度
    char* code;            // 字符的编码(对哈夫曼树结点有效)
    struct ListNode* parent;            //结点的双亲结点(对哈夫曼树结点有效)
    struct ListNode* left;                //结点的左子树(对哈夫曼树结点有效)
    struct ListNode* right;                // 结点的右子树(对哈夫曼树结点有效)
    struct ListNode* next;                // 结点的后继结点(对频度链表结点有效)
}ListNode, HuffmanTree;

typedef enum bool{      //定义枚举类型bool，包含true和false
    false,true
}bool;

ListNode* initListNode()          //initListNode函数用于初始化频度链表
{
    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    if (!head) {
        //内存分配失败
        puts("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    head->c = '\0';               //初始化头结点
    head->frequency = -1;
    head->left = head->right = head->parent = head->next = NULL;
    return head;
}
void input(ListNode* head, char* x, int* n)  //input函数用于将字符存入建立的频度链表
{
    bool flag = false;   //flag为标志变量
	int index = 0;  //index作为字符数组x的下标
    ListNode* q = head;  //q指向头结点
    //使用getchar函数循环读取输入，直到遇到EOF
    while ((x[index] = getchar()) != EOF) {
        index++;
    }
    x[index] = '\0';
    char* p = x;
    while (*p != '\0') {      //处理每个字符
        while (1) {   //先遍历频度链表，判断链表中是否已包含正在读取的字符
            if (q->c == *p) {    //如果找到
                flag = true;
                q->frequency++;
                break;
            }
            if (q->next == NULL) {   //遍历循环终止条件
                //使用break语句，目的在于循环终止后p仍指向尾结点，便于未找到时添加新的结点
                break;
            }
            q = q->next;
        }
        if (!flag) {   //链表中不包含正在读取的字符，需要添加新的结点
            ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
            if (!temp) {
                //内存分配失败
                puts("Memory allocation failed!");
                exit(EXIT_FAILURE);
            }
            //初始化新的结点
            temp->frequency = 1;
            temp->c = *p;
            head->left = head->right = head->parent = temp->next = NULL;
            q->next = temp;   //承上，使用break语句的好处
            (*n)++;  //频度链表中字符的个数加1
        }
        //处理完当前字符后的重置工作
        q = head;  //让q重新指向头结点
        p++;  //p指向下一个要读取的字符
        flag = false;   //flag标志变量重置为false
    }
}
void exchange(ListNode* head, ListNode* p)      //exchange函数用于交换p结点和p的前驱结点
{
    ListNode* r = head, * q = r->next;
    while (q->next != p) {    //遍历找到p的前驱节点
        r = r->next;
        q = q->next;
    }                       //此时q指向p的前驱结点，r指向q的前驱结点
    r->next = p;           //交换p结点和q结点
    q->next = p->next;
    p->next = q;
}
void sort_List(ListNode* head, int n)   //sort_List函数用于对频度链表按频度高低重新排列
{
    bool flag = true;
    ListNode* r = head;
    int i, j, k;
    //类比一维数组中的冒泡排序
    for (i = 1; i <= n && flag; i++) {
        //flag标志变量用于判断频度链表是否已经排好
        flag = false;
        for (j = n - 1; j >= i; j--) {
            //之前设置的count计数器在此发挥作用
            for (k = 1; k <= j; k++) {  //通过循环，让r指向当前需要判断的结点
                r = r->next;
            }
            if (r->frequency < r->next->frequency) {  //未排好，调用exchange函数进行交换
                exchange(head, r->next);
                flag = true;  //置flag为true，表示当前链表仍未排好
            }
            r = head;  //一轮判断结束，需要让r重新指向头结点
        }
    }
}
void print_List(ListNode* head)        //print_List函数用于格式化输出频度链表内容
{
	ListNode* p = head->next;    //初始时，p指向头结点的后继结点
    while (p) {     //遍历整个链表，直到p为NULL
        if (p->c == '\n') {      //处理字符为\n的情况
            printf("\'\\n\' %d\n", p->frequency);
        }
        else {
            printf("\'%c\' %d\n", p->c, p->frequency);
        }
        p = p->next;
    }
}
int main()
{
    char x[MAX_CHAR];
    int count = 0;   //count用于记录频度链表中字符的个数
    ListNode* Node = initListNode();   //初始化频度链表
    input(Node, x, &count);  //将字符存入建立的频度链表
    sort_List(Node, count);  //对频度链表按频度高低重新排列
    print_List(Node);    //格式化输出频度链表内容
    return 0;
}
//Your code end.
