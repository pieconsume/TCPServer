import socket
while True:
 message=input()                                         #Read message from console
 client=socket.socket(socket.AF_INET,socket.SOCK_STREAM) #Create client socket
 client.connect(("127.0.0.1",3721))                      #Connect to server
 client.send(bytes(message+"\n","ascii"))                #Send message
 reply=client.recv(0xFF)                                 #Recieve reply from server
 print(reply.decode("ascii"),end='')                     #Print reply to console
 client.close()                                          #Close client