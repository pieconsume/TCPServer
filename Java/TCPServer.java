//Includes
 import java.net.Socket;
 import java.net.ServerSocket;
 import java.io.InputStream;
 import java.io.OutputStream;

public class TCPServer
{
 public static void main(String[] args) throws Exception
 {
  byte[] buffer = new byte[256];
  ServerSocket server = new ServerSocket(3721,5);          //Create server listener on port 3721
  server.setReuseAddress(true);                            //Set reuse for quick restarts
  while(true)
  {
   Socket client=server.accept();                          //Accept client
   InputStream input=client.getInputStream();              //Get client input stream
   OutputStream output=client.getOutputStream();           //Get client output stream
   int size=input.read(buffer);                            //Read message from client
   System.out.print(new String(buffer).substring(0,size)); //Write message to console
   output.write("Message received\n".getBytes());          //Send response to client
   client.close();                                         //Close client
  }
 }
}