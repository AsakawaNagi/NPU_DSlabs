#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

// ������Ԫ��ṹ��
typedef struct Triple{
    int row, col;  // �кź��к�
    int value;     // Ԫ��ֵ
}Triple;

// ������Ԫ��ϡ�����ṹ��
typedef struct TSMatrix{
    Triple elements[500];  // ��������ʽ�洢��Ԫ��
    int rows, cols, non_zero_count;    // ����������������Լ�����Ԫ�ظ���
}TSMatrix;

// �������Ԫ�ص�ϡ�������
void insert(TSMatrix *matrix, int row, int col, int value, int index){
    matrix->elements[index].row = row;
    matrix->elements[index].col = col;
    matrix->elements[index].value = value;
    matrix->non_zero_count++;
}

// ����ϡ�����
void create_matrix(TSMatrix* matrix, int rows, int cols){
    matrix->rows = rows;
    matrix->cols = cols;
    int index = 0;
    while(1){
        int row, col, value;
        scanf("%d", &row); getchar();  // �����к�
        scanf("%d", &col); getchar();  // �����к�
        scanf("%d", &value);             // ����Ԫ��ֵ
        if(row == 0 && col == 0 && value == 0){  // ���������־Ϊ 0 0 0
            break;
        }
        insert(matrix, row, col, value, index);  // �������Ԫ��
        index++;
    }
}

// �����յ�ϡ�����
TSMatrix* create_empty_matrix(){
     TSMatrix *matrix = (TSMatrix*)malloc(sizeof(TSMatrix));
     if(matrix == NULL){
        printf("Out of space!\n");  // �ڴ����ʧ����ʾ
     }else{
        matrix->rows = 0;
        matrix->cols = 0;
        matrix->non_zero_count = 0;
        return matrix;
     }
}

// ���ϡ�����ķ���Ԫ��
void output_matrix(TSMatrix* matrix){
     for(int index = 0; index < matrix->non_zero_count; index++){
        printf("%d %d %d\n", matrix->elements[index].row, matrix->elements[index].col, matrix->elements[index].value);
     }
}

// ϡ��������
void multiply_matrices(TSMatrix* matrix1, TSMatrix* matrix2, TSMatrix* result_matrix){
    // ������ʱ�������ڴ洢�˻����
    TSMatrix* temp_matrix = create_empty_matrix();
    temp_matrix->rows = matrix1->rows;
    temp_matrix->cols = matrix2->cols;
    // ��ʼ����ʱ����Ϊ�����
    for(int i = 1, index = 0; i <= temp_matrix->rows; i++){
        for(int j = 1; j <= temp_matrix->cols; j++){
            insert(temp_matrix, i, j, 0, index);
            index++;
        }
    }
    // ����˻�
    for(int i = 0; i < matrix1->non_zero_count; i++){
        int row1 = matrix1->elements[i].row;
        int col1 = matrix1->elements[i].col;
        for(int j = 0; j < matrix2->non_zero_count; j++){
            int row2 = matrix2->elements[j].row;
            int col2 = matrix2->elements[j].col;
            if(col1 == row2){
                int product = (matrix1->elements[i].value) * (matrix2->elements[j].value);
                int index = (row1 - 1) * (temp_matrix->cols) + col2 - 1;
                temp_matrix->elements[index].value += product;
            }
        }
    }
    // ����ʱ�����еķ���Ԫ�ظ��Ƶ����������
    result_matrix->rows = temp_matrix->rows;
    result_matrix->cols = temp_matrix->cols;
    for(int i = 0, index = 0; i < temp_matrix->non_zero_count;){
        if(temp_matrix->elements[i].value != 0){
            result_matrix->elements[index].row = temp_matrix->elements[i].row;
            result_matrix->elements[index].col = temp_matrix->elements[i].col;
            result_matrix->elements[index].value = temp_matrix->elements[i].value;
            i++;
            index++;
            result_matrix->non_zero_count++;
        }else{
            i++;
        }
    }
}

int main(){
    // �����һ�������������������������ϡ�����
    int rows1, cols1;
    scanf("%d %d", &rows1, &cols1);
    TSMatrix* matrix1 = create_empty_matrix();
    create_matrix(matrix1, rows1, cols1);
    // ����ڶ��������������������������ϡ�����
    int rows2, cols2;
    scanf("%d %d", &rows2, &cols2);
    TSMatrix* matrix2 = create_empty_matrix();
    create_matrix(matrix2, rows2, cols2);
    // ����������󣬲�����˻�
    TSMatrix* result_matrix = create_empty_matrix();
    multiply_matrices(matrix1, matrix2, result_matrix);
    // ����˻�����
    output_matrix(result_matrix);
    return 0;
}
