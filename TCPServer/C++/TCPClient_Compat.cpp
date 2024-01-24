//Defs
 #define windows
 #ifdef windows
  #define sock unsigned long
  extern "C" int WSAStartup(short int version, void* data);
  extern "C" int closesocket(sock socket);
 #else
  #define sock int
  extern "C" int close(int fd);
  #define closesocket close
  #endif
 extern "C" int read(int fd, const char* buffer, int count);
 extern "C" int write(int fd, const char* buffer, int count);
 extern "C" sock socket(int af, int type, int protocol);
 extern "C" int connect(sock socket, void* addr, int addrlen);
 extern "C" int recv(sock socket, const char* buffer, int len, int flags);
 extern "C" int send(sock socket, const char* buffer, int len, int flags);

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
 #ifdef windows
  char wsadata[16];
  WSAStartup(0x0202, wsadata);
  #endif
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