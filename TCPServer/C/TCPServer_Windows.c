#define ulong unsigned long
extern int read(int fd, char* buffer, int count);
extern int write(int fd, char* buffer, int count);
extern int WSAStartup(short int version, void* data);
extern ulong socket(int af, int type, int protocol);
extern int setsockopt(int socket, int level, int name,void* value, int valuesz);
extern int bind(ulong socket, void* addr, int addrlen);
extern int listen(ulong socket, int backlog);
extern ulong accept(ulong listener, void* addrinfo, int addrlen);
extern int recv(ulong socket, char* buffer, int len, int flags);
extern int send(ulong socket, char* buffer, int len, int flags);
extern int closesocket(ulong socket);

int main()
{
 char buffer[256];
 char wsadata[11];
 char sockaddr[0x10] =
 {
  2, 0,
  3721>>8, 3721&0xFF,
  0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
 };
 int on = 1;
 WSAStartup(0x0202, wsadata);
 ulong listener = socket(2, 1, 0);
 setsockopt(listener, 1, 15, &on, 4);
 bind(listener, sockaddr, 0x10);
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