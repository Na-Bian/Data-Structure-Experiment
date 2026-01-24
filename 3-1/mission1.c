//Your code begin.
//示例仅供参考，你也可以自行修改设计。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTEX_NUM 20     //图的最大顶点数
#define MAX_ROW_NUM 256       //每行读取的最大字符数
#define MAX_STATION_NUM 30    //每个站点名称的最大字符数
typedef enum bool      //自定义定义枚举类型bool，包含true和false
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
int main()
{
	Graph g;
	g.numVertex = g.numArc = 0;   //初始化图的顶点数和边数为0
	char cache[MAX_ROW_NUM],  //cache为存储输入的每一行数据的缓存区
		tempname_1[MAX_STATION_NUM], tempname_2[MAX_STATION_NUM];  //tempname_1和tempname_2为存储站点名称的缓存区
	int index = 0;  //index作为cache缓存区的索引
	float temp_length;  //temp_length存储站点间的距离
	while (1) {   //循环读取输入的每一行数据，直到输入"END!"
		while ((cache[index] = getchar()) != '\n' && cache[index] != EOF) {  //从标准输入读取数据
			index++;
		}
		cache[index] = '\0';   //在末尾添加结束符
		if (strcmp(cache, "END!") == 0) {  //如果输入为"END!"，则结束循环
			break;
		}
		g.numArc++;  //图的边数加1
		processrow(cache, tempname_1, tempname_2, &temp_length);  //处理输入的每一行数据
		arc* temp_1 = initarc(tempname_1, temp_length), * temp_2 = initarc(tempname_2, temp_length);  //初始化两个站点名称分别对应的结点
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
		index = 0;  //重置索引
		//清空缓存区
		memset(cache, '\0', sizeof(cache));
		memset(tempname_1, '\0', sizeof(tempname_1));
		memset(tempname_2, '\0', sizeof(tempname_2));
	}
	for (index = 0; index < g.numVertex; index++) {  //遍历图中的每个顶点
		if (g.adjlist[index].num > 2) {  //如果相邻站点总数大于2，即表示该站点为换乘站
			printf("%s %d\n", g.adjlist[index].name, g.adjlist[index].num);  //格式化输出换乘站名称和其相邻站点总数
		}
	}
	return 0;
}
//Your code end.
