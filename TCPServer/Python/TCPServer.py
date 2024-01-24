import socket
server=socket.socket(socket.AF_INET,socket.SOCK_STREAM)       #Create server socket
server.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,True) #Set reuse for quick restarts
server.bind(("0.0.0.0",3721))                                 #Bind address
server.listen(5)                                              #Set listener
while True:
 (client,address)=server.accept()                             #Accept client
 message=client.recv(0xFF)                                    #Recieve message from client
 print(message.decode("ascii"),end='')                        #Print message to console
 client.send(bytes("Message received\n","ascii"))             #Send reply
 client.close()                                               #Close connection