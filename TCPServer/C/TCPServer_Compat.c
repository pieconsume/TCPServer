//Defs
 #define windows
 #ifdef windows
  #define sock unsigned long
  extern int WSAStartup(short int version, void* data);
  extern int closesocket(sock socket);
 #else
  #define sock int
  extern int close(int fd);
  #define closesocket close
  #endif
 extern int write(int fd, const char* buffer, int count);
 extern sock socket(int af, int type, int protocol);
 extern int setsockopt(sock socket, int level, int name,void* value, int valuesz);
 extern int bind(sock socket, void* addr, int addrlen);
 extern int listen(sock socket, int backlog);
 extern sock accept(sock listener, void* addrinfo, int* addrlen);
 extern int recv(sock socket, const char* buffer, int len, int flags);
 extern int send(sock socket, const char* buffer, int len, int flags);

int main()
{
 char buffer[0x100];
 unsigned char addr[0x10] =
 {
  2, 0,               //Address family in LSB. 0x02 is AF_INET/IPV4
  3721>>8, 3721&0xFF, //Port in MSB
  0,0,0,0,            //IP address in MSB. 0.0.0.0 allows any address to connect
  0,0,0,0,0,0,0,0     //Padding
 };
 int on = 1;
 #ifdef windows
  char wsadata[18];
  WSAStartup(0x0202, wsadata);
  #endif
 sock listener = socket(2, 1, 0);
 setsockopt(listener, 1, 15, &on, 4);
 bind(listener, addr, 0x10);
 listen(listener, 5);
 while (1)
 {
  sock client = accept(listener, 0, 0);
  int size = recv(client, buffer, 0xFF, 0);
  write(1, buffer, size);
  send(client, "Message received\n", 17, 0);
  closesocket(client);
 }
}