//Defs
 extern "C" int read(int fd, const char* buffer, int buffersz);
 extern "C" int write(int fd, const char* buffer, int count);
 extern "C" int socket(int family, int type, int protocol);
 extern "C" int setsockopt(int socket, int level, int name,void* value, int valuesz);
 extern "C" int bind(int socket, void* address, int addrsz);
 extern "C" int listen(int socket, int backlog);
 extern "C" int accept(int socket, void* address, int* addrsz);
 extern "C" int close(int socket);
 
int main()
{
 char buffer[0x100];
 unsigned char addr[0x10] =
 {
  2, 0,               //Address family in LSB. 0x02 is AF_INET/IPV4
  3721>>8, 3721&0xFF, //Port in MSB
  0, 0, 0, 0,         //IP address in MSB. 0.0.0.0 allows any address to connect
  0,0,0,0,0,0,0,0     //Padding
 };
 int on = 1;
 int server = socket(2, 1, 0);      //Create the server socket
 setsockopt(server, 1, 15, &on, 4); //Set reuse for quick restarts
 bind(server, &addr, 0x10);      //Bind the address
 listen(server, 5);                 //Set the socket as a listener
 while(1)
 {
  int client = accept(server, 0, 0); //Accept the client
  int size = read(client, buffer, 0xFF);        //Read a message from the client
  write(1, buffer, size);                       //Write the message to stdout
  write(client, "Message recieved\n", 17);      //Send the response to the client
  close(client);                                //Close the client
 }
}