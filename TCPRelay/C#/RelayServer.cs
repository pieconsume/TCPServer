//Includes
 using System;
 using System.Text;
 using System.Net;
 using System.Net.Sockets;
 using System.Collections.Generic;

public class TCPServer
{
 public static void Main()
 {
  List<Socket> sockets = new List<Socket>(); //Using a list instead of an array because that is what Socket.Select() accepts
  byte[] buffer = new byte[0x100];
  Socket server = new Socket(AddressFamily.InterNetwork, SocketType.Stream,ProtocolType.Tcp); //Create the server socket
  server.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);      //Set reuse for quick restarts
  server.Bind(new IPEndPoint(IPAddress.Any, 3721));                                           //Bind the address
  server.Listen(5);                                                                           //Set the server as a listener socket
  sockets.Add(server);                                                                        //Add the server to the sockets list
  while(true)
  {
   List<Socket> readable = new List<Socket>(sockets); //Create a copy of the list of sockets
   Socket.Select(readable, null, null, -1);           //Select only sockets with data to read
   if (readable[0] == server)
   {
    sockets.Add(server.Accept()); //Add new clients to the list
   }
   else
   {
    for (int i = 0; i < readable.Count; i++)
    {
     int size = readable[i].Receive(buffer, 0, 255, 0); //Receive a message from the client
     if (size == 0) { sockets.Remove(readable[i]); }    //If no data is received then the client has closed
     for (int j = 1; j < sockets.Count; j++)
     {
      if (sockets[j] == readable[i]) { continue; }   //Skip over the client that sent the message
      size = sockets[j].Send(buffer, 0, size, 0);    //Send the message to all other clients
      if (size == 0) { sockets.Remove(sockets[j]); } //Remove any clients that fail to receive the message
     }
    }
   }
  }
 }
}