//Defs
 extern int read(int fd, char* buffer, int count);
 extern int write(int fd, char* buffer, int count);
 extern int socket(int family, int type, int protocol);
 extern int setsockopt(int socket, int level, int name,void* value, int valuesz);
 extern int bind(int socket, void* address, int addrsz);
 extern int listen(int socket, int backlog);
 extern int accept(int socket, void* address, int* addrsz);
 extern int close(int socket);
 extern int poll(void* ufds, int count, int waitms);

int main()
{
 char addr[0x10] = 
 { 
  2, 0,               //Address family in LSB. 0x02 is AF_INET/IPV4
  3721>>8, 3721&0xFF, //Port in MSB
  0, 0, 0, 0,         //IP address in MSB. 0.0.0.0 allows any address to connect
  0,0,0,0,0,0,0,0     //Padding
 };
 int addrlen, on = 1;
 char buffer[0x100];
 int sockfds[0x400]; //Buffer for storing clients formatted for poll() calls. The format has one int for the fd, then two shorts for requested/recieved events.
 for(int i = 0; i < 0x400; i += 2) 
 {
  sockfds[i+0] = -1; //Set all file descriptors to -1 so they arent checked
  sockfds[i+1] = +1; //Request the POLLIN (ready to read) event
 }
 int server = socket(2, 1, 0);      //Create a new socket
 sockfds[0] = server;               //Set index 0 to be our server socket
 setsockopt(server, 1, 15, &on, 4); //Set reuse for quick restarts
 bind(server, addr, 0x10);          //Bind address
 listen(server, 5);                 //Set socket as listener
 while(1)
 {
  poll(sockfds, 0x200, -1); //Poll all fds indefinitely
  if(sockfds[1]>>16 == 1)   //Check if the server has recieved a new connection request
  {
   int client = accept(server, addr, &addrlen); //Accept the request
   for(int i = 2; i < 0x400; i += 2)
   {
    if(sockfds[i] == -1)
    {
      sockfds[i] = client;                      //Find a free space to store the client fd
      break;
    }
    if (i==0x1FF) { close(client); }            //Close the connection if there is no space. You may want to inform the client of this
   }
  }
  else                      //Otherwise one or more clients are sending a message
  {
   for(int i = 2; i < 0x400; i += 2)
   {
    if(sockfds[i+1]>>16 == 1)                   //Check clients for messages
    {
     sockfds[i+1] = 1;                          //Clear the event notifier
     int size = read(sockfds[i], buffer, 0xFF); //Read the message from the client
     if(size == 0)                              //If the message is 0 length then the client has closed the connection
     {
      close(sockfds[i]); //Close the client
      sockfds[i] = -1;   //Clear the fd index
     }
     else                                       //Otherwise relay the message to all other clients
     {
      for(int j = 2; j < 0x400; j += 2)
      {
       if (i==j) { continue; }                  //Dont echo back to the client that sent the message
       if(write(sockfds[j], buffer, size) == 0) //If the write returns 0 then the client has closed the connection
       {                                        //Note that there may still be data to read from the client. I ignore this here for simplicity
        close(sockfds[j]); //Close the client
        sockfds[j] = -1;   //Clear the fd index
       }
      }
     }
    }
   }
  }
 }
}