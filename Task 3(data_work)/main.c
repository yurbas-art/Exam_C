#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Task 3
 * ------
 * Считывает дату из файла data.txt и выводит,
 * сколько дней осталось до неё (или прошло с неё).
 */

// точка входа программы
int main() {
    int day, month, year;  // Теперь порядок day, month, year
    FILE *file_data = fopen("data.txt", "r");
    if (file_data == NULL) {
        printf("Data ne raspoznana\n");
        return 1;
    }

    // Считываем в порядке ДД ММ ГГГГ
    if (fscanf(file_data, "%d %d %d", &day, &month, &year) != 3) {
        printf("Oshibka: Nekorrektniy format\n");
        fclose(file_data);
        return 1;
    }
    fclose(file_data);

    // Проверка корректности даты
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        printf("Oshibka: Nekorrektnaya data!\n");
        return 1;
    }

    time_t now;
    time(&now);
    struct tm *current_time = localtime(&now);

    struct tm target_date = {0};
    target_date.tm_year = year - 1900;
    target_date.tm_mon = month - 1;
    target_date.tm_mday = day;

    time_t target_time = mktime(&target_date);
    if (target_time == -1) {
        printf("Nevernaya data!\n");
        return 1;
    }

    double diff_seconds = difftime(target_time, now);
    int diff_days = (int)(diff_seconds / (60 * 60 * 24));

    // Вывод в формате ДД.ММ.ГГГГ
    if (diff_days > 0) {
        printf("Do %02d.%02d.%04d ostalos %d dney.\n", day, month, year, diff_days);
    } else if (diff_days == 0) {
        printf("Ukazannaya data segodnya! (%02d.%02d.%04d)\n", day, month, year);
    } else {
        printf("Ukazannaya data uje proshla! (%02d.%02d.%04d)\n", day, month, year);
    }

    return 0;
}
