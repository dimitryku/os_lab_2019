## Задание 1
Написать функцию GetMinMax в find_max_min.c, которая ищет минимальный и максимальный элементы массива, на заданном промежутке.
Разобраться, что делает программа в sequiential_min_max.c, скомпилировать, проверить, что написанный вами GetMinMax работает правильно.
**добавил код в find_min_max.c**

gcc sequential_min_max.c utils.c find_min_max.c -o sequental -std=c99
./sequental 133 12
min: 12153372
max: 1825189355

## Задание 2 - 3

### Необходимые знания

Завершить программу parallel\_min\_max.c, так, чтобы задача нахождения минимума и максимума в массиве решалась параллельно.
Если выставлен аргумент `by_files` для синхронизации процессов использовать файлы (задание 2), в противном случае использовать pipe (задание 3).
**код добавлен в необходимые места**
gcc parallel_min_max.c find_min_max.c utils.c -o parallel -std=c99
./parallel --seed 34 --array_size 13 --pnum 5
./parallel --seed 34 --array_size 13 --pnum 5 --by_files

## Задание 4
**код добавлен в makefile**

## Задание 5
**создан файл parallel_sequential.c, добавлен в сборку makefile all + makefile parallel_sequential + makefile clean**
