//Includes
 import java.net.Socket;
 import java.net.ServerSocket;
 import java.io.InputStream;
 import java.io.OutputStream;
public class TCPServer{
 public static void main(String[] args) throws Exception{
  byte[] buffer=new byte[256];
  ServerSocket server=new ServerSocket(3721,5);
  server.setReuseAddress(true);
  while(true){
   Socket client=server.accept();
   InputStream input=client.getInputStream();
   OutputStream output=client.getOutputStream();
   int size=input.read(buffer);
   System.out.print(new String(buffer).substring(0,size));
   output.write("Message received\n".getBytes());
   client.close();}}}