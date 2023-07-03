//Externs
 extern int read(int fd,char* buffer,int buffersz);
 extern int write(int fd,char* buffer,int count);
 extern int socket(int family,int type,int protocol);
 extern int setsockopt(int socket,int level,int name,void* value,int valuesz);
 extern int bind(int socket,void* address,int addrsz);
 extern int listen(int socket,int backlog);
 extern int accept(int socket,void* address,int*addrsz);
 extern int close(int socket);
int main(){
 char addr[]={2,0,3721>>8,3721&0xFF}; // 0..1 is address type in LSB, 2..3 is port in MSB
 int addrlen=0x10;
 char buffer[0x100];
 int server=socket(2,1,0);
 int on=1;
 setsockopt(server,1,15,&on,4);
 bind(server,&addr,addrlen);
 listen(server,5);
 while (1){
  int client=accept(server,&addr,&addrlen);
  int size=read(client,buffer,0xFF);
  write(1,buffer,size);
  write(client,"Message recieved\n",17);
  close(client);}}