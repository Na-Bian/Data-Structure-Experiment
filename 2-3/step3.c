//Your code begin.
//示例仅供参考，你也可以自行修改设计
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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

typedef enum bool{  //定义枚举类型bool，包含true和false
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
	bool flag = 0;   //flag为标志变量
	int index = 0;   //index作为字符数组x的下标
	ListNode* q = head;  //q指向头结点
	//使用fgets函数循环读取输入，直到遇到EOF
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
char* print_code(ListNode* head, char* x, int* WPL)	  //print_code函数用于根据建立的哈夫曼树对字符串进行编码，并记录其WPL
{
	ListNode* p = head->next;
	//code用于存储字符串的编码，v用于遍历字符串x
	char* code = (char*)malloc(sizeof(char)), * v = x;
	if (!code) {
		puts("Memory allocation failed!");
		exit(EXIT_FAILURE);
	}
	code[0] = '\0';  //初始化code
	while (*v != '\0') {  //遍历字符串x
		while (p->c != *v) {   //遍历频度链表，找到当前字符
			p = p->next;
		}
		code = (char*)realloc(code, sizeof(char) * (strlen(code) + strlen(p->code) + 1));  //动态分配内存
		if (!code) {
			puts("Memory allocation failed!");
			exit(EXIT_FAILURE);
		}
		strncat(code, p->code, strlen(p->code) + 1);  //将当前字符的编码添加到code中
		*WPL += strlen(p->code);  //更新WPL
		p = head->next;  //让p重新指向头结点的下一个结点
		v++;
	}
	return code;   //返回编码后的字符串
}
void build_Huffman_Tree(ListNode* head, int count)
{
	ListNode* min1, * min2;  //min1和min2分别指向频度链表中最小和次小的结点
	//第一次调用时，min1和min2分别指向频度链表的倒数第二个和最后一个结点
	min1 = head;
	min2 = min1->next;
	while (min2->next) {
		min1 = min1->next;
		min2 = min2->next;
	}
	//字符数为n的频度链表，哈夫曼树共有2n-1个结点，需要进行n-1次循环，构造n-1个哈夫曼树结点
	for (int i = 1; i <= count - 1; ++i) {
		//临时结点temp用于存储新建的哈夫曼树结点
		ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
		if (!temp) {
			//内存分配失败
			puts("Memory allocation failed!");
			exit(EXIT_FAILURE);
		}
		//初始化新建的哈夫曼树结点
		temp->c = '\0';   //置新建的哈夫曼树结点的字符为'\0'，与链表中的有效字符进行区分，便于后续编码
		temp->frequency = min1->frequency + min2->frequency;  //新建的哈夫曼树结点的频度为min1和min2的频度之和
		temp->left = min1;  //左子树为min1
		temp->right = min2;  //右子树为min2
		temp->parent = NULL;  //新建的哈夫曼树结点的双亲结点为NULL
		min1->parent = min2->parent = temp;  //min1和min2的双亲结点为新建的哈夫曼树结点
		//将新建的哈夫曼树结点插入频度链表中
		temp->next = head->next;  //为方便起见，先将新建的哈夫曼树结点插入频度链表的头部
		head->next = temp;
		//调用sort_List函数对频度链表进行排序，注意此时链表的长度已经变为count+i
		sort_List(head, count + i);
		ListNode* u = min1;  //u用于记录min1的位置
		//重新设置min1和min2
		min1 = head;
		min2 = min1->next;
		//对频度链表重新排序后，下一轮的min2->next即指向该轮次的次小结点(u)
		while (min2->next != u) {
			min1 = min1->next;
			min2 = min2->next;
		}
	}
}
void Huffmancoding(ListNode* head, int count)    //Huffmancoding函数用于对频度链表中的字符进行编码
{
	ListNode* p = head->next;    //p指向频度链表的第一个结点
	char* cd = (char*)malloc(sizeof(char) * count);   //cd作为工作空间，用于临时存储编码
	//字符编码的最大长度不会超过count，因此分配count个字符的内存
	if (!cd) {
		//内存分配失败
		puts("Memory allocation failed!");
		exit(EXIT_FAILURE);
	}
	int index;    //index作为cd的下标
	cd[count - 1] = '\0';   //cd的最后一位为'\0'
	//遍历频度链表
	while (p) {
		//当p->c!='\0'时，说明p->c是频度链表中的一个有效字符
		if (p->c != '\0') {
			index = count - 1;   //向前存储编码
			ListNode* g, * f;
			//从p结点开始向上遍历，直到找到根结点
			for (g = p, f = g->parent; f; g = f, f = g->parent) {
				//如果g是f的左子树，则cd的下标减1，存储0
				if (f->left == g) {
					cd[--index] = '0';
				}
				//否则cd的下标减1，存储1
				else {
					cd[--index] = '1';
				}
			}
			p->code = (char*)malloc(sizeof(char) * (count - index));   //为p->code编码分配内存
			//cd中的有效编码从cd[index]开始，因此向strcpy函数传入&cd[index]，将编码存入p->code
			strcpy(p->code, &cd[index]);
		}
		p = p->next;    //p指向下一个结点
	}
	free(cd);     //释放工作空间cd的内存
}
void decode(ListNode* head, char* code, char decode[])  //decode函数用于对已编码后的字符串进行解码
{
	ListNode* p = head->next;  //p指向频度链表的第一个结点
	char temp[MAX_CHAR] = { '\0' };  //temp用于临时存储当前字符的编码
	char* v = code;   //v用于遍历编码后的字符串
	while (1) {
		//遍历频度链表，找到当前字符的编码
		while (p) {
			if (p->c != '\0') {   //p->c != '\0'表明p->c为频度链表中的有效字符
				if (strcmp(p->code, temp) == 0) {   //找到当前字符
					decode[strlen(decode)] = p->c;  //将当前字符添加到decode中
					memset(temp, '\0', sizeof(temp));  //将temp清空
					break; 
				}
			}
			p = p->next;
		}
		temp[strlen(temp)] = *v;  //将当前编码值添加到temp中
		p = head->next;  //让p重新指向头结点
		v++;   //v指向下一个编码值
		if (*v == '\0') {  //编码后的字符串已经遍历完毕，处理最后一个字符
			while (p) {
				if (p->c != '\0') {  //p->c != '\0'表明p->c为频度链表中的有效字符
					if (strcmp(p->code, temp) == 0) {   //找到当前字符
						decode[strlen(decode)] = p->c;  //将当前字符添加到decode中
						break;
					}
				}
				p = p->next;
			}
			break;
		}
	}
	decode[strlen(decode)] = '\0';  //添加字符串结束符
}
int main()
{
	char x[MAX_CHAR];
	int count = 0;   //count用于记录频度链表中字符的个数
	ListNode* Node = initListNode();   //初始化频度链表
	input(Node, x, &count);  //将字符存入建立的频度链表
	sort_List(Node, count);  //对频度链表按频度高低重新排列
	build_Huffman_Tree(Node, count);   //建立哈夫曼树
	Huffmancoding(Node, count);   //对频度链表中的字符进行编码
	int WPL = 0;   //WPL为加权路径长度
	char DECODE[MAX_CHAR] = { '\0' };  //定义解码后的字符串并对其进行初始化
	char* code = print_code(Node, x, &WPL);  //对字符串进行编码，并记录其WPL
	decode(Node, code, DECODE);   //对字符串进行解码
	printf("%s\n%s\n%d", code, DECODE, WPL);  //格式化输出编码后的字符串、解码后的字符串和WPL
	return 0;
}
//Your code end.
