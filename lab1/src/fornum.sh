#!/bin/bash
c=0
while [ $c -lt 150 ]
do
od -An -d  -N 2 /dev/urandom >> numbers.txt
c=$[$c + 1]
done
echo "done"