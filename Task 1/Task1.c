#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Task 1 (analysis)
 * -----------------
 * Чтение чисел из input.txt и вывод статистики (сумма,
 * минимум, максимум, количество чётных и нечётных) в output.txt.
 */

//Считать из файла input.txt последовательность целых чисел (по одному в строке).
//Найти сумму всех чисел.
//Найти минимальное и максимальное число.
//Посчитать, сколько чисел в файле чётных и сколько нечётных.
//Вывести результаты в файл output.txt в читаемом виде.

// анализ данных из input.txt
int main(){
    int min,sum,max,num;
    FILE *file_in, *file_out;
    file_in = fopen("input.txt", "r");
    file_out = fopen("output.txt","w");

    if (file_in == NULL){
        printf("Oshibka chtenya fila");
        return 1;
    }

    if(fscanf(file_in, "%d",&num)!=1){
        printf("File pustoy ili nekorrektnye dannye\n");
        fclose(file_in);
        return 1;
    }

    min = max = num;
    sum = num;

    while(fscanf(file_in,"%d",&num)==1){
        sum += num;
        if (max < num) max = num;
        if (min > num) min = num;
    }

    rewind(file_in); //перенести указатель в начало


    int even_num = 0, odd_num = 0;

    while(fscanf(file_in, "%d",&num)==1){
        if (num % 2 == 0)
            even_num++;
        else
            odd_num++;
    }

    if (file_in != NULL){
        fprintf(file_out, "Summa: %d\n",sum);
        fprintf(file_out, "Min: %d\n",min);
        fprintf(file_out, "Max: %d\n",max);
        fprintf(file_out, "Kolichesto chetnyh: %d\n",even_num);
        fprintf(file_out, "Kolichesto nechetnyh: %d\n",odd_num);
    }
    else
        printf("Oshibka zapisi faila\n");
    fclose(file_in); //закрытие файла
    fclose(file_out);

    return 0;

}