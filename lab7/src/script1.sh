#!/bin/bash

pkill server
make
./server 20000 &
sleep 1
./client 127.0.0.1 20000 25