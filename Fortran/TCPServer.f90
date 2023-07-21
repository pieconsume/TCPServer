program tcpserver
 use iso_c_binding
 implicit none
 interface ! These are basic C bindings for fortran. Look up the fortran FFI online for more info
  integer(c_int) function socket(family,type,protocol) bind(c,name='socket')
   import::c_int
   integer(c_int),value,intent(in)::family,type,protocol
   end function socket
  integer(c_int) function setsockopt(socket,layer,option,value,size) bind(c,name='setsockopt')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::socket,layer,option,size
   type(c_ptr),value,intent(in)::value
   end function setsockopt
  integer(c_int) function bind(socket,address,length) bind(c,name='bind')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::socket,length
   type(c_ptr),value,intent(in)::address
   end function bind
  integer(c_int) function listen(socket,backlog) bind(c,name='listen')
   import::c_int
   integer(c_int),value,intent(in)::socket,backlog
   end function listen
  integer(c_int) function accept(socket,address,addrsize) bind(c,name='accept')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::socket
   type(c_ptr),value,intent(in)::address,addrsize
   end function accept
  integer(c_int) function read(fd,buffer,size) bind(c,name='read')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::fd,size
   type(c_ptr),value,intent(in)::buffer
   end function read
  integer(c_int) function write(fd,buffer,size) bind(c,name='write')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::fd,size
   type(c_ptr),value,intent(in)::buffer
   end function write
  integer(c_int) function close(fd) bind(c,name='close')
   import::c_int
   integer(c_int),value,intent(in)::fd
   end function close
  end interface
 integer(c_int8_t),dimension(256),target::buffer
 character(len=17),target::reply="Message received"//new_line('1')
 type::sockaddr
  integer(c_short)::type=2                     ! Address family of 2 is AF_INET/IPV4
  integer(c_int8_t)::porthi=SHIFTR(3721,8)     ! Port low high byte
  integer(c_int8_t)::portlo=IAND(3721,255)     ! Port low byte
  integer(c_int8_t),dimension(4)::ip=[0,0,0,0] ! IP address. 0.0.0.0 allows any ip to connect
  integer(c_int8_t),dimension(8)::pad          ! Padding
  end type sockaddr
 type(sockaddr),target::address
 integer(c_int)::server,client,result,size
 integer(c_int),target::true=1,addrsize=16
 server=socket(2,1,0)                          ! Create the server
 result=setsockopt(server,1,15,c_loc(true),4)  ! Set reuse for quick restarts
 result=bind(server,c_loc(address),addrsize)   ! Bind the address
 result=listen(server, 5)                      ! Set the socket as listener
 do while(1==1)
  client=accept(server,c_loc(address),c_loc(addrsize)) ! Accept a client
  size=read(client,c_loc(buffer),255)                  ! Read a message from the client
  size=write(1,c_loc(buffer),size)                     ! Write the message to stdout
  size=write(client,c_loc(reply),17)                   ! Send the response to the client
  result=close(client)                                 ! Close the client
  end do
 end program tcpserver