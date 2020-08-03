# Coded by Anthony Kimondo Mwangi

import socket
s = socket.socket() # create a socket
s.connect(("127.0.0.1" , 6013)) # connect to a localhost server on port 6013
s.send("Python Client\n".encode()) # send the client name
print(s.recv(1024).decode()) # receive data from the server and output it to stdout
s.close() # close the socket