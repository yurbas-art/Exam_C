# Exam_C

Коллекция прототипов и учебных заданий на языке **C**. Каждая папка содержит отдельную задачу или её вариацию. Источником служат лабораторные и пробные работы для экзамена.

## Навигация по проекту

| Каталог | Описание |
|---------|---------|
| [Prototype 1](Prototype%201) | Генерация случайных чисел, замена кратных 5 и 7, формирование матрицы и подсчёт сумм строк/столбцов. |
| [Prototype 2](Prototype%202) | Работа с двумя случайными матрицами: перемножение и сложение с выводом в файл. |
| [Prototype 3](Prototype%203) | Подсчёт дней до даты из *input.txt* и генерация квадратных матриц до совпадения сумм элементов. |
| [Prototype 4](Prototype%204) | Перемножение/сложение матриц, поиск минимума и подсчёт нечётных, а также проверка одинаковых чисел. |
| [Prototype 5](Prototype%205) | Запись случайных чисел, текстовые замены по кратности и преобразование в квадратную матрицу. |
| [Task 1](Task%201) | Чтение чисел из файла, вычисление суммы, минимума/максимума и количества чётных/нечётных. |
| [Task 2](Task%202) | Генерация чисел, замена кратных 5 и 7 и запись результата. |
| [Task 3(data_work)](Task%203(data_work)) | Подсчёт дней до указанной даты из файла `data.txt`. |
| [The Final Prototype](The%20Final%20Prototype) | Итоговая версия с матричными операциями: сложение, вычитание и умножение. Сборка создаёт программы `final_int`, `final_double` и `final_double_input`. | ve48er-codex/решить-задачу-с-датой-и-матрицами
| [Real_Exam_Prototype_var1](Real_Exam_Prototype_var1) | Экзаменационный вариант 1: подсчёт дней до даты, генерация двух квадратных матриц и операции над ними. |
| [Real_Exam_Prototype_var1/Real_Exam_Prototype](Real_Exam_Prototype_var1/Real_Exam_Prototype) | Та же задача, но матрицы имеют тип `double`. |
| [Real_Exam_Var2](Real_Exam_Var2) | Экзаменационный вариант 2: генерация чисел, замены "ПЯТЬ"/"СЕМЬ" и квадратная матрица. |
| [Real_Exam_Prototype_var 2/Real_Exam_Prototype](Real_Exam_Prototype_var%202/Real_Exam_Prototype) | Та же задача, но матрицы имеют тип `double`. |
| [Real_Exam2_var1](Real_Exam2_var1) | Экзаменационный вариант 1 (пересдача): считывание даты, генерация квадратных матриц до 2-ух одинаковых сумм элементов, инициализация время работы программы |
| [Real_Exam2_var2](Real_Exam2_var2) | Экзаменационный вариант 2 (пересдача): генерация файла "input.txt", работа с матрицами(перемножение, сложение), нахождение минимального элемента, пересчет нечетных элементов в матрице 1, инициализация таймера работы программмы |   
 

## Полезные конструкции

- Использование `rand()` и `srand()` для генерации случайных чисел.
- Работа с файлами через `fopen`, `fscanf`, `fprintf`.
- Динамическое выделение памяти с `malloc` и освобождение `free`.
- Измерение времени выполнения: `clock()` и `time()`/`difftime`.
- Формирование и обработка матриц, примеры функций `multiply_matrices`, `plus_matrix`, `read_matrix` и т.д.

## Как собирать

Во всех каталогах с исходниками присутствуют `CMakeLists.txt`. Для финальной версии собирайте следующим образом:
```bash

cd "The Final Prototype"
cmake -B build
cmake --build build
```
В каталоге `build` появятся исполняемые файлы `final_int`, `final_double` и `final_double_input`.
Путь и имя исполняемого файла указаны в соответствующем `CMakeLists.txt`.

