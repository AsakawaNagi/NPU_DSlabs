#include <stdio.h>
#include <malloc.h>

typedef struct Triple{
    int i,j;
    int val;
}Triple;

typedef struct Matrix{
    Triple data[1000];
    int rows, cols, counts;// ����������������Ԫ�ظ���
}Matrix;

// ����Ԫ�����ĳ��λ�ò���Ԫ��
void insert(Matrix *m, int i, int j, int val,int k){
    m->data[k].i=i;
    m->data[k].j=j;
    m->data[k].val=val;
    m->counts++;
}

// �������
void CreateMatrix(Matrix *m, int t){
    // ��������� ��ⲻ��ѧ��д���ٱ���һ��Ѱ�����ֵ ���ǿ�ͷ�Ѿ�������
    for(int k=0;k<t;k++){
        int i,j,x;
        scanf("%d %d %d",&i,&j,&x);
        insert(m,i,j,x,k);
    }
}

// �����Ԫ������������
void Output(Matrix *m){
    for (int k=0;k<m->counts;k++){
        printf("%d %d %d\n",m->data[k].i,m->data[k].j,m->data[k].val);
    }
}

// �����ձ�
Matrix* CreateEmptyMatrix(){
    Matrix *m=(Matrix*)malloc(sizeof(Matrix));
    m->rows=0;
    m->cols=0;
    m->counts=0;
    return m;
}

void add(Matrix *m1, Matrix *m2, Matrix *m3) {
    // ��ʼ����������������
    m3->rows = m1->rows;
    m3->cols = m1->cols;

    int k1 = 0;  // ���� m1 ������
    int k2 = 0;  // ���� m2 ������
    int k3 = 0;  // д�� m3 ������

    // �ϲ���������ķ���Ԫ��
    while (k1 < m1->counts && k2 < m2->counts) {
        if (m1->data[k1].i < m2->data[k2].i) {  // m1 ��ǰԪ�ص��кŸ�С
            insert(m3, m1->data[k1].i, m1->data[k1].j, m1->data[k1].val, k3);
            k1++;
            k3++;
        }
        else if (m1->data[k1].i > m2->data[k2].i) {  // m2 ��ǰԪ�ص��кŸ�С
            insert(m3, m2->data[k2].i, m2->data[k2].j, m2->data[k2].val, k3);
            k2++;
            k3++;
        }
        else {  // �к���ͬ���Ƚ��к�
            if (m1->data[k1].j < m2->data[k2].j) {  // m1 ��ǰԪ�ص��кŸ�С
                insert(m3, m1->data[k1].i, m1->data[k1].j, m1->data[k1].val, k3);
                k1++;
                k3++;
            }
            else if (m1->data[k1].j > m2->data[k2].j) {  // m2 ��ǰԪ�ص��кŸ�С
                insert(m3, m2->data[k2].i, m2->data[k2].j, m2->data[k2].val, k3);
                k2++;
                k3++;
            }
            else {  // ���кž���ͬ���ϲ�ֵ
                int sum = m1->data[k1].val + m2->data[k2].val;
                if (sum != 0) {  // ����Ŵ洢
                    insert(m3, m1->data[k1].i, m1->data[k1].j, sum, k3);
                    k3++;
                }
                k1++;
                k2++;
            }
        }
    }

    // ����ʣ��δ������Ԫ�أ�m1 �� m2 �п�����ʣ�ࣩ
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
