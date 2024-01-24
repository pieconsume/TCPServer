//Defs
 #define sock unsigned long
 extern int write(int fd, const char* buffer, int count);
 extern int WSAStartup(short int version, void* data);
 extern sock socket(int af, int type, int protocol);
 extern int setsockopt(int socket, int level, int name,void* value, int valuesz);
 extern int bind(sock socket, void* addr, int addrlen);
 extern int listen(sock socket, int backlog);
 extern sock accept(sock listener, void* addrinfo, int addrlen);
 extern int recv(sock socket, const char* buffer, int len, int flags);
 extern int send(sock socket, const char* buffer, int len, int flags);
 extern int closesocket(sock socket);

int main()
{
 char buffer[0x100];
 unsigned char addr[0x10] =
 {
  2, 0,
  3721>>8, 3721&0xFF,
  0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
 };
 int on = 1;
 char wsadata[16];
 WSAStartup(0x0202, wsadata);
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