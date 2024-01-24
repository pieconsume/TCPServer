//Defs
 #ifdef windows
  #define sock unsigned long
  extern int WSAStartup(short int version, void* data);
  extern int closesocket(sock socket);
 #else
  #define sock int
  extern int close(int fd);
  #define closesocket close
  #endif
 extern int read(int fd, char* buffer, int count);
 extern int write(int fd, char* buffer, int count);
 extern sock socket(int af, int type, int protocol);
 extern int connect(sock socket, void* addr, int addrlen);
 extern int recv(sock socket, char* buffer, int len, int flags);
 extern int send(sock socket, char* buffer, int len, int flags);

int main()
{
 char buffer[0x100];
 char sockaddr[0x10] =
 {
  2, 0,
  3721>>8, 3721&0xFF,
  127, 0, 0, 1,
  0, 0, 0, 0, 0, 0, 0, 0,
 };
 #ifdef windows
  char wsadata[11];
  WSAStartup(0x2020, wsadata);
  #endif
 while (1)
 {
  int size = read(0, buffer, 0xFF);
  sock client = socket(2, 1, 0);
  connect(client, sockaddr, 0x10);
  send(client, buffer, size, 0);
  size = recv(client, buffer, 0xFF, 0);
  write(1, buffer, size);
  closesocket(client);
 }
}