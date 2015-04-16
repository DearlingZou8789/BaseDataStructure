#include <stdio.h>
#include <structtype.h>

/*二叉树的二叉链表结点结构定义*/
typedef struct BiTNode  //结点结构
{
    int data;           //结点数据
    struct BiTNode *lchild, *rchild;//左右孩子指针
}BiTNode, *BiTree;

/*斐波那契查找，F为[0,1,1,2,3,5,8,13,21,34,...]*/
int Fibonacci_Search(int *a, int n, int key)
{
    int low, high, mid, i, k;
    low = 1;    //定义最低下标为记录首位
    high = n;   //定义最高下标为记录末位
    k = 0;
    while (n>F[k]-1)    //计算n位于斐波那契数列的位置
        k++;
    for (i=n; i<F[k]-1; i++) //将不满的数值补全
        a[i] = a[n];

    while (low<=high)
    {
        mid = low + F[k-1] - 1; //计算当前分隔的下标
        if (key<a[mid])         //若查找记录小于当前分隔记录
        {
            high = mid - 1;     //最高下标调整到分隔下标mid-1处
            k = k - 1;
        }
        else if (key>a[mid])    //若查找记录大于当前分隔记录
        {
            low = mid + 1;      //最低小标调整到分隔下标mid+1处
            k = k - 2;          //斐波那契数列下标减两位
        }
        else
            {
                if (mid<=n)
                    return mid; //若相等则说明mid即为查找到的位置
                else
                    return n;   //若mid>n说明是补全数值,返回
            }
    }
    return 0;
}

/*二叉排序树查找算法
  递归查找二叉排序树T中是否存在key
  指针f指向T的双亲，其初始调用至为NULL
  若查找成功，则指针p指向该数据元素结点，并返回TRUE
  否则指针p指向查找路径上访问的最后一个结点并返回FALSE
*/
Status SearchBSF(BiTree T, int key, BiTree f, BiTree *p)
//T是二叉树链表，f为指向T的双亲，p返回查找到的位置
{
    if (!T)                 //查找不成功
    {
        *p = f;
        return FALSE;
    }
    else if (key==T->data)  //查找成功
    {
        *p = T;
        return TRUE:
    }
    else if (key<T->data)
        return SearchBSF(T->lchild, key, T, p)  //在左子树继续查找
    else
        return  SearchBSF(T->rchild, key, T, p); //在右字数继续查找

}

/*二叉排序树插入操作
 当二叉排序树T中不存在关键字等于key的数据元素时，
 插入key并返回TRUE，否则返回FALSE
 */
Status insertBST(BiTree *T, int key)
{
    BiTree p, s;
    if (!SearchBSF(*T, key, NULL, &p)) //查找不成功
    {
        s = (BiTree)calloc(1, sizeof(BiTNode));
        s->data = key;
        s->lchild = s->rchild = NULL;
        if (!p)
        {
            *T = s; //插入s为新的根结点
        }
        else if (key<p->data)
        {
            p->lchild = s;  //插入s为左孩子
        }
        else
        {
            p->rchild = s;  //插入s为有孩子
        }
        return TRUE;
    }
    else
        return FALSE;   //树中已有关键字相同的结点，不在插入
}
