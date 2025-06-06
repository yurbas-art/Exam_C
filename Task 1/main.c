#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Task 1
 * ------
 * Генерирует N случайных чисел и записывает их
 * построчно в файл input.txt.
 */

// точка входа: создание файла со случайными числами
int main() {
    int n;
    FILE *file;
    printf("Vvedite kolichestvo chisel dlya generacii: ");
    scanf("%d",&n);
    file = fopen("input.txt","w");
    if (file == NULL){
        printf("Oshibka pri otrkytii fila");
        return 1;
    }
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        int num = rand() % 100;
        fprintf(file,"%d\n", num);

    }
    fclose(file);
    printf("File input.txt sozdan uspeshno\n", n);
    return 0;
}
