#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

//здесь нет реализации операции вычитания

void generate_file_matrix(int rows, int cols) {
    FILE *input_file = fopen("input.txt", "w");
    if (input_file == NULL) {
        printf("Ошибка создания файла input.txt\n");
        exit(1);
    }

    srand((unsigned)time(NULL));
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                fprintf(input_file, "%d ", rand() % 10 + 1);
            }
            fprintf(input_file, "\n");
        }
        if (k == 0) {
            fprintf(input_file, "\n");
        }
    }

    fclose(input_file);
}

int** multiply_matrices(int** matrix1, int** matrix2, int cols1, int rows1, int cols2, int rows2) {
    if (cols1 != rows2) {
        return NULL;
    }
    int** result = (int**)malloc(rows1 * sizeof(int*));
    if (result == NULL) {
        printf("Ошибка: не удалось выделить память под результат умножения.\n");
        exit(1);
    }
    for (int i = 0; i < rows1; i++) {
        result[i] = (int*)malloc(cols2 * sizeof(int));
        if (result[i] == NULL) {
            printf("Ошибка: не удалось выделить память под строку результата [%d].\n", i);
            for (int k = 0; k < i; k++) {
                free(result[k]);
            }
            free(result);
            exit(1);
        }
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

int** plus_matrix(int** matrix1, int** matrix2, int rows, int cols) {
    int** result = (int**)malloc(rows * sizeof(int*));
    if (result == NULL) {
        printf("Ошибка: не удалось выделить память под результат сложения.\n");
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        result[i] = (int*)malloc(cols * sizeof(int));
        if (result[i] == NULL) {
            printf("Ошибка: не удалось выделить память под строку результата [%d].\n", i);
            for (int k = 0; k < i; k++) {
                free(result[k]);
            }
            free(result);
            exit(1);
        }
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return result;
}

void write_matrix(FILE* output_file, int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(output_file, "%d ", matrix[i][j]);
        }
        fprintf(output_file, "\n");
    }
}

void free_matrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int** read_matrix(FILE* input_file, int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        printf("Ошибка: не удалось выделить память под указатели строк.\n");
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Ошибка: не удалось выделить память под row %d.\n", i);
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            exit(1);
        }
        for (int j = 0; j < cols; j++) {
            if (fscanf(input_file, "%d", &matrix[i][j]) != 1) {
                printf("Ошибка: недостаточно чисел в файле при чтении элемента [%d][%d].\n", i, j);
                for (int k = 0; k <= i; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                exit(1);
            }
        }
    }
    return matrix;
}

int main() {
    system("chcp 65001 > nul");

    int rows, cols;
    rows = cols = 3;

    generate_file_matrix(rows, cols);

    clock_t start = clock();

    FILE* input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        printf("Ошибка: не удалось открыть input.txt для чтения\n");
        return 1;
    }

    int** matrix1 = read_matrix(input_file, rows, cols);

    int c = fgetc(input_file);
    if (c != '\n') {
        ungetc(c, input_file);
    }

    int** matrix2 = read_matrix(input_file, rows, cols);

    fclose(input_file);

    int** sum_result = plus_matrix(matrix1, matrix2, rows, cols);

    int** mul_result = multiply_matrices(matrix1, matrix2, cols, rows, cols, rows);

    FILE* output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Ошибка: не удалось открыть output.txt для записи\n");
        free_matrix(matrix1, rows);
        free_matrix(matrix2, rows);
        free_matrix(sum_result, rows);
        if (mul_result != NULL) {
            free_matrix(mul_result, rows);
        }
        return 1;
    }

    fprintf(output_file, "Сумма матриц:\n");
    write_matrix(output_file, sum_result, rows, cols);
    fprintf(output_file, "\n");

    if (mul_result != NULL) {
        fprintf(output_file, "Произведение матриц:\n");
        write_matrix(output_file, mul_result, rows, cols);
    } else {
        fprintf(output_file, "Произведение матриц невозможно: несоответствие размерностей.\n");
    }

    fclose(output_file);

    free_matrix(matrix1, rows);
    free_matrix(matrix2, rows);
    free_matrix(sum_result, rows);
    if (mul_result != NULL) {
        free_matrix(mul_result, rows);
    }

    clock_t finish = clock();
    double elapsed = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Время выполнения программы: %.3f секунд\n", elapsed);

    return 0;
}
