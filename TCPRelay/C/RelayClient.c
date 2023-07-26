//Header files could be included instead but this lets you easily view function prototypes you use
 extern int read(int fd, char* buffer, int buffersz);
 extern int write(int fd, char* buffer, int count);
 extern int socket(int family, int type, int protocol);
 extern int connect(int socket, void* address, int addrsz);
 extern int poll(void*, int, int);
 
int main()
{
 char addr[0x10] = 
 { 
  2, 0,               //Address family in LSB. 0x02 is AF_INET/IPV4
  3721>>8, 3721&0xFF, //Port in MSB
  127, 0, 0, 1,       //IP address in MSB
  0,0,0,0,0,0,0,0     //Padding
 };
 char buffer[0x100];
 int fds[] = { 0, 1, 0, 1 };   //Entry 0 is stdin, entry 1 is the client fd
 int client = socket(2, 1, 0); //Create the client
 fds[2] = client;              //Store the fd for poll()
 connect(client, addr, 0x10);  //Connect to the server
 while(1)
 {
  poll(fds, 2, -1);
  if (fds[1]>>16 == 1)
  {
   fds[1] = 1;                   //Clear the event notifier
   int size = read(0, buffer, 0xFF); //Read from stdin
   write(client, buffer, size);  //Send the message to the server
  }
  if (fds[3]>>16 == 1)
  {
   fds[3] = 1;                        //Clear the event notifier
   int size = read(client, buffer, 0xFF); //Read message from the server
   write(1, buffer, size);            //Write message to stdout
  }
 }
}