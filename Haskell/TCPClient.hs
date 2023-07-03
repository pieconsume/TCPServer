module Main where
 import Data.Bits
 import Foreign.C
 import Foreign.C.Types
 import Foreign.Ptr
 import Foreign.Storable
 import Foreign.Marshal.Alloc
 foreign import ccall "socket"     c_socket::CInt->CInt->CInt->IO CInt
 foreign import ccall "connect"    c_connect::CInt->Ptr a->CInt->IO CInt
 foreign import ccall "read"       c_read::CInt->Ptr a->CInt->IO CInt
 foreign import ccall "write"      c_write::CInt->Ptr a->CInt->IO CInt
 foreign import ccall "close"      c_close::CInt->IO CInt
 main=do
  addr<-mallocBytes 16
  buffer<-mallocBytes 256
  poke (addr::Ptr CShort) 2
  poke ((plusPtr addr 2)::Ptr CUShort) (shiftR 3721 8)
  poke ((plusPtr addr 3)::Ptr CUChar) ((.&.) 3721 0xFF)
  poke ((plusPtr addr 4)::Ptr CUChar) 127
  poke ((plusPtr addr 5)::Ptr CUChar) 0
  poke ((plusPtr addr 6)::Ptr CUChar) 0
  poke ((plusPtr addr 7)::Ptr CUChar) 1
  mainloop addr buffer
 mainloop addr buffer=do
  size<-c_read 0 buffer 0xFF
  client<-c_socket 2 1 0
  result<-c_connect client addr 0x10
  result<-c_write client buffer size
  size<-c_read client buffer 0xFF
  result<-c_write 1 buffer size
  mainloop addr buffer