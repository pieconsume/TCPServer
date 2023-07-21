program TCPClient(output);
 //Basic pascal FFI. Search online for more info
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
 addr[0]:=2;            //Address family low byte. 2 is AF_INET/IPV4
 addr[1]:=0;            //Address family high byte
 addr[2]:=3721>>8;      //Port high byte
 addr[3]:=3721 and 255; //Port low byte
 addr[4]:=127;          //Ip address
 addr[5]:=0;
 addr[6]:=0;
 addr[7]:=1;
 while (true) do
  begin
  size:=read(0,buffer,255);      //Read message from stdin
  client:=socket(2,1,0);         //Create socket
  connect(client,addr,16);       //Connect to server
  write(client,buffer,size);     //Write message to server
  size:=read(client,buffer,255); //Recieve response
  write(1,buffer,size);          //Write response to stdout
  close(client)                  //Close connection
  end
end.