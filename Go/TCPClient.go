//Includes
 package main
 import "fmt"
 import "net"
 import "bufio"
 import "os"
func main(){
	for{
	 buf:=make([]byte,256)
  reader:=bufio.NewReader(os.Stdin)
	 input,err:=reader.ReadString('\n')
	 if(err!=nil){panic("Failed input read")}
	 client,err:=net.Dial("tcp","127.0.0.1:3721")
	 if(err!=nil){panic("Failed dail")}
	 size,err:=client.Write([]byte(input));
	 if(err!=nil){panic("Failed TCP write")}
	 size,err=client.Read(buf);
	 if(err!=nil){panic("Failed TCP read")}
	 fmt.Print(string(buf[:size]))}}