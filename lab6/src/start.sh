#!/bin/bash
#nserv nthreads k mod addres

touch $5
I=0
cat /dev/null > $5
chmod 777 $5
while [ $I -lt $1 ]
do
./server --port $[20001+$I] --tnum $2 &
echo 127.0.0.1:$[20001+$I] >> $5
#echo server started
I=$[ $I + 1 ]
done
sleep 1
./client --k $3 --mod $4 --servers $5
#echo client started