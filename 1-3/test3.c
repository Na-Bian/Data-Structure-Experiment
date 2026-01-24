#include"tree.h"
int depth(Bitnode* t)
{
    //在这里输入代码
    /*******begin*****/
	if (t == NULL) return 0;  //空树的深度为0
	if (t->left == NULL && t->right == NULL) {  //t既没有左子树也没有右子树，说明t是叶子结点
		return 1;  //叶子结点的深度为1
	}
	if (t->left == NULL) {    //否则如果t没有左子树，t的深度为右子树的深度加1
		return 1 + depth(t->right);  //递归调用depth函数，计算右子树的深度
    }
	if (t->right == NULL) {   //否则如果t没有右子树，t的深度为左子树的深度加1
		return 1 + depth(t->left);  //递归调用depth函数，计算左子树的深度
    }
	//否则t既有左子树，又有右子树，t的深度为左子树和右子树深度的较大值加1
    return 1 + (depth(t->left) > depth(t->right) ? depth(t->left) : depth(t->right));
    /******end********/
}
