/*Вариант 2
Создать файл input.txt в который поместить 2 случайные матрицы, размера, заданного пользователем. Закрыть файл. Очистить массивы. 
Открыть input.txt файл и прочитать матрицы, произвести их перемножение и сложение (с помощью функций), вывести результат в файл output.txt. 
Найти номер минимального элемента в матрице 1 и найти количество нечетных чисел в ней. 
Найти матрицу с одинаковыми числами в строке или столбце Замерить время работы программы и вывести на экран.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//функция умнржения матриц
void multiplyMatrices(int **mat1, int **mat2, int **result, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[i][j] = 0;
            for (int k = 0; k < m; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}
//функция сложения матриц
void addMatrices(int **mat1, int **mat2, int **result, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}
//освобождение памяти
void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


int main() {
    srand(time(NULL));
    time_t t0 = time(0);
    int n, m;
    printf("Enter matrix size n*m: ");
    scanf("%d %d", &n, &m);

    FILE *f1 = fopen("input.txt", "wt");
    for (int k = 0; k < 2; k++) {     //запись каждой матрицы в файл
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fprintf(f1, "%d ", rand() % 10); //генерация матриц с числами от 0 до 9
            }
            fprintf(f1, "\n");
        }
        if (k == 0) fprintf(f1, "\n"); //если первая матрица была записана, то разделение двух матриц пробелом 
    }
    fclose(f1);

    f1 = fopen("input.txt", "rt");
    int **mat1 = (int **)malloc(sizeof(int *) * n); // выделение памяти для массивов
    int **mat2 = (int **)malloc(sizeof(int *) * n);
    int **result_mult = (int **)malloc(sizeof(int *) * n);
    int **result_add = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        mat1[i] = (int *)malloc(sizeof(int) * m);
        mat2[i] = (int *)malloc(sizeof(int) * m);
        result_mult[i] = (int *)malloc(sizeof(int) * m);
        result_add[i] = (int *)malloc(sizeof(int) * m);
    }
    //чтение матриц из файла
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fscanf(f1, "%d", &mat1[i][j]);
            }
        }
        if (k == 0) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    fscanf(f1, "%d", &mat2[i][j]);
                }
            }
        }
    }
    fclose(f1);

    multiplyMatrices(mat1, mat2, result_mult, n, m);
    addMatrices(mat1, mat2, result_add, n, m);

    f1 = fopen("output.txt", "wt");
    fprintf(f1, "Результат умножения матриц:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(f1, "%d ", result_mult[i][j]);
        }
        fprintf(f1, "\n");
    }
    fprintf(f1, "\nРезультат сложения матриц:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(f1, "%d ", result_add[i][j]);
        }
        fprintf(f1, "\n");
    }
    
    //поиск номера минимального элемента в матрице 1 
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) 
        {
            for (int x = j+1; x < n; x++){
                if (mat1[i][j] == mat1[i][k]){
                    printf("\nMATRIX1 HAS IDENTICAL NUMBERS AT: [%d, %d]\n", j, x);
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) 
        {
            for (int x = j+1; x < n; x++){
                if (mat2[i][j] == mat2[i][k]){
                    printf("\nMATRIX2 HAS IDENTICAL NUMBERS AT: [%d, %d]\n", j, x);
                }
            }
        }
    }
    
    //поиск кол-ва нечетных чисел в матрице 1
    int min = 999, ires = 0, jres = 0, fres = 0, count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) 
        {
            if (min > mat1[i][j]){
                min = mat1[i][j];
                ires = i;
                jres = j;
            }
            if(mat1[i][j] % 2 != 0){
                count += 1;
            }
        }
    }
    printf("\nirregular numbers count = %d\nminimum number = [%d,%d] = %d\n", count, ires+1, jres+1, mat1[ires][jres]);
    
    fclose(f1);
    free_matrix(mat1, n);
    free_matrix(mat2, n);
    free_matrix(result_mult, n);
    free_matrix(result_add, n);
    
    time_t t1 = time(0);
    double time_in_seconds = difftime(t1, t0);
    printf("Время выполнения программы: %f сек", time_in_seconds);
    
    return 0;
}
