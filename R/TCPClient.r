dyn.load("Bridge.so")
addr=.C("c_malloc",16L,0L)[2]
buffer=.C("c_malloc",256L,0L)[2]
result=.C("c_setbyte",addr,0L,2L)                                      #Set address family high byte. 2 is AF_INET/IPV4
result=.C("c_setbyte",addr,1L,0L)                                      #Set address family low byte
result=.C("c_setbyte",addr,2L,bitwShiftR(3721L,8L))                    #Set port high byte
result=.C("c_setbyte",addr,3L,bitwAnd(3721L,0xFFL))                    #Set port low byte
result=.C("c_setbyte",addr,4L,127L)                                    #Set ip
result=.C("c_setbyte",addr,5L,0L)
result=.C("c_setbyte",addr,6L,0L)
result=.C("c_setbyte",addr,7L,1L)
while(TRUE){
 size=.C("c_read",0L,buffer,0xFFL,0L)[4]                               #Read message from stdin
 client=.C("c_socket",2L,1L,0L,0L)[4]                                  #Create client socket
 result=.C("c_connect",as.integer(client),addr,0x10L,0L)[4]            #Connect to server
 result=.C("c_write",as.integer(client),buffer,as.integer(size),0L)[4] #Send message to server
 size=.C("c_read",as.integer(client),buffer,0xFFL,0L)[4]               #Read response
 result=.C("c_write",1L,buffer,as.integer(size),0L)                    #Write response to stdout
 result=.C("c_close",as.integer(client),0L)}                           #Close client