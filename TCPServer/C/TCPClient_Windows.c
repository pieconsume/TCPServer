//Defs
 #define ulong unsigned long
 extern int read(int fd, char* buffer, int count);
 extern int write(int fd, char* buffer, int count);
 extern int WSAStartup(short int version, void* data);
 extern ulong socket(int af, int type, int protocol);
 extern int connect(ulong socket, void* addr, int addrlen);
 extern int recv(ulong socket, char* buffer, int len, int flags);
 extern int send(ulong socket, char* buffer, int len, int flags);
 extern int closesocket(ulong socket);

int main()
{
	char buffer[0x100];
 char wsadata[11];
 char sockaddr[0x10] =
 {
 	2, 0,
 	3721>>8, 3721&0xFF,
 	127, 0, 0, 1,
 	0, 0, 0, 0, 0, 0, 0, 0,
 };
	WSAStartup(0x2020, wsadata);
	while (1)
	{
		int size = read(0, buffer, 0xFF);
	 ulong client = socket(2, 1, 0);
	 connect(client, sockaddr, 0x10);
		send(client, buffer, size, 0);
		size = recv(client, buffer, 0xFF, 0);
		write(1, buffer, size);
		closesocket(client);
	}
}