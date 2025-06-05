#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main() {
    int n = 10;
    int* data = malloc(n * sizeof(int));
    srand((unsigned)time(NULL));
    FILE* input = fopen("input.txt", "w");
    if (!input) return 1;
    for (int i = 0; i < n; ++i) {
        data[i] = rand() % 100;
        fprintf(input, "%d\n", data[i]);
    }
    fclose(input);

    FILE* read = fopen("input.txt", "r");
    if (!read) return 1;
    for (int i = 0; i < n; ++i) {
        fscanf(read, "%d", &data[i]);
    }
    fclose(read);

    bubble_sort(data, n);

    FILE* out = fopen("sorted.txt", "w");
    if (!out) return 1;
    for (int i = 0; i < n; ++i) {
        fprintf(out, "%d\n", data[i]);
    }
    fclose(out);
    free(data);
    return 0;
}
