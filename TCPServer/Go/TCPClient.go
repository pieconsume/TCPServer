//Includes
 package main
 import "fmt"
 import "net"
 import "bufio"
 import "os"

func main(){
	for
 {
	 buf:=make([]byte, 0x100)
  reader:=bufio.NewReader(os.Stdin)            //Create an IO reader for stdin
	 input,err:=reader.ReadString('\n')           //Read a message from stdin
	 if(err!=nil) { panic("Failed input read") }
	 client,err:=net.Dial("tcp","127.0.0.1:3721") //Connect to server
	 if(err!=nil) { panic("Failed dail") }
	 size,err:=client.Write([]byte(input));       //Send message to server
	 if(err!=nil) { panic("Failed TCP write") }
	 size,err=client.Read(buf);                   //Read reply from server
	 if(err!=nil) { panic("Failed TCP read") }
	 fmt.Print(string(buf[:size]))                //Write reply to console
 }
}