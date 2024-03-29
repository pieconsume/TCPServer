program tcpclient
 use iso_c_binding
 implicit none
 interface ! These are basic C bindings for fortran. Look up the fortran FFI online for more info
  integer(c_int) function socket(family,type,protocol) bind(c,name='socket')
   import::c_int
   integer(c_int),value,intent(in)::family,type,protocol
   end function socket
  integer(c_int) function connect(fd,address,addrsize) bind(c,name='connect')
   import::c_int,c_ptr
   integer(c_int),value,intent(in)::fd,addrsize
   type(c_ptr),value,intent(in)::address
   end function connect
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
 type::sockaddr
  integer(c_short)::type=2                       ! Address family of 2 is AF_INET/IPV4
  integer(c_int8_t)::porthi=SHIFTR(3721,8)       ! Port high byte
  integer(c_int8_t)::portlo=IAND(3721,255)       ! Port low byte
  integer(c_int8_t),dimension(4)::ip=[127,0,0,1] ! IP Address
  integer(c_int8_t),dimension(8)::pad            ! Padding
  end type sockaddr
 type(sockaddr),target::address
 integer(c_int)::result,size,client,addrsize=16
 do while(1==1)
  size=read(0,c_loc(buffer),255)                 ! Read message from stdin
  client=socket(2,1,0)                           ! Create the client
  result=connect(client,c_loc(address),addrsize) ! Connect to the server
  size=write(client,c_loc(buffer),size)          ! Send message to the server
  size=read(client,c_loc(buffer),255)            ! Read server response
  size=write(1,c_loc(buffer),size)               ! Write server response to stdout
  close(client)                                  ! Close client
  end do
 end program tcpclient