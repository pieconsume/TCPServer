--If anyone would like to fix this code (if that is even possible) please for the love of all things good and holy on this earth do so.
module Main where
 import Data.Bits
 import Foreign.C
 import Foreign.C.Types
 import Foreign.Ptr
 import Foreign.Storable
 import Foreign.Marshal.Alloc
 foreign import ccall "socket"     c_socket::CInt->CInt->CInt->IO CInt
 foreign import ccall "setsockopt" c_setsockopt::CInt->CInt->CInt->Ptr CInt->CInt->IO CInt
 foreign import ccall "bind"       c_bind::CInt->Ptr a->CInt->IO CInt
 foreign import ccall "listen"     c_listen::CInt->CInt->IO CInt
 foreign import ccall "accept"     c_accept::CInt->Ptr a->Ptr CInt->IO CInt
 foreign import ccall "read"       c_read::CInt->Ptr a->CInt->IO CInt
 foreign import ccall "write"      c_write::CInt->Ptr a->CInt->IO CInt
 foreign import ccall "close"      c_close::CInt->IO CInt
 main=do
  true<-mallocBytes 4 -- Allocating new memory because ??? HOW IN CHRIST DO I MAKE A STRUCT IN A SENSIBLE WAY?
  addrsize<-mallocBytes 4
  addr<-mallocBytes 16
  buffer<-mallocBytes 256
  poke (true::Ptr CInt) 1
  poke (addr::Ptr CShort) 2
  poke ((plusPtr addr 2)::Ptr CUShort) (shiftR 3721 8) -- Have to CUShort because for SOME GOD FORSAKEN REASON IT GETS CASTED TO CHAR BEFORE BEING SHIFTED?
  poke ((plusPtr addr 3)::Ptr CUChar) ((.&.) 3721 0xFF)
  server<-c_socket 2 1 0
  result<-c_setsockopt server 1 15 true 4
  result<-c_bind server addr 16
  result<-c_listen server 5
  mainloop server addr addrsize buffer
 mainloop server addr addrsize buffer=do -- IS THIS GOING TO STACK OVERFLOW? IS THERE NO SENSIBLE WAY TO MAKE A LOOP???
  client<-c_accept server addr addrsize
  size<-c_read client buffer 0xFF
  result<-c_write 1 buffer size
  please <- newCString "Message recieved\n"
  result<-c_write client please 17
  result<-c_close client
  mainloop server addr addrsize buffer