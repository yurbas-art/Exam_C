#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int rows, int cols) {
    int** m = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i) {
        m[i] = malloc(cols * sizeof(int));
    }
    return m;
}

void free_matrix(int** m, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(m[i]);
    }
    free(m);
}

void fill_random(int** m, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            m[i][j] = rand() % 10;
        }
    }
}

void transpose(int** src, int** dst, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            dst[j][i] = src[i][j];
        }
    }
}

void print_matrix(FILE* f, int** m, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            fprintf(f, "%d ", m[i][j]);
        }
        fprintf(f, "\n");
    }
}

int main() {
    srand((unsigned)time(NULL));
    int rows = 3, cols = 4;
    int** matrix = create_matrix(rows, cols);
    fill_random(matrix, rows, cols);
    int** trans = create_matrix(cols, rows);
    transpose(matrix, trans, rows, cols);

    FILE* out = fopen("output.txt", "w");
    if (!out) {
        printf("cannot open output.txt\n");
        free_matrix(matrix, rows);
        free_matrix(trans, cols);
        return 1;
    }
    fprintf(out, "Source matrix:\n");
    print_matrix(out, matrix, rows, cols);
    fprintf(out, "\nTransposed:\n");
    print_matrix(out, trans, cols, rows);
    fclose(out);

    free_matrix(matrix, rows);
    free_matrix(trans, cols);
    return 0;
}
