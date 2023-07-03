//Includes
 import java.net.Socket;
 import java.net.ServerSocket;
 import java.io.InputStream;
 import java.io.OutputStream;
object TCPServer{
 def main(args:Array[String])={
  var buffer=new Array[Byte](256)
  var server=new ServerSocket(3721,5)
  server.setReuseAddress(true)
  while(true){
   var client=server.accept()
   var input=client.getInputStream()
   var output=client.getOutputStream()
   var size=input.read(buffer)
   System.out.print(new String(buffer).substring(0,size))
   output.write("Message received\n".getBytes())
   client.close()}}}