//Header files could be included instead but this lets you easily view function prototypes you use
 extern int read(int fd, char* buffer, int buffersz);
 extern int write(int fd, char* buffer, int count);
 extern int socket(int family, int type, int protocol);
 extern int setsockopt(int socket, int level, int name,void* value, int valuesz);
 extern int bind(int socket, void* address, int addrsz);
 extern int listen(int socket, int backlog);
 extern int accept(int socket, void* address, int* addrsz);
 extern int close(int socket);
 
int main()
{
 char addr[0x10] =
 {
  2, 0,               //Address family in LSB. 0x02 is AF_INET/IPV4
  3721>>8, 3721&0xFF, //Port in MSB
  0, 0, 0, 0,         //IP address in MSB. 0.0.0.0 allows any address to connect
  0,0,0,0,0,0,0,0     //Padding
 };
 char buffer[0x100];
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