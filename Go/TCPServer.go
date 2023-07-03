//Includes
 package main
 import "fmt"
 import "net"
func main(){
	server,err:=net.Listen("tcp",":3721")
	if(err!=nil){panic("Failed listen")}
	for{
	 client,err:=server.Accept()
	 if(err!=nil){panic("Failed accept")}
	 buf:=make([]byte,256)
	 size,err:=client.Read(buf)
	 if(err!=nil){panic("Failed TCP read")}
	 fmt.Print(string(buf[:size]))
	 client.Write([]byte("Message received\n"));
	 client.Close();}}