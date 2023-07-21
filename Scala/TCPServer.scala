//Includes
 import java.net.Socket;
 import java.net.ServerSocket;
 import java.io.InputStream;
 import java.io.OutputStream;

object TCPServer
{
 def main(args:Array[String])=
 {
  var buffer=new Array[Byte](256)
  var server=new ServerSocket(3721,5)                     //Create server socket
  server.setReuseAddress(true)                            //Set reuse for quick restarts
  while(true)
  {
   var client=server.accept()                             //Accept client
   var input=client.getInputStream()                      //Get client input stream
   var output=client.getOutputStream()                    //Get client output stream
   var size=input.read(buffer)                            //Read message from client
   System.out.print(new String(buffer).substring(0,size)) //Print message to console
   output.write("Message received\n".getBytes())          //Send response
   client.close()                                         //Close connection
  }
 }
}