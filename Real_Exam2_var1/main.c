/*
 * Var 1
 * ------------
 * 1. Считывает дату из input.txt и рассчитывает,
 *    сколько дней осталось до неё.
 * 2. Генерирует квадратные матрицы из случайных чисел.
 * 3. Создаёт матрицы до тех пор, пока не встретятся две
 *    с одинаковой суммой элементов, после чего выводит
 *    их в output.txt.
 * 4. В конце выводится время работы программы.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// создаёт квадратную матрицу m x m
// и заполняет её числами от 0 до 9
int** generateMatrix(int m) {
    int** matrix = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        matrix[i] = (int*)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

// возвращает сумму всех элементов матрицы
int sum_matrix(int** matrix, int m) {
    int sum = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

// печатает матрицу в указанный файл
void write_matrix(int** matrix, int m, FILE *file) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
}

// освобождает память, выделенную под матрицу
void free_matrix(int** matrix, int m) {
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// точка входа программы
int main() {
    system("chcp 65001 > nul");
    srand(time(NULL));

    time_t t0 = time(0);

    FILE *f1 = fopen("input.txt", "rt"); //открываем файл и считываем дату
    int day, month, year;
    fscanf(f1, "%d %d %d", &day, &month, &year);

    time_t now;
    struct tm *current_time; //получаем текущее время
    time(&now);
    current_time = localtime(&now); //конвертация текущего времени в структуру tm

    struct tm file_time; // создание структуры tm для записи в нее даты из файла
    file_time.tm_mday = day;
    file_time.tm_mon = month - 1;
    file_time.tm_year = year - 1900;

    time_t current_timerec = mktime(current_time); //восстановление полной даты
    time_t file_timerec = mktime(&file_time); //преобразование даты в формат time_t

    double difference = difftime(file_timerec, current_timerec); //разница в днях между текущей и датой из файла
    int days_difference = difference/(60*60*24);
    printf("До указанной даты осталось %d дней\n", days_difference);

    fclose(f1);

    int m;
    printf("Введите размер массива: ");
    scanf("%d", &m);

    int** mass1 = generateMatrix(m);
    printf("Сумма элементов матрицы 1: %d\n\n", sum_matrix(mass1, m));
    FILE *file = fopen("output.txt", "wt");
    write_matrix(mass1, m, file);

    int** mass2 = generateMatrix(m);
    printf("Сумма элементов матрицы 2: %d\n\n", sum_matrix(mass2, m));
    write_matrix(mass2, m, file);

    while (sum_matrix(mass1, m) != sum_matrix(mass2, m)) {
        free_matrix(mass1, m);
        free_matrix(mass2, m);

        mass1 = generateMatrix(m);
        printf("Сумма элементов матрицы 1: %d\n\n", sum_matrix(mass1, m));
        write_matrix(mass1, m, file);

        mass2 = generateMatrix(m);
        printf("Сумма элементов матрицы 2: %d\n\n", sum_matrix(mass2, m));
        write_matrix(mass2, m, file);
    }
    fclose(file);
    free_matrix(mass1, m);
    free_matrix(mass2, m);

    time_t t1 = time(0);
    double time_in_seconds = difftime(t1, t0);
    printf("Время выполнения программы: %f сек\n", time_in_seconds);

    return 0;
}
