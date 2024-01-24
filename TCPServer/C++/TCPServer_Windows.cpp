#define ulong unsigned long
extern "C" int read(int fd, char* buffer, int count);
extern "C" int write(int fd, char* buffer, int count);
extern "C" int WSAStartup(short int version, void* data);
extern "C" ulong socket(int af, int type, int protocol);
extern "C" int setsockopt(int socket, int level, int name,void* value, int valuesz);
extern "C" int bind(ulong socket, void* addr, int addrlen);
extern "C" int listen(ulong socket, int backlog);
extern "C" ulong accept(ulong listener, void* addrinfo, int addrlen);
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
  0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
 };
 int on = 1;
 char wsadata[16];
 WSAStartup(0x0202, wsadata);
 ulong listener = socket(2, 1, 0);
 setsockopt(listener, 1, 15, &on, 4);
 bind(listener, addr, 0x10);
 listen(listener, 5);
 while (1)
 {
  ulong client = accept(listener, 0, 0);
  int size = recv(client, buffer, 0xFF, 0);
  write(1, buffer, size);
  send(client, "Message received\n", 17, 0);
  closesocket(client);
 }
}