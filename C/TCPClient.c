//Externs
 extern int read(int fd,char* buffer,int buffersz);
 extern int write(int fd,char* buffer,int count);
 extern int socket(int family,int type,int protocol);
 extern int connect(int socket,void* address,int addrsz);
 extern int close(int socket);
int main(){
 char addr[]={2,0,3721>>8,3721&0xFF,127,0,0,1};
 char buffer[0x100];
 while(1){
  int size=read(0,buffer,0xFF);
  int client=socket(2,1,0);
  connect(client,&addr,0x10);
  write(client,buffer,size);
  size=read(client,buffer,0xFF);
  write(1,buffer,size);
  close(client);}}