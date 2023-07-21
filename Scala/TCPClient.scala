//Includes
 import java.net.Socket;
 import java.io.InputStream;
 import java.io.OutputStream;

object TCPClient
{
 def main(args:Array[String])=
 {
  while(true)
  {
   var buffer=new Array[Byte](256)
   var message=System.console().readLine()                //Read message from console
   var client=new Socket("127.0.0.1",3721)                //Connect to server
   var output=client.getOutputStream()                    //Get client output stream
   var input=client.getInputStream()                      //Get client input stream
   output.write((message+"\n").getBytes())                //Write message to server
   var size=input.read(buffer)                            //Read response from server
   System.out.print(new String(buffer).substring(0,size)) //Write response to console
   client.close()                                         //Close client
  }
 }
}