// 1. Создать и заполнить input.txt случайными числами
// 2. Открыть input.txt для чтения, считать числа в массив
// 3. Открыть output.txt для записи, записать заменённые значения
// 4. Закрыть файлы

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int n = 10;
    FILE *file_in = fopen("input.txt", "w");
    if (file_in == NULL){
        printf("Oshibka chtenia fila");
        return 1;
    }

    srand(time(NULL));
    for(int i = 0; i < n; i++){
        int num = rand() % 100;
        fprintf(file_in,"%d\n", num);
    }
    fclose(file_in);

    file_in = fopen("input.txt","r");
    if (file_in == NULL){
        printf("Oshibka chtenia fila");
        return 1;
    }
    int arr[10],count = 0;
    while (fscanf(file_in, "%d",&arr[count]) == 1 && count < n){
        count++;
    }
    fclose(file_in);

    FILE *file_out = fopen("output.txt", "w");
    if (file_out == NULL){
        printf("Oshibka chtenia fila");
        return 1;
    }

    for (int i = 0; i < count; i++){
        if (arr[i] % 5 == 0 && arr[i] % 7 == 0)
            fprintf(file_out, "FIVESEVEN\n");
        else if (arr[i] % 5 == 0)
            fprintf(file_out,"FIVE\n");
        else if (arr[i] % 7 == 0)
            fprintf(file_out,"SEVEN\n");
        else
            fprintf(file_out, "%d\n", arr[i]);
    }

    fclose(file_out);

    return 0;
}
