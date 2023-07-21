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
  true<-mallocBytes 4
  addrsize<-mallocBytes 4
  addr<-mallocBytes 16
  buffer<-mallocBytes 256
  poke (true::Ptr CInt) 1
  poke (addr::Ptr CShort) 2                             --Address family 2, AF_INET/IPV4
  poke ((plusPtr addr 2)::Ptr CUShort) (shiftR 3721 8)  --Port high byte. Have to CUShort because because the value is cast before shifting
  poke ((plusPtr addr 3)::Ptr CUChar) ((.&.) 3721 0xFF) --Port low byte. The ip and padding should be initialized to 0. IP 0.0.0.0 accepts connections from any address.
  server<-c_socket 2 1 0                  --Create server socket
  result<-c_setsockopt server 1 15 true 4 --Set reuse for quick restarts
  result<-c_bind server addr 16           --Bind address
  result<-c_listen server 5               --Set socket as listener
  mainloop server addr addrsize buffer
 mainloop server addr addrsize buffer=do
  reply<-newCString "Message recieved\n"
  client<-c_accept server addr addrsize   --Accept client
  size<-c_read client buffer 0xFF         --Read message from client
  result<-c_write 1 buffer size           --Write message to stdout
  result<-c_write client reply 17         --Send reply to client
  result<-c_close client                  --Close client
  mainloop server addr addrsize buffer