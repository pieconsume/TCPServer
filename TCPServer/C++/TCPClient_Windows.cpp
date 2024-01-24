//Defs              
 #define ulong unsigned long
 extern "C" int read(int fd, char* buffer, int count);
 extern "C" int write(int fd, char* buffer, int count);
 extern "C" int WSAStartup(short int version, void* data);
 extern "C" ulong socket(int af, int type, int protocol);
 extern "C" int connect(ulong socket, void* addr, int addrlen);
 extern "C" int recv(ulong socket, const char* buffer, int len, int flags);
 extern "C" int send(ulong socket, const char* buffer, int len, int flags);
 extern "C" int closesocket(ulong socket);

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
 char wsadata[16];
 WSAStartup(0x2020, wsadata);
 while (1)
 {
  int size = read(0, buffer, 0xFF);
  ulong client = socket(2, 1, 0);
  connect(client, addr, 0x10);
  send(client, buffer, size, 0);
  size = recv(client, buffer, 0xFF, 0);
  write(1, buffer, size);
  closesocket(client);
 }
}