program TCPServer(output);
 uses ctypes;
 const c='libc.so.6';
 function read(fd:cint;buffer:pcchar;buffersz:cint): cint; external c;
 function write(fd:cint;buffer:pcchar;count:cint): cint; external c;
 function socket(family:cint;subtype:cint;protocol:cint): cint; external c;
 function setsockopt(socket:cint;level:cint;name:cint;value:pcchar;valuesz:cint): cint; external c;
 function bind(socket:cint;address:pcchar;addrsz:cint): cint; external c;
 function listen(socket:cint;backlog:cint): cint; external c;
 function accept(socket:cint;address:pcchar;addrsz:pcint): cint; external c;
 function close(socket:cint): cint; external c;
 type addrtype=array[0..15] of cchar;
 type buftype=array[0..255] of cchar;
 var addr:addrtype;
 var buffer:buftype;
 var server,client,on,addrlen,size:cint;
 var msg:string[17];
begin
 addr[0]:=2;
 addr[1]:=0;
 addr[2]:=3721>>8;
 addr[3]:=3721 and 255;
 on:=1;
 msg:='Message received'+sLineBreak;
 server:=socket(2,1,0);
 setsockopt(server,1,15,@on,4);
 bind(server,addr,16);
 listen(server,1);
 while (true) do
  begin
  client:=accept(server,addr,@addrlen);
  size:=read(client,buffer,255);
  write(1,buffer,size);
  write(client,@msg+1,17);
  close(client);
  end
 end.