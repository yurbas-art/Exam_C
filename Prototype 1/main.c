#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
 * Prototype 1
 * ------------
 * Программа демонстрирует работу с файлами и динамическими
 * массивами. Сначала генерируются случайные числа и записываются
 * в input.txt. Затем при чтении числа заменяются на слова
 * (если делятся на 5 или 7) и сохраняются в output.txt.
 * После этого из исходного набора формируется матрица и
 * вычисляются суммы её строк и столбцов.
 */

// Функция для создания файла со случайными числами.
// На вход принимается количество чисел, которые нужно
// сгенерировать и записать построчно в input.txt.
void create_input_file(int N) {
    FILE *file = fopen("input.txt", "w");
    if (file == NULL) {
        printf("Oshibka pri sozdanii input.txt\n");
        exit(1);
    }

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        // записываем числа от 1 до 100
        fprintf(file, "%d ", rand() % 100 + 1);
    }

    fclose(file);
}

// Читает числа из input.txt и пишет их в output.txt,
// заменяя значения, кратные 5 или 7, на соответствующие слова.
void process_numbers(int N) {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (input == NULL || output == NULL) {
        printf("Oshibka pri otkytii\n");
        exit(1);
    }

    int num;
    for (int i = 0; i < N; i++) {
        // читаем очередное число
        fscanf(input, "%d", &num);

        // проверяем кратность и выводим слово вместо числа
        if (num % 5 == 0 && num % 7 == 0) {
            fprintf(output, "PYATSEM");
        } else if (num % 5 == 0) {
            fprintf(output, "PYAT");
        } else if (num % 7 == 0) {
            fprintf(output, "SEM");
        } else {
            fprintf(output, "%d ", num);
        }
    }

    fclose(input);
    fclose(output);
}

// Формирует матрицу из чисел в input.txt и печатает
// её на экран вместе с суммами строк и столбцов.
void create_matrix_and_calculate_sums(int N, int M) {
    FILE *input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Osibka pri otkrytii faila input.txt\n");
        exit(1);
    }

    int total_numbers = N;
    int cols = M;
    // количество строк вычисляется исходя из числа элементов
    int rows = total_numbers / cols;
    if (total_numbers % cols != 0) {
        rows++;  // Если есть остаток, добавляем еще одну строку
    }

    // Выделяем память под матрицу
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    // Читаем числа из файла и заполняем матрицу
    int num, count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (count < total_numbers && fscanf(input, "%d", &num) == 1) {
                matrix[i][j] = num;
                count++;
            } else {
                matrix[i][j] = 0;  // Заполняем нулями, если чисел не хватает
            }
        }
    }

    fclose(input);

    // Выводим матрицу
    printf("Matrica %dx%d:\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Считаем суммы строк
    printf("\nSummy strok:\n");
    for (int i = 0; i < rows; i++) {
        int row_sum = 0;
        for (int j = 0; j < cols; j++) {
            row_sum += matrix[i][j];
        }
        printf("Stroka %d: %d\n", i + 1, row_sum);
    }

    // Считаем суммы столбцов
    printf("\nSummy stolbcov:\n");
    for (int j = 0; j < cols; j++) {
        int col_sum = 0;
        for (int i = 0; i < rows; i++) {
            col_sum += matrix[i][j];
        }
        printf("Stolbec %d: %d\n", j + 1, col_sum);
    }

    // Освобождаем память
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    clock_t start_time = clock();

    int N, M;
    printf("Vvedite kolichestvo N: ");
    scanf("%d", &N);
    printf("Vvedite kolichestvo stolbcov M: ");
    scanf("%d", &M);

    // Часть 1: Создание файла и обработка чисел
    create_input_file(N);
    process_numbers(N);

    // Часть 2: Создание матрицы и подсчет сумм
    create_matrix_and_calculate_sums(N, M);

    // Замер времени работы программы
    clock_t end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("\nVremya rabota programmy: %.6f секунд\n", time_spent);

    return 0;
}
