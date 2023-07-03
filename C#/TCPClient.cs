//Includes
 using System;
 using System.Text;
 using System.Net;
 using System.Net.Sockets;
public class TCPClient{
 public static void Main(){
  byte[] buffer=new byte[256];
  while(true){
   Socket client=new Socket(AddressFamily.InterNetwork,SocketType.Stream,ProtocolType.Tcp);
   IPEndPoint address=new IPEndPoint(IPAddress.Loopback,3721);
   string message=Console.ReadLine()+"\n";
   client.Connect(address);
   client.Send(Encoding.ASCII.GetBytes(message));
   int size=client.Receive(buffer,0,255,0,out SocketError error);
   buffer[size]=0;
   Console.Write(Encoding.ASCII.GetString(buffer));
   client.Close();}}}