#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct DNode
{
    int data;
    struct DNode *prior, *next;
} DNode, *DoubleList;


void getInput(int *n);//输入
int computeTermN(int n);//计算精度
DoubleList computePi(DoubleList PI, int k);//计算pi
void createDLList(DoubleList *L, int k);//创建长度为k的双向链表L并全部初始为0
DoubleList bigSum(DoubleList L1, DoubleList L2);//大数加法，并将结果返回至L1
DoubleList bigDiv(DoubleList L, DoubleList result, int k);//大数除法，并将结果返回至result
DoubleList bigMul(DoubleList L, DoubleList result, int k);//大数乘法，并将结果返回至result
void printDLList(DoubleList L, int k);//输出链表


int main()
{

    int n;//小数点后位数
    int k;//计算次数

    ///1.输入
    getInput(&n);

    ///2.计算精度
    k = computeTermN(n);

    ///3.计算pi
    DoubleList PI;
    createDLList(&PI, k);
    computePi(PI, k);

    ///4.输出pi
    printDLList(PI, n);

    ///5.释放节点
    free(PI);

    return 0;
}

void getInput(int *n)
{
    scanf("%d", n);
}

int computeTermN(int n)//计算精度，具体为什么我也不知道
{
    int k;
    double i, sum = 0;

    for(i = 1; sum <= n + 1; i++)
    {
        sum = sum + log10((2 * i + 1) / i);
    }
    k = i + 20;

    return k;
}


DoubleList computePi(DoubleList PI, int k)
{//求和公式：2*Σn!/(2n+1)!!
    DoubleList L, R;
    createDLList(&L, k);
    createDLList(&R, k);

    double i;
    PI->next->data = 2;//初始化为2*1
    R->next->data = 2;//从第二项开始，第一项初始化为2*1
    for(i = 1; i < k; i++)
    {
        bigMul(R, L, i);//r = r * i，结果在L中
        bigDiv(L, R, (2 * i + 1));//r = r * i / (2 * i + 1)，结果在R中
        bigSum(PI, R);//pi = pi + r，结果在PI中
    }

    free(L);
    free(R);

    return PI;
}

void createDLList(DoubleList *L, int k)
{
    DoubleList q, s;
    int i;

    *L = (DoubleList)malloc(sizeof(DNode));
    (*L)->prior = *L;
    (*L)->next = *L;

    q = *L;
    for(i = 0; i < k; i++)//创建k个链表结点，并全部置为0
    {
        s = (DoubleList)malloc(sizeof(DNode));
        s->data = 0;
        q->next = s;
        s->next = *L;
        s->prior = q;
        (*L)->prior = s;
        q = s;
    }
}

DoubleList bigSum(DoubleList L1, DoubleList L2)
{
    DoubleList p, q;
    int carry = 0;
    p = L1->next;
    q = L2->next;

    while(p != L1 && q != L2)//每一位相加
    {
        p->data = p->data + q->data;//相加
        p = p->next;//指向下一个结点
        q = q->next;//同上
    }

    p = L1->prior;
    while(p != L1)//从尾结点开始，每一位往前依次进位
    {
        p->data = p->data + carry;//加上进位
        carry = p->data / 10;//计算进位
        p->data = p->data % 10;//计算当前位
        p = p->prior;//指向前一个结点
    }
    return L1;
}

DoubleList bigMul(DoubleList L, DoubleList result, int k)
{
    DoubleList p, q;
    int carry = 0;
    p = L->next;
    q = result->next;

    while(p != L && q != result)//每位乘k
    {
        q->data = p->data * k;
        p = p->next;
        q = q->next;
    }

    q = result->prior;
    while(q != result)//从尾结点开始,依次往前进位
    {
        q->data = q->data + carry;
        carry = q->data / 10;
        q->data = q->data % 10;
        q = q->prior;
    }
    return result;
}

DoubleList bigDiv(DoubleList L, DoubleList result, int k)//大数除法
{
    int num;
    DoubleList p, q;
    p = L->next;
    q = result->next;
    num = 0;

    while(q != result)
    {
        num = num + p->data;
        while(num < k)//如果不能除，则继续往后取数
        {
            q->data = 0;
            q = q->next;
            p = p->next;
            num = num * 10 + p->data;
            if(q == result)//如果已经到达最后一个结点，则返回
            {
                return result;
            }
        }
        q->data = num / k;
        q = q->next;
        p = p->next;
        num = (num % k) * 10;
    }
    return result;
}

void printDLList(DoubleList L, int k)
{
    DoubleList p;
    int i;

    p = L->next;
    printf("%d", p->data);
    p = p->next;

    printf(".");//打印小数点
    for(i = 0; i < k; i++)//打印小数点后k位
    {
        printf("%d", p->data);
        p = p->next;
    }
    printf("\n");
}

