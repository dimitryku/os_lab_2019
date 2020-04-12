#!/bin/bash

count=0
sum=0
while [ -n "$1" ]
do
count=$[$count+1]
sum=$[$sum+$1]
shift
done
if [[ $count -ne 0 ]]; then
av=$( echo "scale=4; $sum/$count" | bc )
echo "Среднее значение равно $av"
else
echo "Среднего значения нет!"
fi
echo "Число элементов равно $count"