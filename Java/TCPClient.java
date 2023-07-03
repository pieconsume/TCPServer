//Includes
 import java.net.Socket;
 import java.io.InputStream;
 import java.io.OutputStream;
public class TCPClient{
 public static void main(String[] args) throws Exception{
  while (true){
   byte[] buffer=new byte[256];
   String message=System.console().readLine();
   Socket client=new Socket("127.0.0.1",3721);
   OutputStream output=client.getOutputStream();
   InputStream input=client.getInputStream();
   output.write((message+"\n").getBytes());
   int size=input.read(buffer);
   System.out.print(new String(buffer).substring(0,size));}}}