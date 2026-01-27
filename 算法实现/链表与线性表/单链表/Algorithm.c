# include "List.h"


/*
 * 快慢指针法
 */

//查找链表中倒数第k个节点
Node *find_last_k_node(List head, int k) {
    if (!head || k <= 0) {
        return nullptr;
    }
    Node *slow;
    Node *fast = slow = head;
    //先让fast指针走k步
    for (int i = 1; i <= k; i++) {
        if (!fast) {
            return nullptr; //链表长度小于k
        }
        fast = fast->next;
    }
    //同步移动fast和slow指针，直到fast指向NULL
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

//查找具有相同后缀的两个单词，共同后缀的起始位置
Node *find_start_of_common_suffix(List str_1, List str_2) {
    if (!str_1 || !str_2) {
        return nullptr;
    }
    //求出两个单词的长度
    int len_1 = 0, len_2 = 0;
    Node *fast = str_1, *slow = str_2;
    while (fast->next) {
        fast = fast->next;
        len_1++;
    }
    while (slow->next) {
        slow = slow->next;
        len_2++;
    }
    //让fast指针指向较长的单词头节点，先走|len_1 - len_2|步
    fast = (len_1 > len_2) ? str_1 : str_2;
    slow = (len_1 > len_2) ? str_2 : str_1;
    for (int i = 1; i <= abs(len_1 - len_2); i++) {
        fast = fast->next;
    }
    //同步移动fast和slow指针，直到两者相等
    while (fast && slow && fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}

//删除链表中间的节点（长度为奇数且大于2）
void delete_middle_node(List head) {
    if (!head || !head->next || !head->next->next) {
        return;
    }
    Node *slow;
    Node *fast = slow = head;
    //每次slow先走一步，然后fast走两步，直到fast->next为NULL
    while (1) {
        for (int i = 1; i <= 2 && fast->next; i++) {
            fast = fast->next;
        }
        if (!fast->next) {
            break;
        }
        slow = slow->next;
    }
    //slow指向待删除节点的前驱节点
    Node *to_delete = slow->next;
    //删除节点
    slow->next = to_delete->next;
    free(to_delete);
}

//反转链表（元素个数>2）
List reverse_list(List head, DataType type) {
    //先让first指向NULL，second指向head->next，third指向head->next->next
    if (!head || !head->next || !head->next->next) {
        return nullptr;
    }
    Node *first = nullptr, *second = head->next;
    //每次让second->next指向first，然后依次后移三个指针，直到second为NULL
    while (second) {
        Node *third = second->next;
        second->next = first;
        first = second;
        second = third;
    }
    //设置新的头节点
    Node *new_head = init_list(type);
    new_head->next = first;
    return new_head;
}

//判断链表是否有环并找到环的入口
Node *find_entry_of_loop(List head) {
    if (!head) {
        return nullptr;
    }
    //使用快慢指针法判断链表是否有环
    Node *slow;
    Node *fast = slow = head;
    //每次slow走一步，fast走两步
    while (1) {
        slow = slow->next;
        for (int i = 1; i <= 2 && fast; i++) {
            fast = fast->next;
        }
        if (!fast) {
            return nullptr; //链表无环
        }
        if (fast == slow) {
            break; //链表有环，跳出循环
        }
    }
    //让fast继续走，直到再次相遇，走的步数即环的大小
    int loop_size = 0;
    do {
        fast = fast->next;
        loop_size++;
    } while (fast != slow);
    //让fast指针先走loop_size步，然后fast和slow同步移动，直到两者相等
    fast = slow = head;
    for (int i = 1; i <= loop_size; i++) {
        fast = fast->next;
    }
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }
    return fast; //返回环的入口节点
}

/*
 * 用空间换时间
 */

//将链表中data绝对值相等的节点仅保留第一次出现的节点，已知|data| <= n
void remove_duplicate_nodes(List head, int n) {
    if (!head) {
        return;
    }
    //声明大小为n的辅助数组visited
    bool *visited = calloc(n + 1, sizeof(bool));
    if (!visited) {
        //内存分配失败
        printf("Memory allocation failed!\n");
        return;
    }
    Node *p = head->next, *prev = head;
    while (p) {
        //若visited[|data|]为true，则删除该节点
        if (visited[abs(p->data.int_data)]) {
            prev->next = p->next;
            free(p);
            p = prev->next;
        } else {
            //否则将visited[|data|]设为true，继续遍历
            visited[abs(p->data.int_data)] = true;
            prev = p;
            p = p->next;
        }
    }
    free(visited);
}
