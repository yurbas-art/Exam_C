#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

// программа с вводом размера матрицы; реализованы сложение, вычитание и умножение

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
                fprintf(input_file, "%lf ", (double)(rand() % 10 + 1));
            }
            fprintf(input_file, "\n");
        }
        if (k == 0) {
            fprintf(input_file, "\n");
        }
    }

    fclose(input_file);
}

double** multiply_matrices(double** matrix1, double** matrix2, int cols1, int rows1, int cols2, int rows2) {
    if (cols1 != rows2) {
        return NULL;
    }
    double** result = (double**)malloc(rows1 * sizeof(double*));
    if (result == NULL) {
        printf("Ошибка: не удалось выделить память под результат умножения.\n");
        exit(1);
    }
    for (int i = 0; i < rows1; i++) {
        result[i] = (double*)malloc(cols2 * sizeof(double));
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

double** plus_matrix(double** matrix1, double** matrix2, int rows, int cols) {
    double** result = (double**)malloc(rows * sizeof(double*));
    if (result == NULL) {
        printf("Ошибка: не удалось выделить память под результат сложения.\n");
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        result[i] = (double*)malloc(cols * sizeof(double));
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

double** minus_matrix(double** matrix1, double** matrix2, int rows, int cols) {
    double** result = (double**)malloc(rows * sizeof(double*));
    if (result == NULL) {
        printf("Ошибка: не удалось выделить память под результат вычитания.\n");
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        result[i] = (double*)malloc(cols * sizeof(double));
        if (result[i] == NULL) {
            printf("Ошибка: не удалось выделить память под строку результата [%d].\n", i);
            for (int k = 0; k < i; k++) {
                free(result[k]);
            }
            free(result);
            exit(1);
        }
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return result;
}

void write_matrix(FILE* output_file, double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(output_file, "%lf ", matrix[i][j]);
        }
        fprintf(output_file, "\n");
    }
}

void free_matrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

double** read_matrix(FILE* input_file, int rows, int cols) {
    double** matrix = (double**)malloc(rows * sizeof(double*));
    if (matrix == NULL) {
        printf("Ошибка: не удалось выделить память под указатели строк.\n");
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
        if (matrix[i] == NULL) {
            printf("Ошибка: не удалось выделить память под row %d.\n", i);
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            exit(1);
        }
        for (int j = 0; j < cols; j++) {
            if (fscanf(input_file, "%lf", &matrix[i][j]) != 1) {
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
    setlocale(LC_ALL, "");

    int rows, cols;
    printf("Введите количество строк: ");
    if (scanf("%d", &rows) != 1) {
        printf("Ошибка ввода.\n");
        return 1;
    }
    printf("Введите количество столбцов: ");
    if (scanf("%d", &cols) != 1) {
        printf("Ошибка ввода.\n");
        return 1;
    }

    generate_file_matrix(rows, cols);

    clock_t start = clock();

    FILE* input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        printf("Ошибка: не удалось открыть input.txt для чтения\n");
        return 1;
    }

    double** matrix1 = read_matrix(input_file, rows, cols);

    int c = fgetc(input_file);
    if (c != '\n') {
        ungetc(c, input_file);
    }

    double** matrix2 = read_matrix(input_file, rows, cols);

    fclose(input_file);

    double** sum_result = plus_matrix(matrix1, matrix2, rows, cols);
    double** diff_result = minus_matrix(matrix1, matrix2, rows, cols);

    double** mul_result = multiply_matrices(matrix1, matrix2, cols, rows, cols, rows);

    FILE* output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Ошибка: не удалось открыть output.txt для записи\n");
        free_matrix(matrix1, rows);
        free_matrix(matrix2, rows);
        free_matrix(sum_result, rows);
        free_matrix(diff_result, rows);
        if (mul_result != NULL) {
            free_matrix(mul_result, rows);
        }
        return 1;
    }

    fprintf(output_file, "Сумма матриц:\n");
    write_matrix(output_file, sum_result, rows, cols);
    fprintf(output_file, "\n");

    fprintf(output_file, "Разность матриц:\n");
    write_matrix(output_file, diff_result, rows, cols);
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
    free_matrix(diff_result, rows);
    if (mul_result != NULL) {
        free_matrix(mul_result, rows);
    }

    clock_t finish = clock();
    double elapsed = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Время выполнения программы: %.3f секунд\n", elapsed);

    return 0;
}
