//Includes
 using System;
 using System.Text;
 using System.Net;
 using System.Net.Sockets;
 using System.Threading.Tasks;

public class TCPClient
{
 public static void Main()
 {
  Socket client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp); //Create the client
  client.Connect(new IPEndPoint(IPAddress.Loopback, 3721));                                    //Connect to the address
  Task.Run(() => ReadMessages(client));                                                        //Create and run another thread for recieving messages
  while(true)
  {
   string message=Console.ReadLine()+"\n";        //Read message from console
   client.Send(Encoding.ASCII.GetBytes(message)); //Send the message to the server
  }
 }
 private static void ReadMessages(Socket client)
 {
  while (true)
  {
   byte[] buffer = new byte[0x100];
   client.Receive(buffer, 0, 255, 0);               //Receive the message
   Console.Write(Encoding.ASCII.GetString(buffer)); //Print it to console
  }
 }
}