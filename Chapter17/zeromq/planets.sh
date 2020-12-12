#!/bin/bash

./server.py &
SERVER_PID=$!

./client.py Mars &
./client.py Jupiter &
./client.py Venus

kill $SERVER_PID
