№1 и 2 в соответствующих  папках


№ 3
В **задании 2**, вы написали маленькую библиотеку с одной функцией, переворота строки. Тем не менее этот код уже можно переиспользовать, а чтобы это было удобнее делать, его необходимо вынести в библиотеку. Ваше задание скомпилировать статическую и динамическую библиотеки с RevertString и залинковать их в приложения с main.c.

***Получится две программы, первая будет использовать статическую билиотеку, а вторая динамическую.*** 

gcc -c main.c -o  main.o
mkdir static
gcc -c ./revert_string.c -o ./static/revert_string.o -std=c99
mkdir shared
gcc -c -fPIC revert_string.c -o ./shared/revert_string.o -std=c99
ar rcs ./static/lib1.a ./static/revert_string.o
gcc main.o -Lstatic -l1 -o static_reverter
gcc -shared shared/revert_string.o -o shared/libreverter.so
gcc main.o -Lshared -lreverter -o shared_reverter

копируем в usr/lib
sudo mv shared/libreverter.so /usr/lib
**Для облака**
LD_LIBRARY_PATH=/projects/os_lab_2019/lab2/src/revert_string/shared/:${LD_LIBRARY_PATH}

./shared_reverter qwerty


**на облаке не работает**
№4
Если вы зайдете в update.sh, то увидите, слежующую строчку 
`sudo apt -y install libcunit1 libcunit1-doc libcunit1-dev`. 
Это установка в вашу систему библиотеки для юнит тестирования на 
языке Си - CUnit. В папочке test вы найдете tests.c - готовую программу, 
которая запускает несколько юнит тестов для функции RevertString. 
Ваша задача, скомпилировать эту программу с динамической 
библиотекой из **Задания 3**. Важно, что программа с тестами и 
программа из **Задания 2** должны использовать одну библиотеку 
(один файл). 

~/os_lab_2019/lab2/src/tests$ cp ../revert_string/revert_string.h ./
gcc tests.c -L/usr/lib -lreverter -o testsforreverter -lcunit
./testsforreverter

Suite: Suite
  Test: test of RevertString function ...passed

Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      1      1    n/a      0        0
               tests      1      1      1      0        0
             asserts      4      4      4      0      n/a

Elapsed time =    0.000 seconds


