#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// выделение квадратной матрицы double размером n x n
double** alloc_matrix_d(int n) {
    double** m = (double**)malloc(n * sizeof(double*));
    if (!m) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        m[i] = (double*)malloc(n * sizeof(double));
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
void free_matrix_d(double** m, int n) {
    for (int i = 0; i < n; i++) {
        free(m[i]);
    }
    free(m);
}

// заполнение матрицы случайными числами 1..9
void fill_random_d(double** m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = (double)(rand() % 9 + 1);
        }
    }
}

// запись матрицы в файл
void write_matrix_d(FILE* f, double** m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(f, "%.2lf ", m[i][j]);
        }
        fprintf(f, "\n");
    }
}

// чтение матрицы из файла
double** read_matrix_d(FILE* f, int n) {
    double** m = alloc_matrix_d(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(f, "%lf", &m[i][j]) != 1) {
                printf("Ошибка формата файла\n");
                free_matrix_d(m, n);
                exit(1);
            }
        }
    }
    return m;
}

// сложение матриц
double** plus_matrix_d(double** a, double** b, int n) {
    double** r = alloc_matrix_d(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            r[i][j] = a[i][j] + b[i][j];
        }
    }
    return r;
}

// вычитание матриц
double** minus_matrix_d(double** a, double** b, int n) {
    double** r = alloc_matrix_d(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            r[i][j] = a[i][j] - b[i][j];
        }
    }
    return r;
}

// умножение матриц
double** multiply_matrix_d(double** a, double** b, int n) {
    double** r = alloc_matrix_d(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            r[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                r[i][j] += a[i][k] * b[k][j];
            }
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
    double** m1 = alloc_matrix_d(n);
    double** m2 = alloc_matrix_d(n);
    fill_random_d(m1, n);
    fill_random_d(m2, n);

    FILE* f = fopen("input.txt", "w");
    if (!f) {
        printf("Не удалось создать input.txt\n");
        free_matrix_d(m1, n);
        free_matrix_d(m2, n);
        return 1;
    }
    write_matrix_d(f, m1, n);
    fprintf(f, "\n");
    write_matrix_d(f, m2, n);
    fclose(f);

    free_matrix_d(m1, n);
    free_matrix_d(m2, n);

    // --- считываем матрицы обратно ---
    f = fopen("input.txt", "r");
    if (!f) {
        printf("Не удалось открыть input.txt\n");
        return 1;
    }
    m1 = read_matrix_d(f, n);
    int c = fgetc(f);
    if (c != '\n') {
        ungetc(c, f);
    }
    m2 = read_matrix_d(f, n);
    fclose(f);

    double** sum = plus_matrix_d(m1, m2, n);
    double** diff = minus_matrix_d(m1, m2, n);
    double** prod = multiply_matrix_d(m1, m2, n);

    FILE* out = fopen("output.txt", "w");
    if (!out) {
        printf("Не удалось создать output.txt\n");
        free_matrix_d(m1, n);
        free_matrix_d(m2, n);
        free_matrix_d(sum, n);
        free_matrix_d(diff, n);
        free_matrix_d(prod, n);
        return 1;
    }

    fprintf(out, "Сумма матриц:\n");
    write_matrix_d(out, sum, n);
    fprintf(out, "\nРазность матриц:\n");
    write_matrix_d(out, diff, n);
    fprintf(out, "\nПроизведение матриц:\n");
    write_matrix_d(out, prod, n);
    fclose(out);

    free_matrix_d(m1, n);
    free_matrix_d(m2, n);
    free_matrix_d(sum, n);
    free_matrix_d(diff, n);
    free_matrix_d(prod, n);

    double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Время выполнения программы: %.3f секунд\n", elapsed);

    return 0;
}

