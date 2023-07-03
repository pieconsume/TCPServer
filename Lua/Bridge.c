//Includes
 #include <lua.h>
 #include <lauxlib.h>
 #include <lualib.h>
 extern void* malloc(long unsigned int size);
 extern int   read(int fd,const char* buffer,int buffersz);
 extern int   write(int fd,const char* buffer,int count);
 extern int   socket(int family,int type,int protocol);
 extern int   setsockopt(int socket,int level,int name,void* value,int valuesz);
 extern int   bind(int socket,void* address,int addrsz);
 extern int   listen(int socket,int backlog);
 extern int   connect(int socket,void* address,int addrsz);
 extern int   accept(int socket,void* address,int*addrsz);
 extern int   close(int socket);
static int c_malloc(lua_State* L){
 int   size=lua_tonumber(L,-1);
 void* ptr =malloc(size);
 lua_pushnumber(L,(long)ptr);
 return 1;}
static int c_getbyte(lua_State* L){
 long ptr  =lua_tonumber(L,-2);
 int  index=lua_tonumber(L,-1);
 lua_pushnumber(L,((char*)ptr)[index]);
 return 1;
 }
static int c_setbyte(lua_State* L){
 long ptr  =lua_tonumber(L,-3);
 int  index=lua_tonumber(L,-2);
 char value=lua_tonumber(L,-1);
 ((char*)ptr)[index]=value;
 return 0;
 }
static int c_getint(lua_State* L){
 long ptr  =lua_tonumber(L,-2);
 int  index=lua_tonumber(L,-1);
 lua_pushnumber(L,((int*)ptr)[index]);
 return 1;
 }
static int c_setint(lua_State* L){
 long ptr  =lua_tonumber(L,-3);
 int  index=lua_tonumber(L,-2);
 int  value=lua_tonumber(L,-1);
 ((int*)ptr)[index]=value;
 return 0;
 }
static int c_setstr(lua_State* L){
 long        ptr   =lua_tonumber(L,-3);
 int         length=lua_tonumber(L,-2);
 const char* value =lua_tostring(L,-1);
 for(int i=0;i<length;i++){((char*)ptr)[i]=value[i];}
 return 0;}
static int c_read(lua_State* L){
 int  file  =lua_tonumber(L,-3);
 long buffer=lua_tonumber(L,-2);
 int  size  =lua_tonumber(L,-1);
 lua_pushnumber(L,read(file,(char*)buffer,size));
 return 1;}
static int c_write(lua_State* L){
 int  file  =lua_tonumber(L,-3);
 long buffer=lua_tonumber(L,-2);
 int  size  =lua_tonumber(L,-1);
 lua_pushnumber(L,write(file,(char*)buffer,size));
 return 1;}
static int c_socket(lua_State* L){
 int family  =lua_tonumber(L,-3);
 int type    =lua_tonumber(L,-2);
 int protocol=lua_tonumber(L,-1);
 lua_pushnumber(L,socket(family,type,protocol));
 return 1;}
static int c_setsockopt(lua_State* L){
 int  socket =lua_tonumber(L,-5);
 int  level  =lua_tonumber(L,-4);
 int  name   =lua_tonumber(L,-3);
 long value  =lua_tonumber(L,-2);
 int  valuesz=lua_tonumber(L,-1);
 lua_pushnumber(L,setsockopt(socket,level,name,(void*)value,valuesz));
 return 1;}
static int c_bind(lua_State* L){
 int  socket =lua_tonumber(L,-3);
 long address=lua_tonumber(L,-2);
 int  addrsz =lua_tonumber(L,-1);
 lua_pushnumber(L,bind(socket,(void*)address,addrsz));
 return 1;}
static int c_listen(lua_State* L){
 int socket =lua_tonumber(L,-2);
 int backlog=lua_tonumber(L,-1);
 lua_pushnumber(L,listen(socket,backlog));
 return 1;}
static int c_connect(lua_State* L){
 int  socket =lua_tonumber(L,-3);
 long address=lua_tonumber(L,-2);
 int  addrsz =lua_tonumber(L,-1);
 lua_pushnumber(L,connect(socket,(void*)address,addrsz));
 return 1;}
static int c_accept(lua_State* L){
 int  socket =lua_tonumber(L,-3);
 long address=lua_tonumber(L,-2);
 long addrsz =lua_tonumber(L,-1);
 lua_pushnumber(L,accept(socket,(void*)address,(int*)addrsz));
 return 1;}
static int c_close(lua_State* L){
 int socket=lua_tonumber(L,-1);
 lua_pushnumber(L,close(socket));
 return 1;}
int luaopen_Bridge(lua_State* L){
 lua_register(L,"c_malloc",c_malloc);
 lua_register(L,"c_getbyte",c_getbyte);
 lua_register(L,"c_setbyte",c_setbyte);
 lua_register(L,"c_getint",c_getint);
 lua_register(L,"c_setint",c_setint);
 lua_register(L,"c_setstr",c_setstr);
 lua_register(L,"c_read",c_read);
 lua_register(L,"c_write",c_write);
 lua_register(L,"c_socket",c_socket);
 lua_register(L,"c_setsockopt",c_setsockopt);
 lua_register(L,"c_bind",c_bind);
 lua_register(L,"c_listen",c_listen);
 lua_register(L,"c_connect",c_connect);
 lua_register(L,"c_accept",c_accept);
 lua_register(L,"c_close",c_close);
 return 0;}