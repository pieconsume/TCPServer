//Defs
 #define sock unsigned long long
 extern int read(int fd, const char* buffer, int count);
 extern int write(int fd, const char* buffer, int count);
 extern int printf(const char* str, ...);
 extern int WSAStartup(short int version, void* data);
 extern int WSAPoll(void* fds, unsigned long count, int timeoutms);
 extern sock socket(int af, int type, int protocol);
 extern int setsockopt(int socket, int level, int name,void* value, int valuesz);
 extern int bind(sock socket, void* addr, int addrlen);
 extern int listen(sock socket, int backlog);
 extern sock accept(sock listener, void* addrinfo, int* addrlen);
 extern int recv(sock socket, const char* buffer, int len, int flags);
 extern int send(sock socket, const char* buffer, int len, int flags);
 extern int closesocket(sock socket);

int main()
{
 struct sockfd { sock socket; short events; short revents; };
 char buffer[256];
 unsigned char addr[0x10] =
 {
  2, 0,               //Address family in LSB. 0x02 is AF_INET/IPV4
  3721>>8, 3721&0xFF, //Port in MSB
  0,0,0,0,            //IP address in MSB. 0.0.0.0 allows any address to connect
  0,0,0,0,0,0,0,0     //Padding
 };
 char wsadata[18];
 WSAStartup(0x0202, wsadata);
 struct sockfd sockfds[0x100];
 for (int i = 0; i < 0x100; i++)
 {
  sockfds[i].socket = -1;
  sockfds[i].events = 0x300;
 }
 sock server = socket(2, 1, 0); //Create a new socket
 bind(server, addr, 0x10);      //Bind address
 listen(server, 5);             //Set socket as listener
 sockfds[0].socket = server;    //Set index 0 to be our server socket
 int conncount = 1;
 while (1)
 {
  WSAPoll(sockfds, conncount, -1);
  if (sockfds[0].revents && 1)
  {
   sock client = accept(server, 0, 0);
   sockfds[conncount].socket = client;
   conncount++;
   printf("New connection. Total connections: %i\n", conncount-1);
  }
  else
  {
   for (int i = 1; i < conncount; i++)
   {
    if (sockfds[i].revents && 0x300 != 0)
    {
     sockfds[i].revents = 0;
     int size = recv(sockfds[i].socket, buffer, 0xFF, 0);
     if (size <= 0)
     {
      closesocket(sockfds[i].socket);
      sockfds[i].socket = sockfds[conncount-1].socket;
      sockfds[i].revents = sockfds[conncount-1].revents;
      conncount--;
      i--;
      printf("Connection lost. Total connections: %i\n", conncount-1);
     }
     else
     {
      for (int j = 1; j < conncount; j++)
      {
       if (i == j) { continue; }
       write(1, buffer, size);
       if (send(sockfds[j].socket, buffer, size, 0) <= 0)
       {
        closesocket(sockfds[j].socket);
        sockfds[j].socket = sockfds[conncount-1].socket;
        sockfds[j].revents = sockfds[conncount-1].revents;
        conncount--;
        j--;
        printf("Connection lost. Total connections: %i\n", conncount-1);
       }
      }
     }
    }
   }
  }
 }
}