dyn.load("Bridge.so")
addr=.C("c_malloc",16L,0L)[2]
buffer=.C("c_malloc",256L,0L)[2]
result=.C("c_setbyte",addr,0L,2L)
result=.C("c_setbyte",addr,1L,0L)
result=.C("c_setbyte",addr,2L,bitwShiftR(3721L,8L))
result=.C("c_setbyte",addr,3L,bitwAnd(3721L,0xFFL))
while(TRUE){
 size=.C("c_read",0L,buffer,0xFFL,0L)[4]
 client=.C("c_socket",2L,1L,0L,0L)[4]
 result=.C("c_connect",as.integer(client),addr,0x10L,0L)[4]
 result=.C("c_write",as.integer(client),buffer,as.integer(size),0L)[4]
 size=.C("c_read",as.integer(client),buffer,0xFFL,0L)[4]
 result=.C("c_write",1L,buffer,as.integer(size),0L)
 result=.C("c_close",as.integer(client),0L)}