#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

// 定义三元组结构体
typedef struct Triple{
    int row, col;  // 行号和列号
    int value;     // 元素值
}Triple;

// 定义三元组稀疏矩阵结构体
typedef struct TSMatrix{
    Triple elements[500];  // 以数组形式存储三元组
    int rows, cols, non_zero_count;    // 矩阵的行数、列数以及非零元素个数
}TSMatrix;

// 插入非零元素到稀疏矩阵中
void insert(TSMatrix *matrix, int row, int col, int value, int index){
    matrix->elements[index].row = row;
    matrix->elements[index].col = col;
    matrix->elements[index].value = value;
    matrix->non_zero_count++;
}

// 创建稀疏矩阵
void create_matrix(TSMatrix* matrix, int rows, int cols){
    matrix->rows = rows;
    matrix->cols = cols;
    int index = 0;
    while(1){
        int row, col, value;
        scanf("%d", &row); getchar();  // 输入行号
        scanf("%d", &col); getchar();  // 输入列号
        scanf("%d", &value);             // 输入元素值
        if(row == 0 && col == 0 && value == 0){  // 输入结束标志为 0 0 0
            break;
        }
        insert(matrix, row, col, value, index);  // 插入非零元素
        index++;
    }
}

// 创建空的稀疏矩阵
TSMatrix* create_empty_matrix(){
     TSMatrix *matrix = (TSMatrix*)malloc(sizeof(TSMatrix));
     if(matrix == NULL){
        printf("Out of space!\n");  // 内存分配失败提示
     }else{
        matrix->rows = 0;
        matrix->cols = 0;
        matrix->non_zero_count = 0;
        return matrix;
     }
}

// 输出稀疏矩阵的非零元素
void output_matrix(TSMatrix* matrix){
     for(int index = 0; index < matrix->non_zero_count; index++){
        printf("%d %d %d\n", matrix->elements[index].row, matrix->elements[index].col, matrix->elements[index].value);
     }
}

// 稀疏矩阵相乘
void multiply_matrices(TSMatrix* matrix1, TSMatrix* matrix2, TSMatrix* result_matrix){
    // 创建临时矩阵用于存储乘积结果
    TSMatrix* temp_matrix = create_empty_matrix();
    temp_matrix->rows = matrix1->rows;
    temp_matrix->cols = matrix2->cols;
    // 初始化临时矩阵为零矩阵
    for(int i = 1, index = 0; i <= temp_matrix->rows; i++){
        for(int j = 1; j <= temp_matrix->cols; j++){
            insert(temp_matrix, i, j, 0, index);
            index++;
        }
    }
    // 计算乘积
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
    // 将临时矩阵中的非零元素复制到结果矩阵中
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
    // 输入第一个矩阵的行数和列数，并创建稀疏矩阵
    int rows1, cols1;
    scanf("%d %d", &rows1, &cols1);
    TSMatrix* matrix1 = create_empty_matrix();
    create_matrix(matrix1, rows1, cols1);
    // 输入第二个矩阵的行数和列数，并创建稀疏矩阵
    int rows2, cols2;
    scanf("%d %d", &rows2, &cols2);
    TSMatrix* matrix2 = create_empty_matrix();
    create_matrix(matrix2, rows2, cols2);
    // 创建结果矩阵，并计算乘积
    TSMatrix* result_matrix = create_empty_matrix();
    multiply_matrices(matrix1, matrix2, result_matrix);
    // 输出乘积矩阵
    output_matrix(result_matrix);
    return 0;
}
