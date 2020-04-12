Задание 1:
Запустить скрипт background.sh в фоновом режиме:
 ./background.sh &

Создать текстовый файл и вывести его содержимое на экран терминала:
 cat - > newfile
*some text for file* 

cat newfile

Очистить окно терминала:

ctrl + C или  reset или clear

Посчитать количество символов в файле:

wc newfile -m


Задание 2:
Записать из файла with_cake.txt все строчки, в которых есть слово cake.

grep -i cake > with_cake.txt


Задание 3:
Сделать файл hello.sh исполняемым и выполнить его
Написать bash скрипт, который выводит текущие путь, дату,
время и содержимое PATH.

./task3.sh


Задание  4:
Скормить скрипту 150 рандомных чисел

./fornum.sh 
./average.sh $(cat numbers.txt)
