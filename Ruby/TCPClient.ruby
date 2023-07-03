require 'socket'
loop do
 message=gets
 client=TCPSocket.new '127.0.0.1',3721
 client.puts(message)
 reply=client.recvfrom(0xFF)
 puts reply[0]
 client.close
 end