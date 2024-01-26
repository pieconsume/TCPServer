//Defs
 #define sock unsigned long long
 extern int read(int fd, const char* buffer, int count);
 extern int write(int fd, const char* buffer, int count);
 extern int WSAStartup(short int version, void* data);
 extern sock socket(int af, int type, int protocol);
 extern int connect(sock socket, void* addr, int addrlen);
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
  127, 0, 0, 1,
  0, 0, 0, 0, 0, 0, 0, 0,
 };
 char wsadata[18];
 WSAStartup(0x2020, wsadata);
 while (1)
 {
  int size = read(0, buffer, 0xFF);
  sock client = socket(2, 1, 0);
  connect(client, addr, 0x10);
  send(client, buffer, size, 0);
  size = recv(client, buffer, 0xFF, 0);
  write(1, buffer, size);
  closesocket(client);
 }
}