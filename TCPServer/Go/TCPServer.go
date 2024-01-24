//Includes
 package main
 import "fmt"
 import "net"

func main(){
	buf:=make([]byte, 0x100)
	server,err:=net.Listen("tcp", ":3721")       //Create a server which listens on 3721
 //Neglected to set reuse here because I couldn't find a standard library function. Maybe I just missed it?
	if(err!=nil) { panic("Failed listen") }
	for
 {
	 client,err:=server.Accept()                 //Accept a client
	 if(err!=nil) { panic("Failed accept") }
	 size,err:=client.Read(buf)                  //Read a message from the client
	 if(err!=nil) { panic("Failed TCP read") }
	 fmt.Print(string(buf[:size]))               //Write the message to console
	 client.Write([]byte("Message received\n")); //Send the response to the client
	 client.Close();                             //Close the client
 }
}