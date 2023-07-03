program TCPClient(output);
 uses ctypes;
 const c='libc.so.6';
 function read(fd:cint;buffer:pcchar;buffersz:cint): cint; external c;
 function write(fd:cint;buffer:pcchar;count:cint): cint; external c;
 function socket(family:cint;subtype:cint;protocol:cint): cint; external c;
 function connect(socket:cint;address:pcchar;addrsz:cint): cint; external c;
 function close(socket:cint): cint; external c;
 type addrtype=array[0..15] of cchar;
 type buftype=array[0..255] of cchar;
 var addr:addrtype;
 var buffer:buftype;
 var size,client:cint;
begin
 addr[0]:=2;
 addr[1]:=0;
 addr[2]:=3721>>8;
 addr[3]:=3721 and 255;
 addr[4]:=127;
 addr[5]:=0;
 addr[6]:=0;
 addr[7]:=1;
 while (true) do
  begin
  size:=read(0,buffer,255);
  client:=socket(2,1,0);
  connect(client,addr,16);
  write(client,buffer,size);
  size:=read(client,buffer,255);
  write(1,buffer,size);
  close(client)
  end
end.