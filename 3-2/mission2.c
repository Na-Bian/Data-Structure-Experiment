//Your code begin.
//示例仅供参考，你也可以自行修改设计。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTEX_NUM 20     //图的最大顶点数
#define MAX_ROW_NUM 256       //每行读取的最大字符数
#define MAX_STATION_NUM 30    //每个站点名称的最大字符数
#define MAX_FLOAT 0x10000     //定义最大浮点数为0x10000
typedef enum bool    //自定义定义枚举类型bool，包含true和false
{
	false,true
}bool;
typedef struct arc     //作为邻接表头节点所指向的边
{
	char NAME[MAX_STATION_NUM];   //存储指向的节点
	float dist;                   //存储边的长度
	struct arc* next;             //指向下一条邻接的边
} arc;
typedef struct VNode   //站点顶点
{
	char name[MAX_STATION_NUM];   //存储站点名称
	int num;                      //存储相邻站点总数
	arc* add;                     //指向邻接表头结点
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct Graph   //以邻接表存储的图
{
	AdjList adjlist;   //邻接表
	int numVertex;     //图的顶点数
	int numArc;        //图的边数
}Graph;
typedef struct Stack   //顺序栈
{
	int* data;    //数据域
	int top;      //栈顶指针
}Stack;

void getcache(char cache[])     //getcache函数用于获取输入的每一行数据
{
	int index = 0;  //index作为cache缓存区的索引
	while ((cache[index] = getchar()) != '\n' && cache[index] != EOF) {   //从标准输入读取数据
		index++;
	}
	cache[index] = '\0';  //在末尾添加结束符
}
void processrow(char cache[], char str_1[], char str_2[], float* length)   //processrow函数用于处理输入的每一行的数据
{
	int i = 0, j = 0;
	while (cache[i] != ' ' && cache[i] != '\0') {   //找到第一个站点名称结束的位置
		i++;
	}
	strncpy(str_1, cache, i);   //拷贝第一个站点名称
	str_1[i] = '\0';  //在末尾添加结束符
	while (cache[i] == ' ') {   //跳过空格
		i++;
	}
	j = i;
	while (cache[j] != ' ' && cache[j] != '\0') {   //找到第二个站点名称结束的位置
		j++;
	}
	strncpy(str_2, &cache[i], j - i);   //拷贝第二个站点名称
	str_2[j - i] = '\0';   //在末尾添加结束符
	while (cache[j] == ' ') {  //跳过空格
		j++;
	}
	*length = cache[j] - '0' + (cache[j + 2] - '0') / 10.0;  //将字符串末尾站点间的距离转换为浮点数
}
arc* initarc(char str[], float length)   //initarc函数用于初始化邻接表中的结点
{
	arc* p = (arc*)malloc(sizeof(arc));  //为结点分配内存
	if (!p) {
		puts("Memory allocation failed!");
		exit(EXIT_FAILURE);
	}
	p->next = NULL;   //初始化指向下一条邻接边的指针
	strcpy(p->NAME, str);  //拷贝站点名称
	p->dist = length;  //拷贝站点间的距离
	return p;   //返回该结点
}
int search(Graph g, char str[])  //search函数用于在图中查找指定站点的名称并返回其索引
{
	int i = 0;
	for (; i < g.numVertex; i++) {
		if (strcmp(g.adjlist[i].name, str) == 0) {  //如果找到指定站点名称
			return i;  //返回其索引
		}
	}
	return -1;  //如果没有找到指定站点名称，返回-1
}
void addarc(Graph* g, int index, arc* r)  //addarc函数用于在指定站点index的邻接表中添加新的边r
{
	g->adjlist[index].num++;  //相邻站点总数加1
	arc* p = g->adjlist[index].add;  //p指向index的邻接表的头结点
	while (1) {  //遍历邻接表，使p指向邻接表的最后一个结点
		if (!p->next) {
			break;
		}
		p = p->next;
	}
	p->next = r;  //将新的边r添加到邻接表的最后
}
void addvertex(Graph* g, char name[], arc* r)  //addvertex函数用于在图中添加新的顶点
{
	g->numVertex++;     //图的顶点数加1
	strcpy(g->adjlist[g->numVertex - 1].name, name);    //拷贝站点名称
	g->adjlist[g->numVertex - 1].num = 1;     //相邻站点总数初始化为1
	g->adjlist[g->numVertex - 1].add = r;     //将新的边r添加到新的顶点的邻接表的头结点
}
float* set_row_vector(Graph g, arc* p)  //set_row_vector函数用于将各站点的邻接表中的距离数据转换为一维距离向量
{
	float* row = (float*)malloc(sizeof(float) * g.numVertex);  //为距离向量分配内存
	if (!row) {   //内存分配失败
		puts("Memory allocation failed!");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < g.numVertex; i++) {    //初始化距离向量，将各个分量设为MAX_FLOAT
		row[i] = MAX_FLOAT;
	}
	while (p) {   //遍历邻接表，将邻接的边所对应的分量设为相应的距离
		row[search(g, p->NAME)] = p->dist;   //通过search函数找到站点名称对应的索引，并将对应分量设为相应的距离
		p = p->next;
	}
	return row;
}
int find_min(Graph g, bool* found, float* distance)  //find_min函数用于在未访问过的站点中找到当前距离最小的站点
{
	float min = MAX_FLOAT;   //初始化距离最小值MAX_FLOAT
	int index = -1;          //索引index初始化为-1
	for (int i = 0; i < g.numVertex; i++) {   //遍历所有站点
		if (!found[i] && distance[i] < min) {   //若该站点未访问过且距离小于当前最小值
			min = distance[i];   //更新最小值
			index = i;           //更新索引
		}
	}
	return index;
}
void Dijkstra(Graph g, int start, int end, int path[], float distance[])  //Dijkstra函数用于实现Dijkstra算法，找到从起点到终点的最短路径
{
	//found数组用于标记站点是否被访问过
	bool* found = (bool*)malloc(sizeof(bool) * g.numVertex);  //为found数组分配内存
	if (!found) {   //内存分配失败
		puts("Memory allocation failed!");
		exit(EXIT_FAILURE);
	}
	memset(found, false, sizeof(bool) * g.numVertex);        //初始化found数组为false，表示所有站点未被访问
	memset(path, -1, sizeof(int) * g.numVertex);             //初始化path数组为-1，表示所有站点的前驱站点未知
	//进行Dijkstra算法的第一次迭代
	float* row = set_row_vector(g, g.adjlist[start].add);    //获取起点的邻接表并转换为距离向量
	for (int i = 0; i < g.numVertex; i++) {   //遍历所有站点
		distance[i] = row[i];     //用距离向量初始化distance数组
	}
	found[start] = true;  //标记起点已被访问
	distance[start] = 0;  //将起点的距离设为0
	for (int i = 1; i < g.numVertex; i++) {    //进行Dijkstra算法的后续g.numVertex-1次迭代
		int index = find_min(g, found, distance);  //找到当前距离最小的站点并赋值给索引index
		found[index] = true;    //标记该站点已被访问
		row = set_row_vector(g, g.adjlist[index].add);  //获取该站点的邻接表并转换为距离向量
		for (int j = 0; j < g.numVertex; j++) {    //遍历所有站点
			if (!found[j] && distance[index] + row[j] < distance[j]) {   //如果当前站点未被访问且通过当前站点到达index站点的距离小于当前距离
				distance[j] = distance[index] + row[j];    //更新当前站点的距离
				path[j] = index;                //更新当前站点的前驱站点为index
			}
		}
	}
}
Stack* initstack(int capacity)  //initstack函数用于初始化顺序栈
{
	Stack* s = (Stack*)malloc(sizeof(Stack));   //为栈分配内存
	if (!s) {   //内存分配失败
		puts("Memory allocation failed!");
		exit(EXIT_FAILURE);
	}
	s->data = (int*)malloc(sizeof(int) * capacity);   //为栈的数据域分配内存
	if (!s->data) {  //内存分配失败
		free(s);
		puts("Memory allocation failed!");
		exit(EXIT_FAILURE);
	}
	s->top = -1;  //栈顶指针初始化为-1，表示栈为空
	return s;
}
void push(Stack* s, int index)    //push函数用于将元素压入栈中
{
	if (s->top >= MAX_VERTEX_NUM - 1) {   //如果栈已满
		puts("Stack is full!");
		exit(EXIT_FAILURE);
	}
	s->top++;      //栈顶指针加1
	s->data[s->top] = index;     //将元素压入栈中
}
int pop(Stack* s)     //pop函数用于将栈顶元素弹出并将其返回
{
	if (s->top == -1) {   //如果栈为空
		puts("Stack is empty!");
		exit(EXIT_FAILURE);
	}
	s->top--;    //栈顶指针减1
	return s->data[s->top + 1];   //返回弹出的元素
}
void printpath(Graph g, int path[], int start, int end, float distance)  //printpath函数用于打印从起点到终点的最短路径
{
	Stack* s = initstack(g.numVertex);   //初始化顺序栈
	int index = end;   //从终点开始，沿着前驱站点回溯到起点
	while (index != -1) {       //如果前驱站点不为-1，表示还未回溯至起点
		push(s, index);         //将当前站点压入栈中
		index = path[index];    //更新当前站点为前驱站点
	}
	printf("%s ", g.adjlist[start].name);    //打印起点名称
	while (s->top != -1) {    //连续弹出栈中的元素，直到栈为空
		printf("%s ", g.adjlist[pop(s)].name);   //打印弹出的站点名称
	}
	printf("%.2f\n", distance);   //打印从起点到终点的最短路径长度
}
int main()
{
	Graph g;
	g.numVertex = g.numArc = 0;   //初始化图的顶点数和边数为0
	char cache[MAX_ROW_NUM],  //cache为存储输入的每一行数据的缓存区
		tempname_1[MAX_STATION_NUM], tempname_2[MAX_STATION_NUM];  //tempname_1和tempname_2为存储站点名称的缓存区
	float temp_length;  //temp_length存储站点间的距离
	while (1) {
		getcache(cache);   //获取输入的每一行数据
		if (strcmp(cache, "END!") == 0) {   //如果输入为"END!"，则结束循环
			break;
		}
		g.numArc++;   //图的边数加1
		processrow(cache, tempname_1, tempname_2, &temp_length);   //处理输入的每一行数据
		arc* temp_1 = initarc(tempname_1, temp_length), * temp_2 = initarc(tempname_2, temp_length);   //初始化两个站点名称分别对应的结点
		if (search(g, tempname_1) != -1) {  //如果在图中已存在第一个站点
			addarc(&g, search(g, tempname_1), temp_2);  //在第一个站点的邻接表中添加第二个站点
		}
		else {  //如果在图中不存在第一个站点
			addvertex(&g, tempname_1, temp_2);  //在图中添加第一个站点并将第二个站点添加到第一个站点的邻接表中
		}
		if (search(g, tempname_2) != -1) {  //如果在图中已存在第二个站点
			addarc(&g, search(g, tempname_2), temp_1);  //在第二个站点的邻接表中添加第一个站点
		}
		else {  //如果在图中不存在第二个站点
			addvertex(&g, tempname_2, temp_1);  //在图中添加第二个站点并将第一个站点添加到第二个站点的邻接表中
		}
		//清空缓存区
		memset(cache, '\0', sizeof(cache));
		memset(tempname_1, '\0', sizeof(tempname_1));
		memset(tempname_2, '\0', sizeof(tempname_2));
	}
	char start_name[MAX_STATION_NUM], end_name[MAX_STATION_NUM];   //两个字符数组分别用于存储起点和终点的名称
	scanf("%s %s", start_name, end_name);   //输入起点和终点的名称
	int start = search(g, start_name), end = search(g, end_name);   //在图中查找起点和终点的索引
	//为distance和path数组分配内存
	float* distance = (float*)malloc(sizeof(float) * g.numVertex);
	int* path = (int*)malloc(sizeof(int) * g.numVertex);
	if (!distance || !path) {   //内存分配失败
		puts("Memory allocation failed!");
		exit(EXIT_FAILURE);
	}
	Dijkstra(g, start, end, path, distance);  //调用Dijkstra函数，找到从起点到终点的最短路径
	printpath(g, path, start, end, distance[end]);  //格式化输出从起点到终点的最短路径和对应的路径长度
	return 0;
}
//Your code end.
