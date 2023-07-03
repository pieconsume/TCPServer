//Includes
 using System;
 using System.Text;
 using System.Net;
 using System.Net.Sockets;
public class TCPServer{
 public static void Main(){
  byte[] buffer=new byte[256];
  Socket server=new Socket(AddressFamily.InterNetwork,SocketType.Stream,ProtocolType.Tcp);
  IPEndPoint address=new IPEndPoint(IPAddress.Any,3721);
  server.Bind(address);
  server.Listen(5);
  while(true){
   Socket client=server.Accept();
   int size=client.Receive(buffer,0,255,0,out SocketError error);
   buffer[size]=0;
   Console.Write(Encoding.ASCII.GetString(buffer));
   client.Send(Encoding.ASCII.GetBytes("Message received\n"));
   client.Close();}}}