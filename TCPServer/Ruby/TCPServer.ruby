require 'socket'
server = TCPServer.new 3721        #Create server on port
server.setsockopt(1,15,true)       #Set reuse for quick restarts
loop do
 client=server.accept              #Accept client
 message=client.recvfrom(0xFF)     #Recieve message from client
 puts message[0]                   #Print message to console
 client.puts("Message recieved\n") #Send reply
 client.close                      #Close connection
 end