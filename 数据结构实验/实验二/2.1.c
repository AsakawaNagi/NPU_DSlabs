//Sparse matrix transpose
#include <stdio.h>
#include <string.h>
#define MAX 100
typedef struct
{
    int rol;
    int col;
    int e;
}triple;
typedef struct
{
    triple data[MAX+1];
    int m,n,len;//行数，列数，非零元个数
}tsm;
void getinfo(tsm *A)
{
    A->m=0;A->n=0;
    int e,f;
    scanf("%d %d",&e,&f);
    A->m=e;
    A->n=f;
    int i;
    for(i=0;;i++)
    {
        int a,b,c;
        //A->data[i]={0};
        scanf("%d",&a);
        getchar();
        scanf("%d",&b);
        getchar();
        scanf("%d",&c);
        if(a==0&&b==0&&c==0) break;
            //scanf("%d %d %d",&a,&b,&c);
        else
        {
            A->data[i].rol=a;
            A->data[i].col=b;
            A->data[i].e=c;
        }

        //if(a==0&&b==0&&c==0)
        //break;
    }
    A->len=i;
}//注意不要随便给输入函数加东西
void seq(tsm *A)
{
    for(int j=0;j<A->len-1;j++)
        for (int i=0;i<A->len-1;i++)
        {
            if(A->data[i].rol>=A->data[i+1].rol&&A->data[i].col>A->data[i+1].col)
            {
                int temp=A->data[i].col;
                A->data[i].col=A->data[i+1].col;
                A->data[i+1].col=temp;
                temp=A->data[i].rol;
                A->data[i].rol=A->data[i+1].rol;
                A->data[i+1].rol=temp;
                temp=A->data[i].e;
                A->data[i].e=A->data[i+1].rol;
                A->data[i+1].e=temp;
            }
        }
}
void transpose(tsm *A,tsm *B)
{
    int i,j,k;
    B->m=A->n;B->n=A->m;
    B->len=A->len;
    if(B->len>0)
    {
        j=0;
        //for(k=1;k<=A->n;k++)
        for(i=0;i<A->len;i++)
        {
            B->data[j].rol=A->data[i].col;
            B->data[j].col=A->data[i].rol;
            B->data[j].e=A->data[i].e;
            j++;
        }
    }
}
void fastransposition ()
{
    int col,t,p,q;
    int num[MAX],position[MAX];
}
void print(tsm *B)
{
    //printf("ok!!\n");
    for(int i=0;i<B->len;i++)
    {
        printf("%d %d %d\n",B->data[i].rol,B->data[i].col,B->data[i].e);
    }
}
int main()
{
    tsm *A,*B,A1,B1;
    A=&A1;B=&B1;
    //记住初始化，虽然我也不知道为啥要这么做，但是就不会出现一些奇怪的错误
    getinfo(A);
    transpose(A,B);
    seq(B);
    print(B);
    //print(A);
    return 0;
}
