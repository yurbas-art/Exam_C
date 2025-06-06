#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Prototype 2
 * ------------
 * Сначала создаются две матрицы случайных чисел и записываются
 * в файл input.txt. Далее матрицы читаются обратно, выполняется
 * их умножение и сложение, а результаты сохраняются в output.txt.
 * В конце выводится время работы программы.
 */

//•Создать файл input.txt в который поместить 2 случайные матрицы размера,
// заданного пользователем с консоли. Закрыть файл. Отчистить массивы.
// Открыть input.txt файл и прочитать матрицы, произвести их перемножение и
// сложение (с помощью своих функций) вывести результат в файл output.txt
// замерить время работы программы и вывести на экран.


// заполняет переданную матрицу случайными числами
void generate_random_matrix(int** matrix, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            matrix[i][j] = rand() % 10 + 1;
        }
    }
}

// перемножение двух матриц
int** multiply_matrices(int** matrix1, int** matrix2, int cols1, int rows1, int cols2, int rows2){
    if (cols1 != rows2){
        return NULL;
    }
    int** result = (int**)malloc(rows1 * sizeof(int*));
    for (int i = 0; i < rows1; i++){
        result[i] = (int*)malloc(cols2 * sizeof(int));
        for (int j = 0; j < cols2; j++){
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

// сложение двух матриц одинакового размера
int** plus_matrix(int** matrix1, int** matrix2, int rows, int cols){
    int** result = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++){
        result[i] = (int*) malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++){
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return result;
}

// освобождение памяти, выделенной под матрицу
void free_matrix(int** matrix, int rows){
    for (int i = 0; i < rows; i++){
        free(matrix[i]);
    }
    free(matrix);
}

// запись матрицы в файл
void write_files(FILE *input_file, int** matrix, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            fprintf(input_file,"%d ", matrix[i][j]);
        }
        fprintf(input_file, "\n");
    }
}

// чтение матрицы из файла
int** read_matrix(FILE *input_file, int rows, int cols){
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++){
        matrix[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++){
            fscanf(input_file,"%d",&matrix[i][j]);
        }
    }
    return matrix;
}

// точка входа: запрашивает размеры матриц, выполняет
// запись/чтение и выводит результаты операций
int main(){
    clock_t start = clock();
    srand(time(NULL));

    int rows1, cols1, rows2, cols2;

    printf("Vvedite kolichestvo strok i stolbcov pervoi matricy:");
    scanf("%d %d", &rows1, &cols1);

    printf("Vvedite kolichestvo strok i stolbcov vtoroi matricy:");
    scanf("%d %d", &rows2, &cols2);

    int** matrix1 = (int**)malloc(rows1 * sizeof(int*));
    for (int i = 0; i < rows1; i++){
        matrix1[i] = (int*)malloc(cols1 * sizeof(int));
    }

    int** matrix2 = (int**)malloc(rows2 * sizeof(int*));
    for (int i = 0; i < rows2; i++){
        matrix2[i] = (int*)malloc(cols2 * sizeof(int));
    }

    generate_random_matrix(matrix1, rows1, cols1);
    generate_random_matrix(matrix2, rows2, cols2);

    FILE *input_file = fopen("input.txt", "w");
    if (input_file == NULL){
        printf("Oshibka otkritia fila");
        exit(1);
    }

    fprintf(input_file,"%d %d\n", rows1, cols1);
    write_files(input_file, matrix1, rows1, cols1);

    fprintf(input_file,"%d %d\n", rows2, cols2);
    write_files(input_file, matrix2, rows2, cols2);

    fclose(input_file);
    free_matrix(matrix1, rows1);
    free_matrix(matrix2, rows2);

    input_file = fopen("input.txt", "r");
    if (input_file == NULL){
        printf("Oshibka otkritia fila");
        exit(1);
    }

    fscanf(input_file, "%d %d", &rows1, &cols1);
    matrix1 = read_matrix(input_file, rows1, cols1);

    fscanf(input_file, "%d %d", &rows2, &cols2);
    matrix2 = read_matrix(input_file, rows2, cols2);

    fclose(input_file);

    FILE *output_file = fopen("output.txt", "w");
    if (output_file == NULL){
        printf("Oshibka otkritia fila");
        exit(1);
    }

    if (cols1 == rows2){
        int** product = multiply_matrices(matrix1, matrix2, cols1, rows1, cols2, rows2);
        fprintf(output_file, "Rezultat umnozhenia matric:\n");
        write_files(output_file, product, rows1, cols2);
        free_matrix(product, rows1);
    } else {
        fprintf(output_file, "Umnozhenie matric nevozmozhno: nesovmestimye razmery\n");
    }

    if (rows1 == rows2 && cols1 == cols2){
        int** sum = plus_matrix(matrix1, matrix2, rows1, cols1);
        fprintf(output_file, "\nRezultat slozhenia matric:\n");
        write_files(output_file, sum, rows1, cols1);
        free_matrix(sum, rows1);
    } else {
        fprintf(output_file, "\nSlozhenie matric nevozmozhno: raznie razmery\n");
    }

    fclose(output_file);
    free_matrix(matrix1, rows1);
    free_matrix(matrix2, rows2);

    clock_t end = clock();
    double time_result = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Programma vipolnena za %.4f sekund\n", time_result);

    return 0;
}
