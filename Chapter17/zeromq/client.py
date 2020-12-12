#!/usr/bin/env python3

#
#   Echo client in Python
#   Connects REQ socket to tcp://localhost:5555
#   Sends "<username>" to server, expects "Hello <username>" back
#

import zmq

def main(who):
    context = zmq.Context()

    # Socket to talk to server
    print("Connecting to echo server...")
    socket = context.socket(zmq.REQ)
    socket.connect("tcp://localhost:5555")

    # Do 5 requests, waiting each time for a response
    for request in range(5):
        print(f"Sending request {request} ...")
        socket.send_pyobj(who)

        # Get the reply.
        message = socket.recv_pyobj()
        print(f"Received reply {request} [ {message} ]")

if __name__ == '__main__':
    import sys
    if len(sys.argv) != 2:
        print("usage: client.py <username>")
        raise SystemExit
    main(sys.argv[1])
