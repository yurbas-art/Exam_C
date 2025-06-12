#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Создание файла с N случайными числами
void create_numbers(const char *name, int n) {
    FILE *f = fopen(name, "w");
    if (!f) {
        printf("Не удалось создать %s\n", name);
        exit(1);
    }
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d\n", rand() % 100);
    }
    fclose(f);
}

// Чтение чисел из файла в массив
int *read_numbers(const char *name, int n) {
    FILE *f = fopen(name, "r");
    if (!f) {
        printf("Не удалось открыть %s\n", name);
        exit(1);
    }
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (fscanf(f, "%d", &a[i]) != 1) {
            printf("Неверный формат файла\n");
            fclose(f);
            free(a);
            exit(1);
        }
    }
    fclose(f);
    return a;
}

// Запись чисел в файл с заменой кратных 5 и 7
void write_replaced(const char *name, const int *a, int n) {
    FILE *f = fopen(name, "w");
    if (!f) {
        printf("Не удалось создать %s\n", name);
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        if (a[i] % 5 == 0 && a[i] % 7 == 0)
            fprintf(f, "ПЯТЬСЕМЬ\n");
        else if (a[i] % 5 == 0)
            fprintf(f, "ПЯТЬ\n");
        else if (a[i] % 7 == 0)
            fprintf(f, "СЕМЬ\n");
        else
            fprintf(f, "%d\n", a[i]);
    }
    fclose(f);
}

// Формирование квадратной матрицы из вектора
void build_matrix(const int *a, int n) {
    int m = (int)sqrt(n);           // размер стороны матрицы
    int used = m * m;               // сколько чисел будет использовано
    int **mat = malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        mat[i] = malloc(m * sizeof(int));
    }

    for (int i = 0, k = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            mat[i][j] = a[k++];
        }
    }

    printf("Матрица %dx%d:\n", m, m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            printf("%4d", mat[i][j]);
        }
        printf("\n");
    }

    printf("\nСуммы строк:\n");
    for (int i = 0; i < m; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) sum += mat[i][j];
        printf("Строка %d: %d\n", i + 1, sum);
    }

    printf("\nСуммы столбцов:\n");
    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < m; i++) sum += mat[i][j];
        printf("Столбец %d: %d\n", j + 1, sum);
    }

    for (int i = 0; i < m; i++) free(mat[i]);
    free(mat);

    if (n > used)
        printf("\nИгнорировано %d лишних чисел\n", n - used);
}

int main() {
    clock_t start = clock();

    int N;
    printf("Введите размер вектора N: ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Некорректное значение N\n");
        return 1;
    }

    create_numbers("input.txt", N);

    int *arr = read_numbers("input.txt", N);
    write_replaced("output.txt", arr, N);

    build_matrix(arr, N);

    free(arr);

    double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("\nВремя выполнения программы: %.3f секунд\n", elapsed);

    return 0;
}
