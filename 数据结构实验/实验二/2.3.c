#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

// ����ϡ������Ԫ������ ElemType Ϊ int
typedef int ElemType;

// ����ʮ��������Ľṹ��
typedef struct OLNode{
    int i, j;             // �кź��к�
    ElemType elem;        // Ԫ��ֵ
    struct OLNode *right; // ָ���ұߵĽ��
    struct OLNode *down;  // ָ���±ߵĽ��
}OLNode, *OLink;

// ����ʮ������Ľṹ��
typedef struct CrossList{
    OLink* rHead;  // ��ͷָ������
    OLink* cHead;  // ��ͷָ������
    int mu, nu, tu; // ���������������������Ԫ�ظ���
}CrossList;

// ����ϡ�����ĺ�����rΪ������cΪ������tΪ����Ԫ�ظ���
CrossList* CreateOLSMatrix(int r, int c, int t){
    CrossList* p = (CrossList*)malloc(sizeof(CrossList)); // �����ڴ�ռ�
    if(p == NULL){
        printf("Out of space!");
    }
    p->mu = r;
    p->nu = c;
    p->tu = t;
    p->rHead = (OLink*)malloc((r + 1) * sizeof(OLink)); // ������ͷָ�������ڴ�ռ�
    p->cHead = (OLink*)malloc((c + 1) * sizeof(OLink)); // ������ͷָ�������ڴ�ռ�
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

// ����Ԫ�ص�ϡ�����ĺ���
void InsertMatrix(CrossList* p, int i, int j, int elem){
    OLink p1 = (OLink)malloc(sizeof(OLNode)); // �������ڴ�ռ�
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

// ����ϡ�����ĺ������ӱ�׼�����ж�ȡ����Ԫ����Ϣ
int BuildMatrix(CrossList* p){
    for(int k = 1; k <= p->tu; k++){
        int i, j, elem;
        scanf("%d%d%d", &i, &j, &elem);
        InsertMatrix(p, i, j, elem);
    }
}

// ���ϡ�����ĺ���
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

// ϡ�����ӷ��ĺ���
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

// ������
int main(){
    int r, c, t1, t2;
    scanf("%d%d%d%d", &r, &c, &t1, &t2); // �ӱ�׼�����ж�ȡ��������������������ķ���Ԫ�ظ���
    CrossList* p1 = CreateOLSMatrix(r, c, t1); // ������һ��ϡ�����
    CrossList* p2 = CreateOLSMatrix(r, c, t2); // �����ڶ���ϡ�����
    CrossList* p3 = CreateOLSMatrix(r, c, t1 + t2); // �����������
    BuildMatrix(p1); // ������һ��ϡ�����
    BuildMatrix(p2); // �����ڶ���ϡ�����
    AddMatrix(p1, p2, p3); // ���о���ӷ�
    OutputMatrix(p3); // ����������
    return 0;
}
