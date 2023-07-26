dyn.load("Bridge.so")
addrlen<-0x10L
on<-1L
addr=.C("c_malloc",16L,0L)[2]
buffer=.C("c_malloc",256L,0L)[2]
result=.C("c_setbyte",addr,0L,2L)                                       #Set address family high byte. 2 is AF_INET/IPV4
result=.C("c_setbyte",addr,1L,0L)                                       #Set address family low byte
result=.C("c_setbyte",addr,2L,bitwShiftR(3721L,8L))                     #Set port high byte
result=.C("c_setbyte",addr,3L,bitwAnd(3721L,0xFFL))                     #Set port low byte. The address should be initialized to 0.0.0.0 which accepts any ip
server=.C("c_socket",2L,1L,0L,0L)[4]                                    #Create server socket
result=.C("c_setsockopt",as.integer(server),1L,15L,on,4L,0L)[6]         #Set reuse for quick restarts
result=.C("c_bind",as.integer(server),addr,addrlen,0L)[4]               #Bind address
result=.C("c_listen",as.integer(server),5L,0L)[3]                       #Set listener
while(TRUE){
 client=.C("c_accept",as.integer(server),addr,addrlen,0L)[4]            #Accept client
 size=.C("c_read",as.integer(client),buffer,0xFFL,0L)[4]                #Read message from client
 result=.C("c_write",1L,buffer,as.integer(size),0L)[4]                  #Write message to stdout
 result=.C("c_write",as.integer(client),"Message received\n",17L,0L)[4] #Send reply
 result=.C("c_close",as.integer(client),0L)[2]}                         #Close client