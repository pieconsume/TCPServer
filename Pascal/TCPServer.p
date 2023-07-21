program TCPServer(output);
 //Basic pascal FFI. Search online for more info
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
 addr[0]:=2;            //Address family low byte. 2 is AF_INET/IPV4
 addr[1]:=0;            //Address family high byte
 addr[2]:=3721>>8;      //Port high byte
 addr[3]:=3721 and 255; //Port low byte. The address should be initialized to 0.0.0.0 which accepts from any address
 on:=1;
 msg:='Message received'+sLineBreak;
 server:=socket(2,1,0);         //Create socket
 setsockopt(server,1,15,@on,4); //Set reuse for quick restarts
 bind(server,addr,16);          //Bind address
 listen(server,1);              //Set as listener
 while (true) do
  begin
  client:=accept(server,addr,@addrlen); //Accept client
  size:=read(client,buffer,255);        //Read message from client
  write(1,buffer,size);                 //Write message to stdout
  write(client,@msg+1,17);              //Send reply to client. The address of msg is offset by one because pascal strings are formatted differently
  close(client);                        //Close the connection
  end
 end.