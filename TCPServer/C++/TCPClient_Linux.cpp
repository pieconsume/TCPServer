//Defs
 extern "C" int read(int fd, const char* buffer, int buffersz);
 extern "C" int write(int fd, const char* buffer, int count);
 extern "C" int socket(int family, int type, int protocol);
 extern "C" int connect(int socket, void* address, int addrsz);
 extern "C" int close(int socket);

int main()
{
 char buffer[0x100];
 unsigned char addr[0x10] =
 { 
  2, 0,               //Address family in LSB. 0x02 is AF_INET/IPV4
  3721>>8, 3721&0xFF, //Port in MSB
  127, 0, 0, 1,       //IP address in MSB
  0,0,0,0,0,0,0,0     //Padding
 };
 while(1)
 {
  int size = read(0, buffer, 0xFF); //Read the message from stdin
  int client = socket(2, 1, 0);     //Create the client afterwards so you don't have a useless socket sitting around
  connect(client, addr, 0x10);      //Connect to the server
  write(client, buffer, size);      //Write the message to the server
  size=read(client, buffer, 0xFF);  //Read the response from the server
  write(1, buffer, size);           //Write the response to stdout
  close(client);                    //Close the client
 }
}