#!/usr/bin/env python3

#
#   Echo server in Python
#   Binds REP socket to tcp://*:5555
#   Expects "<username>" from client, replies with "Hello <username>"
#

import time
import zmq

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

while True:
    # Wait for next request from client
    message = socket.recv_pyobj()
    print(f"Received request: {message}")

    # Do some 'work'
    time.sleep(1)

    # Send reply back to client
    socket.send_pyobj(f"Hello {message}")
