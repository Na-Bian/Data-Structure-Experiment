# include "Algorithm.c"

int main() {
    //测试函数find_last_k_node
    puts("Test function: find_last_k_node");
    List list = init_list(INT);
    int n;
    printf("Please enter the length of the linked list: ");
    scanf("%d", &n);
    build_list(list, n, INT);
    puts("The linked list is:");
    print_list(list, INT);
    int k;
    printf("Please enter the value of k to find the k-th last node: ");
    scanf("%d", &k);
    Node *last_k_node = find_last_k_node(list, k);
    if (last_k_node) {
        printf("The %d-th last node data is: %d\n", k, last_k_node->data.int_data);
    } else {
        //非法输入
        printf("Input k is invalid!\n");
    }
    puts("\nTest function: find_start_of_common_suffix");

    //测试函数find_start_of_common_suffix
    //测试用例：str_1 = "loading"，str_2 = "being"
    List str_1 = init_list(CHAR), str_2 = init_list(CHAR);
    int len_1 = 7;
    puts("Please enter \"loading\" one by one.");
    build_list(str_1, len_1, CHAR);
    Node *p = str_1;
    for (int i = 1; i <= 5; i++) {
        p = p->next;
    }
    int len_2 = 2;
    puts("Please enter \"be\" one by one.");
    build_list(str_2, len_2, CHAR);
    Node *q = str_2;
    while (q->next) {
        q = q->next;
    }
    q->next = p; //制造公共后缀
    puts("The first string is:");
    print_list(str_1, CHAR);
    puts("The second string is:");
    print_list(str_2, CHAR);
    Node *common_suffix_start = find_start_of_common_suffix(str_1, str_2);
    if (common_suffix_start) {
        printf("The starting node of the common suffix is: %c\n", common_suffix_start->data.char_data);
    } else {
        printf("There is no common suffix!\n");
    }

    //测试函数delete_middle_node
    puts("\nTest function: delete_middle_node");
    List list_2 = init_list(INT);
    int m;
    printf("Please enter the length of the linked list (odd number): ");
    scanf("%d", &m);
    build_list(list_2, m, INT);
    puts("The linked list before deleting the middle node is:");
    print_list(list_2, INT);
    delete_middle_node(list_2);
    puts("The linked list after deleting the middle node is:");
    print_list(list_2, INT);

    //测试函数reverse_list
    puts("\nTest function: reverse_list");
    List list_3 = init_list(INT);
    int p_len;
    printf("Please enter the length of the linked list (greater than 2): ");
    scanf("%d", &p_len);
    build_list(list_3, p_len, INT);
    puts("The linked list before reversal is:");
    print_list(list_3, INT);
    List reversed_list = reverse_list(list_3, INT);
    puts("The linked list after reversal is:");
    print_list(reversed_list, INT);

    //测试函数find_entry_of_loop
    //测试用例：1->2->3->4->5->6->7->8->3(环的入口节点为data=3的节点)
    puts("\nTest function: find_entry_of_loop");
    List loop_list = init_list(INT);
    printf("Please enter \"1 2 3 4 5 6 7 8\" one by one to build a linked list with a loop.\n");
    build_list(loop_list, 8, INT);
    Node *tail = loop_list;
    while (tail->next) {
        tail = tail->next;
    }
    Node *loop_entry = loop_list->next->next->next; //data=3
    tail->next = loop_entry; //制造环
    //查找环的入口节点
    Node *entry_node = find_entry_of_loop(loop_list);
    if (entry_node) {
        printf("The entry node of the loop has data: %d\n", entry_node->data.int_data);
    } else {
        printf("The linked list has no loop!\n");
    }

    //测试函数remove_duplicate_nodes
    puts("\nTest function: remove_duplicate_nodes");
    List list_4 = init_list(INT);
    int q_len;
    printf("Please enter the length of the linked list: ");
    scanf("%d", &q_len);
    build_list(list_4, q_len, INT);
    puts("The linked list before removing duplicate nodes is:");
    print_list(list_4, INT);
    remove_duplicate_nodes(list_4, 50); //假设链表中data的绝对值不超过50
    puts("The linked list after removing duplicate nodes is:");
    print_list(list_4, INT);
    return 0;
}
