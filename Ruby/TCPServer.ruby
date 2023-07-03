require 'socket'
server = TCPServer.new 3721
loop do
 client=server.accept
 message=client.recvfrom(0xFF)
 puts message[0]
 client.puts("Message recieved\n")
 client.close
 end