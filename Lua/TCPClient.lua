--Note - allocated memory is not freed

require("Bridge")
addr=c_malloc(16)
buffer=c_malloc(256)
c_setbyte(addr,0,2)         --Address family low byte, 2 is AF_INET/IPV4
c_setbyte(addr,1,0)         --Address family high byte
c_setbyte(addr,2,3721>>8)   --Port high byte
c_setbyte(addr,3,3721&0xFF) --Port low byte
c_setbyte(addr,4,127)       --IP address
c_setbyte(addr,5,0)
c_setbyte(addr,6,0)
c_setbyte(addr,7,1)
while (true) do
 size=c_read(0,buffer,0xFF)      --Read message from stdin
 client=c_socket(2,1,0)          --Create socket
 c_connect(client,addr,0x10)     --Connect to server
 c_write(client,buffer,size)     --Send message to server
 size=c_read(client,buffer,0xFF) --Read response from server
 c_write(1,buffer,size)          --Write response to stdout
 c_close(client)                 --Close connection
 end