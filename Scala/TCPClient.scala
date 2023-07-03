//Includes
 import java.net.Socket;
 import java.io.InputStream;
 import java.io.OutputStream;
object TCPClient{
 def main(args:Array[String])={
  while(true){
   var buffer=new Array[Byte](256)
   var message=System.console().readLine()
   var client=new Socket("127.0.0.1",3721)
   var output=client.getOutputStream()
   var input=client.getInputStream()
   output.write((message+"\n").getBytes())
   var size=input.read(buffer)
   System.out.print(new String(buffer).substring(0,size))}}}