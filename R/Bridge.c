//Externs
 extern void* malloc(long unsigned int size);
 extern int   read(int fd, char* buffer, int buffersz);
 extern int   write(int fd, char* buffer, int count);
 extern int   socket(int family, int type, int protocol);
 extern int   setsockopt(int socket, int level, int name, void* value, int valuesz);
 extern int   bind(int socket, void* address, int addrsz);
 extern int   listen(int socket, int backlog);
 extern int   accept(int socket, void* address, int*addrsz);
 extern int   connect(int socket, void* address, int addrsz);
 extern int   close(int socket);
//Basic C bridge for R. Search online for more info
void c_malloc(unsigned long int* size, void** result){ *result = malloc(*size); }
void c_getbyte(char** buffer, int* index, char* result){ *result = (*buffer)[*index]; }
void c_setbyte(char** buffer, int* index, char* value){(*buffer)[*index] = *value; }
void c_read(int* fd, char** buffer, int* bufsz, int* result){ *result = read(*fd, *buffer, *bufsz); }
void c_write(int* fd, char** buffer, int* bufsz, int* result){ *result = write(*fd, *buffer, *bufsz); }
void c_socket(int* family, int* type, int* protocol, int* result){ *result = socket(*family, *type, *protocol); }
void c_setsockopt(int* socket, int* level, int* name, void* value, int* valuesz, int* result){ *result = setsockopt(*socket, *level, *name, value, *valuesz); }
void c_bind(int* socket, void** address, int* addrsz, int* result){ *result = bind(*socket, *address, *addrsz); }
void c_listen(int* socket, int* backlog, int* result){ *result = listen(*socket, *backlog); }
void c_accept(int* socket, void** address, int* addrsz, int* result){ *result = accept(*socket, *address, addrsz); }
void c_connect(int* socket, void** address, int* addrsz, int* result){ *result = connect(*socket, *address, *addrsz); }
void c_close(int* socket, int* result){ *result = close(*socket); }