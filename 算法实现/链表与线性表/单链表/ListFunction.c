# include "List.h"


//初始化链表
List init_list(DataType type) {
    List head = malloc(sizeof(*head));
    if (type == INT) {
        head->data.int_data = -1; //头节点数据域设为-1
    } else if (type == CHAR) {
        head->data.char_data = '\0'; //头节点数据域设为'\0'
    }
    head->next = nullptr; //头节点指针域设为NULL
    return head;
}

//遍历输出链表
void print_list(List head, DataType type) {
    if (!head) {
        return;
    }
    Node *p = head->next;
    if (type == INT) {
        while (p) {
            printf("%d->", p->data.int_data);
            p = p->next;
        }
    } else if (type == CHAR) {
        while (p) {
            printf("%c->", p->data.char_data);
            p = p->next;
        }
    }
    printf("NULL\n");
}

//建立长度为n的链表
void build_list(List head, int n, DataType type) {
    if (!head || n <= 0) {
        return;
    }
    Node *p = head;
    for (int i = 1; i <= n; i++) {
        Node *new_node = malloc(sizeof(Node));
        if (!new_node) {
            printf("Memory allocation failed!\n");
            return;
        }
        if (type == INT) {
            //链表数据类型为整数
            printf("Please enter an integer number for node %d: ", i);
            scanf("%d", &new_node->data.int_data);
        } else {
            //链表数据类型为字符
            printf("Please enter a character for node %d: ", i);
            scanf(" %c", &new_node->data.char_data);
        }
        new_node->next = nullptr;
        p->next = new_node;
        p = p->next;
    }
}
