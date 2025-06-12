#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// выделение квадратной матрицы int размером n x n
int** alloc_matrix(int n) {
    int** m = (int**)malloc(n * sizeof(int*));
    if (!m) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        m[i] = (int*)malloc(n * sizeof(int));
        if (!m[i]) {
            printf("Ошибка выделения памяти\n");
            for (int k = 0; k < i; k++) {
                free(m[k]);
            }
            free(m);
            exit(1);
        }
    }
    return m;
}

// освобождение памяти матрицы
void free_matrix(int** m, int n) {
    for (int i = 0; i < n; i++) {
        free(m[i]);
    }
    free(m);
}

// заполнение матрицы случайными числами 1..9
void fill_random(int** m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = rand() % 9 + 1;
        }
    }
}

// запись матрицы в файл
void write_matrix(FILE* f, int** m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(f, "%d ", m[i][j]);
        }
        fprintf(f, "\n");
    }
}

// чтение матрицы из файла
int** read_matrix(FILE* f, int n) {
    int** m = alloc_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(f, "%d", &m[i][j]) != 1) {
                printf("File format error\n");
                free_matrix(m, n);
                exit(1);
            }
        }
    }
    return m;
}

// сложение матриц
int** plus_matrix(int** a, int** b, int n) {
    int** r = alloc_matrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            r[i][j] = a[i][j] + b[i][j];
    return r;
}

// вычитание матриц
int** minus_matrix(int** a, int** b, int n) {
    int** r = alloc_matrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            r[i][j] = a[i][j] - b[i][j];
    return r;
}

// умножение матриц
int** multiply_matrix(int** a, int** b, int n) {
    int** r = alloc_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            r[i][j] = 0;
            for (int k = 0; k < n; k++)
                r[i][j] += a[i][k] * b[k][j];
        }
    }
    return r;
}

int main() {
    system("chcp 65001 > nul");
    clock_t start = clock();

    // --- читаем дату из input.txt ---
    int day, month, year;
    FILE* fdate = fopen("input.txt", "r");
    if (!fdate) {
        printf("Не удалось открыть input.txt\n");
        return 1;
    }
    if (fscanf(fdate, "%d %d %d", &day, &month, &year) != 3) {
        printf("Неверный формат даты\n");
        fclose(fdate);
        return 1;
    }
    fclose(fdate);

    time_t now;
    time(&now);
    struct tm target = {0};
    target.tm_mday = day;
    target.tm_mon = month - 1;
    target.tm_year = year - 1900;

    time_t target_time = mktime(&target);
    if (target_time == -1) {
        printf("Неверная дата\n");
        return 1;
    }
    double diff_seconds = difftime(target_time, now);
    int diff_days = (int)(diff_seconds / (60 * 60 * 24));
    if (diff_days > 0)
        printf("До %02d.%02d.%04d осталось %d дней.\n", day, month, year, diff_days);
    else if (diff_days == 0)
        printf("Указанная дата сегодня! (%02d.%02d.%04d)\n", day, month, year);
    else
        printf("Указанная дата уже прошла! (%02d.%02d.%04d)\n", day, month, year);

    // --- генерация матриц ---
    int n;
    printf("Введите размер квадратных матриц: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Некорректный размер\n");
        return 1;
    }

    srand((unsigned)time(NULL));
    int** m1 = alloc_matrix(n);
    int** m2 = alloc_matrix(n);
    fill_random(m1, n);
    fill_random(m2, n);

    FILE* f = fopen("input.txt", "w");
    if (!f) {
        printf("Не удалось создать input.txt\n");
        free_matrix(m1, n);
        free_matrix(m2, n);
        return 1;
    }
    write_matrix(f, m1, n);
    fprintf(f, "\n");
    write_matrix(f, m2, n);
    fclose(f);

    free_matrix(m1, n);
    free_matrix(m2, n);

    // --- считываем матрицы обратно ---
    f = fopen("input.txt", "r");
    if (!f) {
        printf("Не удалось открыть input.txt\n");
        return 1;
    }
    m1 = read_matrix(f, n);
    int c = fgetc(f);
    if (c != '\n') ungetc(c, f);
    m2 = read_matrix(f, n);
    fclose(f);

    int** sum = plus_matrix(m1, m2, n);
    int** diff = minus_matrix(m1, m2, n);
    int** prod = multiply_matrix(m1, m2, n);

    FILE* out = fopen("output.txt", "w");
    if (!out) {
        printf("Не удалось создать output.txt\n");
        free_matrix(m1, n);
        free_matrix(m2, n);
        free_matrix(sum, n);
        free_matrix(diff, n);
        free_matrix(prod, n);
        return 1;
    }

    fprintf(out, "Сумма матриц:\n");
    write_matrix(out, sum, n);
    fprintf(out, "\nРазность матриц:\n");
    write_matrix(out, diff, n);
    fprintf(out, "\nПроизведение матриц:\n");
    write_matrix(out, prod, n);
    fclose(out);

    free_matrix(m1, n);
    free_matrix(m2, n);
    free_matrix(sum, n);
    free_matrix(diff, n);
    free_matrix(prod, n);

    double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Время выполнения программы: %.3f секунд\n", elapsed);

    return 0;
}
