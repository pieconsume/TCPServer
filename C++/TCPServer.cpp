//Externs
 extern "C" int read(int fd,char* buffer,int buffersz);
 extern "C" int write(int fd,const char* buffer,int count);
 extern "C" int socket(int family,int type,int protocol);
 extern "C" int setsockopt(int socket,int level,int name, void* value,int valuesz);
 extern "C" int bind(int socket,void* address,int addrsz);
 extern "C" int listen(int socket,int backlog);
 extern "C" int accept(int socket,void* address,int* addrsz);
 extern "C" int close(int socket);
int main(){
 int addrlen=0x10;
 unsigned char address[]={2,0,(3721>>8),3721&0xFF};
 char buffer[0x100];
 int server=socket(2,1,0);
 int on=1;
 setsockopt(server,1,15,&on,4);
 bind(server,&address,addrlen);
 listen(server,5);
 while(1){
  int client=accept(server,&address,&addrlen);
  int size=read(client,buffer,0xFF);
  write(1,buffer,size);
  write(client,"Message recieved\n",17);
  close(client);}}