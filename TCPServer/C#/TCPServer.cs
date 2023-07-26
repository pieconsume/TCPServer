//Includes
 using System;
 using System.Text;
 using System.Net;
 using System.Net.Sockets;

public class TCPServer
{
 public static void Main()
 {
  byte[] buffer = new byte[0x100];
  Socket server = new Socket(AddressFamily.InterNetwork, SocketType.Stream,ProtocolType.Tcp); //Create the server socket
  server.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);      //Set reuse for quick restarts
  server.Bind(new IPEndPoint(IPAddress.Any, 3721));                                           //Bind the address
  server.Listen(5);                                                                           //Set the server as a listener socket
  while(true)
  {
   Socket client = server.Accept();                                 //Accept the client
   int size = client.Receive(buffer,0,255,0,out SocketError error); //Recieve a message from the client
   Console.Write(Encoding.ASCII.GetString(buffer), 0, size);        //Write the message to console
   client.Send(Encoding.ASCII.GetBytes("Message received\n"));      //Send a reply to the client
   client.Close();                                                  //Close the client
  }
 }
}