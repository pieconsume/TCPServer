require 'socket'
loop do
 message=gets                          #Read message from console
 client=TCPSocket.new '127.0.0.1',3721 #Connect to server
 client.puts(message)                  #Send message to server
 reply=client.recvfrom(0xFF)           #Read response from server
 puts reply[0]                         #Print response to console
 client.close                          #Close connection
 end