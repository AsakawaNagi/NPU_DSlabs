#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

// 定义稀疏矩阵的元素类型 ElemType 为 int
typedef int ElemType;

// 定义十字链表结点的结构体
typedef struct OLNode{
    int i, j;             // 行号和列号
    ElemType elem;        // 元素值
    struct OLNode *right; // 指向右边的结点
    struct OLNode *down;  // 指向下边的结点
}OLNode, *OLink;

// 定义十字链表的结构体
typedef struct CrossList{
    OLink* rHead;  // 行头指针数组
    OLink* cHead;  // 列头指针数组
    int mu, nu, tu; // 矩阵的行数、列数、非零元素个数
}CrossList;

// 创建稀疏矩阵的函数，r为行数，c为列数，t为非零元素个数
CrossList* CreateOLSMatrix(int r, int c, int t){
    CrossList* p = (CrossList*)malloc(sizeof(CrossList)); // 分配内存空间
    if(p == NULL){
        printf("Out of space!");
    }
    p->mu = r;
    p->nu = c;
    p->tu = t;
    p->rHead = (OLink*)malloc((r + 1) * sizeof(OLink)); // 分配行头指针数组内存空间
    p->cHead = (OLink*)malloc((c + 1) * sizeof(OLink)); // 分配列头指针数组内存空间
    if(p->rHead == NULL || p->cHead == NULL)
        printf("Out of space!\n");
    for(int i = 0; i < r + 1; i++){
        p->rHead[i] = NULL;
    }
    for(int i = 0; i < c + 1; i++){
        p->cHead[i] = NULL;
    }
    return p;
}

// 插入元素到稀疏矩阵的函数
void InsertMatrix(CrossList* p, int i, int j, int elem){
    OLink p1 = (OLink)malloc(sizeof(OLNode)); // 分配结点内存空间
    if(p1 == NULL)
        printf("Out of space!\n");
    p1->i = i;
    p1->j = j;
    p1->elem = elem;
    if(p->rHead[i] == NULL || p->rHead[i]->j > j){
        p1->right = p->rHead[i];
        p->rHead[i] = p1;
    }else{
        OLink q = p->rHead[i];
        while(1){
            if(q->right == NULL || q->right->j > j) break;
            q = q->right;
        }
        p1->right = q->right;
        q->right = p1;
    }
    if(p->cHead[j] == NULL || p->cHead[j]->i > i){
        p1->down = p->cHead[j];
        p->cHead[j] = p1;
    }else{
        OLink q = p->cHead[j];
        while(1){
            if(q->down == NULL || q->down->i > i) break;
            q = q->down;
        }
        p1->down = q->down;
        q->down = p1;
    }
}

// 构建稀疏矩阵的函数，从标准输入中读取非零元素信息
int BuildMatrix(CrossList* p){
    for(int k = 1; k <= p->tu; k++){
        int i, j, elem;
        scanf("%d%d%d", &i, &j, &elem);
        InsertMatrix(p, i, j, elem);
    }
}

// 输出稀疏矩阵的函数
int OutputMatrix(CrossList* p){
    for(int i = 1; i <= p->mu; i++){
        OLink q = p->rHead[i];
        for(int j = 1; j <= p->nu; j++){
            if(q != NULL && j == q->j){
                printf("%d %d %d\n", q->i, q->j, q->elem);
                q = q->right;
            }
        }
    }
}

// 稀疏矩阵加法的函数
int AddMatrix(CrossList* p1, CrossList* p2, CrossList* p3){
    for(int i = 1; i <= p1->mu; i++){
        OLink temp1 = p1->rHead[i];
        OLink temp2 = p2->rHead[i];
        for(int j = 1; j <= p1->nu; j++){
            int flag1 = temp1 != NULL && j == temp1->j;
            int flag2 = temp2 != NULL && j == temp2->j;
            if(flag1 == 1 && flag2 != 1){
                InsertMatrix(p3, temp1->i, temp1->j, temp1->elem);
                temp1 = temp1->right;
            }
            if(flag1 != 1 && flag2 == 1){
                InsertMatrix(p3, temp2->i, temp2->j, temp2->elem);
                temp2 = temp2->right;
            }
            if(flag1 == 1 && flag2 == 1){
                int total = temp1->elem + temp2->elem;
                if(total == 0){
                    p3->tu = p3->tu - 2;
                }else if(total != 0){
                    InsertMatrix(p3, temp1->i, temp1->j, total);
                    p3->tu--;
                }
                temp1 = temp1->right;
                temp2 = temp2->right;
            }
        }
    }
}

// 主函数
int main(){
    int r, c, t1, t2;
    scanf("%d%d%d%d", &r, &c, &t1, &t2); // 从标准输入中读取行数、列数、两个矩阵的非零元素个数
    CrossList* p1 = CreateOLSMatrix(r, c, t1); // 创建第一个稀疏矩阵
    CrossList* p2 = CreateOLSMatrix(r, c, t2); // 创建第二个稀疏矩阵
    CrossList* p3 = CreateOLSMatrix(r, c, t1 + t2); // 创建结果矩阵
    BuildMatrix(p1); // 构建第一个稀疏矩阵
    BuildMatrix(p2); // 构建第二个稀疏矩阵
    AddMatrix(p1, p2, p3); // 进行矩阵加法
    OutputMatrix(p3); // 输出结果矩阵
    return 0;
}
