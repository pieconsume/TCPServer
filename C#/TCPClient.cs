//Includes
 using System;
 using System.Text;
 using System.Net;
 using System.Net.Sockets;

public class TCPClient
{
 public static void Main()
 {
  byte[] buffer = new byte[0x100];
  while(true)
  {
   string message=Console.ReadLine()+"\n";                                                      //Read message from console
   Socket client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp); //Create the client
   client.Connect(new IPEndPoint(IPAddress.Loopback, 3721));                                    //Connect to the address
   client.Send(Encoding.ASCII.GetBytes(message));                                               //Send the message to the server
   int size = client.Receive(buffer, 0, 255, 0, out SocketError error);                         //Recieve the response from the server
   Console.Write(Encoding.ASCII.GetString(buffer), 0, size);                                    //Write the response to console
   client.Close();                                                                              //Close the client
  }
 }
}