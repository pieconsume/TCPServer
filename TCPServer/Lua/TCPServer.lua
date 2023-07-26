--Note - allocated memory is not freed

require("Bridge")
addrlen=c_malloc(4)
on=c_malloc(4)
addr=c_malloc(16)
buffer=c_malloc(256)
reply=c_malloc(17)
c_setint(on,0,1)
c_setbyte(addr,0,2)         --Address family low byte, 2 is AF_INET/IPV4
c_setbyte(addr,1,0)         --Address family high byte
c_setbyte(addr,2,3721>>8)   --Port high byte
c_setbyte(addr,3,3721&0xFF) --Port low byte. The address should be initialized to 0.0.0.0 which accepts all addresses
c_setstr(reply,17,'Message received\n')
server=c_socket(2,1,0)                --Create socket
result=c_setsockopt(server,1,15,on,4) --Set reuse for fast restarts 
result=c_bind(server,addr,0x10)       --Bind the address
result=c_listen(server,5)             --Set as listener
while(true) do
 client=c_accept(server,addr,addrlen) --Accept a client
 size=c_read(client,buffer,0xFF)      --Read message from client
 c_write(1,buffer,size)               --Write message to stdout
 c_write(client,reply,17)             --Send reply to client
 c_close(client)                      --Close the client
 end