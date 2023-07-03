import socket
while True:
 message=input()
 client=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
 client.connect(("127.0.0.1",3721))
 client.send(bytes(message+"\n","ascii"))
 reply=client.recv(0xFF)
 print(reply.decode("ascii"),end='')