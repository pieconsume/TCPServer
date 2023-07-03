import socket
server=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEPORT,True)
server.bind(("0.0.0.0",3721))
server.listen(5)
while True:
 (client,address)=server.accept()
 message=client.recv(0xFF)
 print(message.decode("ascii"),end='')
 client.send(bytes("Message received\n","ascii"))
 client.close()