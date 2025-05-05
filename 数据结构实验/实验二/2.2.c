#include <stdio.h>
#include <malloc.h>

typedef struct Triple{
    int i,j;
    int val;
}Triple;

typedef struct Matrix{
    Triple data[1000];
    int rows, cols, counts;// 行数，列数，非零元素个数
}Matrix;

// 在三元组表里某个位置插入元素
void insert(Matrix *m, int i, int j, int val,int k){
    m->data[k].i=i;
    m->data[k].j=j;
    m->data[k].val=val;
    m->counts++;
}

// 填充数据
void CreateMatrix(Matrix *m, int t){
    // 我这里改了 理解不了学长写的再遍历一遍寻找最大值 不是开头已经给了吗
    for(int k=0;k<t;k++){
        int i,j,x;
        scanf("%d %d %d",&i,&j,&x);
        insert(m,i,j,x,k);
    }
}

// 输出三元组表里面的数据
void Output(Matrix *m){
    for (int k=0;k<m->counts;k++){
        printf("%d %d %d\n",m->data[k].i,m->data[k].j,m->data[k].val);
    }
}

// 创建空表
Matrix* CreateEmptyMatrix(){
    Matrix *m=(Matrix*)malloc(sizeof(Matrix));
    m->rows=0;
    m->cols=0;
    m->counts=0;
    return m;
}

void add(Matrix *m1, Matrix *m2, Matrix *m3) {
    // 初始化结果矩阵的行列数
    m3->rows = m1->rows;
    m3->cols = m1->cols;

    int k1 = 0;  // 遍历 m1 的索引
    int k2 = 0;  // 遍历 m2 的索引
    int k3 = 0;  // 写入 m3 的索引

    // 合并两个矩阵的非零元素
    while (k1 < m1->counts && k2 < m2->counts) {
        if (m1->data[k1].i < m2->data[k2].i) {  // m1 当前元素的行号更小
            insert(m3, m1->data[k1].i, m1->data[k1].j, m1->data[k1].val, k3);
            k1++;
            k3++;
        }
        else if (m1->data[k1].i > m2->data[k2].i) {  // m2 当前元素的行号更小
            insert(m3, m2->data[k2].i, m2->data[k2].j, m2->data[k2].val, k3);
            k2++;
            k3++;
        }
        else {  // 行号相同，比较列号
            if (m1->data[k1].j < m2->data[k2].j) {  // m1 当前元素的列号更小
                insert(m3, m1->data[k1].i, m1->data[k1].j, m1->data[k1].val, k3);
                k1++;
                k3++;
            }
            else if (m1->data[k1].j > m2->data[k2].j) {  // m2 当前元素的列号更小
                insert(m3, m2->data[k2].i, m2->data[k2].j, m2->data[k2].val, k3);
                k2++;
                k3++;
            }
            else {  // 行列号均相同，合并值
                int sum = m1->data[k1].val + m2->data[k2].val;
                if (sum != 0) {  // 非零才存储
                    insert(m3, m1->data[k1].i, m1->data[k1].j, sum, k3);
                    k3++;
                }
                k1++;
                k2++;
            }
        }
    }

    // 处理剩余未遍历的元素（m1 或 m2 中可能有剩余）
    while (k1 < m1->counts) {
        insert(m3, m1->data[k1].i, m1->data[k1].j, m1->data[k1].val, k3);
        k1++;
        k3++;
    }
    while (k2 < m2->counts) {
        insert(m3, m2->data[k2].i, m2->data[k2].j, m2->data[k2].val, k3);
        k2++;
        k3++;
    }
}
int main() {
    int m,n,t1,t2;
    scanf("%d %d %d %d",&m,&n,&t1,&t2);
    Matrix* M1= CreateEmptyMatrix();
    Matrix* M2= CreateEmptyMatrix();
    Matrix* M3= CreateEmptyMatrix();

    CreateMatrix(M1,t1);
    CreateMatrix(M2,t2);

    add(M1,M2,M3);
    Output(M3);
    free(M1);
    free(M2);
    free(M3);
    return 0;
}
