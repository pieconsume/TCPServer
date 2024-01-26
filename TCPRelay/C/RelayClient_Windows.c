//Defs
 #define sock unsigned long long
 #define hand unsigned long long
 extern int   getchar();
 extern int   read(int fd, const char* buffer, int count);
 extern int   write(int fd, const char* buffer, int count);
 extern sock  WSASocketA(int af, int type, int protocol, void* pinfo, int group, int flags);
 extern int   connect(sock socket, void* addr, int addrlen);
 extern int   recv(sock socket, const char* buffer, int len, int flags);
 extern int   send(sock socket, const char* buffer, int len, int flags);
 extern int   WSAStartup(short int version, void* data);
 extern int   WSAGetLastError();
 extern int   WSASetLastError(int error);
 extern hand  GetStdHandle(int handle); 
 extern int   GetConsoleMode(hand console, int* settings);
 extern int   SetConsoleMode(hand console, int settings);
 extern int   WaitForSingleObject(hand handle, int timeoutms);
 extern int   WaitForMultipleObjects(int count, void* handles, int waitall, int waitms);
 extern int   PeekConsoleInputA(hand console, void* buffer, int bufsz, int* readcount);
 extern int   ReadConsoleInputA(hand console, void* buffer, int bufsz, int* readcount);
 extern int   ReadConsoleA(hand console, void* buffer, int count, int* rdcount, void* control);
 extern int   printf(const char* str, ...);
 extern hand  WSACreateEvent();
 extern int   WSAEventSelect(sock s, hand handle, long events);
 extern int   WSAEnumNetworkEvents(sock s, hand event, void* data);
 extern int   GetConsoleScreenBufferInfo(hand console, void* output);
 extern void* memset(void* buffer, int index, unsigned long long count);
 extern int   GetLastError();

int main()
{
 int bufindex = 0;
 char inbuffer[0x100];
 char outbuffer[0x100];
 char eventbuf[64];
 char consbuf[32];
 char empty[256];
 memset(empty, 0, 256);
 int trash;
 unsigned char addr[0x10] =
 {
  2, 0,
  3721>>8, 3721&0xFF,
  127, 0, 0, 1,
  0, 0, 0, 0, 0, 0, 0, 0,
 };
 char wsadata[18];
 hand fds[2]; 
 WSAStartup(0x2020, wsadata);
 sock client = WSASocketA(2, 1, 0, 0, 0, 0);
 connect(client, addr, 0x10);
 hand event = WSACreateEvent();
 WSAEventSelect(client, event, 1);
 fds[0] = event;
 fds[1] = GetStdHandle(-10);
 GetConsoleMode(fds[1], &trash);
 SetConsoleMode(fds[1], trash & 0xFD);
 while (1)
 {
  int result = WaitForMultipleObjects(2, fds, 0, -1);
  if (result == 0)
  {
   int size = recv(client, inbuffer, 0xFF, 0);
   if (size > 0)
   {
    int result = GetConsoleScreenBufferInfo(GetStdHandle(-11), consbuf);
    printf("\r");
    write(1, empty, ((short*)consbuf)[7]-((short*)consbuf)[5]);
    printf("\r");
    write(1, inbuffer, size);
    write(1, outbuffer, bufindex);
    WSAEnumNetworkEvents(client, event, inbuffer);
   }
   else
   {
    printf("error yo! %i\n", WSAGetLastError());
   }
  }
  else if (result == 1 && PeekConsoleInputA(fds[1], eventbuf, 1, &trash) != 0)
  {
   if (eventbuf[0] == 1 && eventbuf[4] == 1)
   {
    ReadConsoleA(fds[1], outbuffer+bufindex, 1, &trash, 0);
    printf("%c", outbuffer[bufindex]);
    if (outbuffer[bufindex] == 13)
    { 
     outbuffer[bufindex] = '\n';
     printf("\n");
     send(client, outbuffer, bufindex+1, 0);
     bufindex = 0;
    }
    else if (outbuffer[bufindex] == 8) 
    { 
     outbuffer[bufindex] = 0;
     if (bufindex > 0) { bufindex--; } 
     int result = GetConsoleScreenBufferInfo(GetStdHandle(-11), consbuf);
     printf("\r");
     write(1, empty, ((short*)consbuf)[7]-((short*)consbuf)[5]);
     printf("\r");
     write(1, outbuffer, bufindex);
    }
    else { bufindex++; }
   }
   else
   {
    ReadConsoleInputA(fds[1], eventbuf, 1, &trash);
   }
  }
 }
}