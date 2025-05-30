//1)создать файл input.txt, в который поместить N случайных чисел, размера, заданного с консоли. 
//Массивы очистить. Закрыть файл
//2)открыть файл input.txt и прочитать все значения.
//3)Все числа % на 5 заменить на слово "ПЯТЬ", % на 7 - на"СЕМЬ", % на 7 и 5 - "СЕМЬПЯТЬ". 
//Вывести результат в файл output.txt
//4)из файла input.txt сформировать матрицу путем преобразования вектора N в M столбцов. 
//Посчитать сумму строк и столбцов. Вывести матрицу и результат сложения на консоль.
//5)замерить время работы программы

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


int main ()
{
    
    srand(time(NULL));
    time_t t0 = time(0);
    
    
    char line[256];
    FILE *file = fopen("input.txt", "wt");
    FILE *new_file = fopen("output.txt", "wt");
    int *mass, **matrix; 
    int n;

    printf("Введите размер массива: ");
    scanf("%d", &n);

    // Выделение памяти для одномерного массива
    mass = (int *)malloc(n * sizeof(int));
   
    //1 Записываем случайные числа в файл
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", rand() % 100); // случайное число
    }
   
    fclose(file);
    
    // Освобождение выделенной памяти

    
  //3
    file = fopen("input.txt", "rt");
    
    for (int i = 0; i < n; i++) {
        fgets(line, 256, file);
        mass[i] = atoi(line);
    }
   
    for (int i = 0; i < n; i++){
        if (mass[i] % 5 == 0 && mass[i] % 7 == 0) 
        {
            fprintf(new_file, "FIVESEVEN\n");
        } else if (mass[i] % 5 == 0) { 
            fprintf(new_file, "FIVE\n");
        } else if (mass[i] % 7 == 0) { 
            fprintf(new_file, "SEVEN\n");
        } else {
            fprintf(new_file, "%d\n", mass[i]);
        }
    }
    
    fclose(new_file);
    
    
  //4 матрица из вектора N
    int r = floor(sqrt(n));
    
    //выделяем память для матрицы 
    matrix = (int**)malloc(r*sizeof(int*));
    for(int i = 0; i < r; i++)
    {
        matrix[i] = (int*)malloc(r*sizeof(int));
    }
     
    // заполнение матрицы элементами из массива
    int k = 0;
    for (int i = 0; i < r; i++) { 
        for (int j = 0; j < r; j++) { 
            if (k < n) {
                matrix[i][j] = mass[k++]; 
            }
        }
    }
    
    // вывод матрицы на экран
    for (int i = 0; i < r; i++) 
    {
        for (int j = 0; j < r; j++) 
        {
            printf("[%d]", matrix[i][j]);
        }
        printf("\n");
    }
    
    
    //сумма строк 
    int summa = 0;
    for (int i = 0; i < r; i++){
        for (int j = 0; j < r; j++){
        summa += matrix[i][j];
        }
    }
    printf("Сумма строк и столбцов матрицы: %d\n\n", summa);
    
    
    // Освобождение памяти
    for (int i = 0; i < r; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(mass);

    fclose(file);
    
    
    time_t t1 = time(0);
    double time_in_seconds = difftime(t1, t0);
    printf("Время выполнения программы: %f сек", time_in_seconds);
    
    
    return 0;
}
