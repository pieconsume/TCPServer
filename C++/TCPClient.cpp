//Externs
 extern "C" int read(int fd,char* buffer,int buffersz);
 extern "C" int write(int fd,char* buffer,int count);
 extern "C" int socket(int family,int type,int protocol);
 extern "C" int connect(int socket,void* address,int addrsz);
 extern "C" int close(int socket);
int main(){
 unsigned char address[]={2,0,3721>>8,3721&0xFF,127,0,0,1};
 char buffer[0x100];
 while(1){
  int size=read(0,buffer,0xFF);
  int client=socket(2,1,0);
  connect(client,&address,0x10);
  write(client,buffer,size);
  size=read(client,buffer,0xFF);
  write(1,buffer,size);
  close(client);
 }
}