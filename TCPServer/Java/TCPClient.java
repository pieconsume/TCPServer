//Includes
 import java.net.Socket;
 import java.io.InputStream;
 import java.io.OutputStream;

public class TCPClient
{
 public static void main(String[] args) throws Exception{
  while (true)
  {
   byte[] buffer=new byte[256];
   String message=System.console().readLine();             //Read message from console
   Socket client=new Socket("127.0.0.1",3721);             //Create client socket and connect to server
   OutputStream output=client.getOutputStream();           //Get client output stream
   InputStream input=client.getInputStream();              //Get client input stream
   output.write((message+"\n").getBytes());                //Send message to server
   int size=input.read(buffer);                            //Get response from server
   System.out.print(new String(buffer).substring(0,size)); //Write response to console
  }
 }
}