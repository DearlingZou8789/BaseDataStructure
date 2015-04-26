#include <stdio.h>
#include <structtype.h>

#define LH +1      //左高
#define EH 0        //等高
#define RH -1       //右高


/*二叉树的二叉链表结点结构定义*/
typedef struct BiTNode  //结点结构
{
    int data;           //结点数据
    struct BiTNode *lchild, *rchild;//左右孩子指针
    int bf;             //结点的平衡因子
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

/*二叉排序树删除操作
 * 若二叉排序书T中存在关键字等于key的数据元素是，则删除该数据元素结点。
 * 并返回TRUE,否则返回FALSE。
 */

Status DeleteBST(BiTree *T, int key)
{
    if (!*T)    //不存在关键字等于key的数据元素
        return FALSE;
    else
    {
        if (key == (*T)->data) //找到关键字等于key的数据元素
            return Delete(T);
        else if (key<(*T)->data)
            return DeleteBST(&(*T)->lchild, key);
        else
            return DeleteBST(&(*T)->rchild, key);
    }
}


/*从二叉排序树中删除结点p，并重接它的左或右子树*/
Status Delete(BiTree *p)
{
    BiTree q, s;
    if ( (*p)->rchild == NULL )  //右子树空则只需要重接它的左子树
    {
        q = *p;
        *p = (*p)->lchild;
        free(q);
    }
    else if ( (*p)->lchild == NULL )        //只需重接它的右子树
    {
        q = *p;
        *p = (*p)->rchild;
        free(q);
    }
    else        //左右子树均不为空
    {
        q = *p;
        s = (*p)->lchild;
        while (s->rchild)   //转左，然后向右到尽头（找待删结点的前驱）
        {
            q = s;
            s = s->rchild;
        }
        (*p)->data = s->data;       //s指向被删结点的直接前驱
        if (q!=*p)
            q->rchild = s->lchild;  //重接q的右子树
        else
            q->lchild = s->lchild;  //重接q的左子树
        free(s);
    }
    return TRUE;
 }

/*对以p为根的二叉排序树作右旋处理
 * 处理之后p指向新的树根结点，及旋转处理之前的左子树的根节点
 */
void R_Rotate(BiTree *p)
{
    BiTree L;
    L = (*p)->lchild;           //L指向p左子树根结点
    (*p)->lchild = L->rchild;   //L的右子树挂接为p的左子树
    L->rchild = (*p);
    *p = L;                     //p指向新的根结点
}

/*对以p为根的二叉排序树做左旋处理
 * 处理之后p指向新的树根节点，及旋转处理之前的右子树的根结点0
 */
void L_Rotate(BiTree *p)
{
    BiTree R;
    R = (*p)->rchild;       //R指向p右子树根结点
    (*p)->rchild = R->lchild;   //R的左子树挂接为p的右子树
    R->lchild = (*p);   
    *p = R;                //p指向新的根结点
}

/*对以指针T所指结点为根的二叉树作作做平衡旋转处理
 * 本算法结束是，指针T指向新的根结点
 */
void LeftBalance(BiTree *T)
{
    BiTree L, Lr;
    L = (*T)->lchild;       //L指向T的左子树根结点
    switch(L->bf)
    {
        //检查T的左子树的平衡度，并做相应平衡处理
        case LH:        //新结点插入在T的左孩子的左子树上，要作单右旋转处理
            (*T)->bf = L->bf = EH;
            R_Rotate(T);
            break;
        case RH:        //新节点插入在T的左孩子的右子树上，要作双旋处理
            Lr = L->rchild;     //Lr指向T的左孩子的右子树根
            switch(Lr->bf)  //修改T及其左子树的平衡因子
            {
                case LH:
                    (*T)->bf = RH;
                    L->bf = EH;
                    break;
                case EH:
                    (*T)->bf = L->bf = EH;
                    break;
                case RH:
                    (*T)->bf = EH;
                    L->bf = LH;
                    break;
            }
            Lr->bf = EH;
            L_Rotate(&(*T)->lchild);       //对T的左子树作左旋平衡处理
            R_Rotate(T);                    //对T作右旋平衡处理
    }
}

/*若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个
 * 数据元素为e的新结点并返回1，否则返回0.若因插入而是二叉排序树
 * 失去平衡，则作平衡旋转处理，布尔变量taller反应T长高与否
 */
Status InsertAVL(BiTree *T, int e, Status *taller)
{
    if (!*T)
    {
        //插入新结点，树长高，置taller为TRUE
        *T = (BiTree)malloc(sizeof(BiTNod));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = TRUE;
    }
    else
    {
        if (e == (*T)->data)
        {
            //树中已存在和e相同关键字的结点则不再插入
            *taller = FALSE;
            return FALSE;
        }
        if (e<(*T)->data)
        {
            //应继续在T的左子树中进行搜索
            if (!InsertAVL (&(*T)->lchild, e, taller))      //未插入
                return FALSE;
            if (taller)     //已插入到T的左子树中左子树长高
            {
                switch((*T)->bf)    //检查T的平衡度
                {
                    case LH:        //原本左子树比右子树高，需要做左平衡处理
                        LeftBalance(T);
                        *taller = FALSE:
                            break;
                    case EH:        //原本左右子树等高，现因左子树增高而树增高
                        (*T)->bf = LH;
                        *taller = TRUE;
                        break;
                    case RH:        //原本右子树比左子树高，现左右子树等高
                        (*T)->bf = EH;
                        *taller = FALSE;
                        break;
                }
            }
        }
        else
        {
            //应继续在T的右子树中进行搜索
            if (!InsertAVL(&(*T)->rchild, e, taller))           //未插入
            {
                return FALSE;
            }
            if (*taller)        //已插入到T的右子树且右子树长高
            {
                switch((*T)->bf)        //检查T的平衡度
                {
                    case LH:        //原本左子树比右子树高，现左，右子树等高
                        (*T)->bf = EH;
                        *taller = FALSE;
                        break;
                    case EH:        //原本左右子树等高，现因右子树增高而树增高
                        (*T)->bf = RH;
                        *taller = TRUE;
                        break;
                    case RH:        //原本右子树比左子树高，需要做右平衡处理
                        RightBalance(T);
                        *taller = FALSE;
                        break;
                }
            }
        }
    }
    return TRUE;
}
