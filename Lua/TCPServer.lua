require("Bridge")
--Seemed most sensible to cast pointers to long and use lua_pushnumber. Simple and works fine as far as I can tell.
--I don't explicitly free memory since it will be freed anyway on program exit.
--I just realized that this entire program only calls bridge functions. Somewhat silly if you ask me.
addrlen=c_malloc(4)
on=c_malloc(4)
addr=c_malloc(16)
buffer=c_malloc(256)
reply=c_malloc(17)
c_setint(on,0,1)
c_setbyte(addr,0,2)
c_setbyte(addr,1,0)
c_setbyte(addr,2,3721>>8)
c_setbyte(addr,3,3721&0xFF)
c_setstr(reply,17,'Message received\n')
server=c_socket(2,1,0)
result=c_setsockopt(server,1,15,on,4)
result=c_bind(server,addr,0x10)
result=c_listen(server,5)
while (true) do
 client=c_accept(server,addr,addrlen)
 size=c_read(client,buffer,0xFF)
 c_write(1,buffer,size)
 c_write(client,reply,17)
 c_close(client)
 end