#include "linearList.h"

node* insertTail(node* h, node* t)
{
    // 请在此添加代码，补全函数insertTail
    /********** Begin *********/
	if (!h) {     //如果链表为空
		h = t;   //将头指针指向新结点
    }
    else {
        node* p = h;
		while (p->next) {  //遍历链表直到找到最后一个结点
            p = p->next;
        }
		p->next = t;    //将新结点插入到链表的最后
    }
	return h;    //返回头指针
    /********** End **********/
}
void delNode(node* h, int e)
{
    //清在此添加代码，补全函数delNode
    /********** Begin *********/
	node* p = h;    //指针p指向头结点
	if (p->data == e) {   //如果头结点就是要删除的结点
		h = h->next;  //将头指针指向下一个结点
		free(p);  //释放头结点
        return;
    }
	while (p->next) {  //遍历链表
		if (p->next->data == e) {  //如果找到要删除的结点
			node* q = p->next;  //指针q指向要删除的结点
			p->next = p->next->next;  //将前一个结点的指针域指向要删除结点的下一个结点
			free(q);  //释放要删除的结点
            return;
        }
        p = p->next;
    }
	printf("error\n");  //如果没有找到要删除的结点
    /********** End **********/
}
