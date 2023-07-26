# TCPServer
Basic TCPServer/Client in several languages

For simplicity there is no error handling except in languages which force you to handle all errors.
The programs will also hang if a connection is made but no data is sent and the connection is not terminated.

When available programs will use the functions provided by their standard libraries. Otherwise libc functions will be used via the programming language's FFI.

All programs have largely the same behavior. The server will recieve messages on port 3721 and print them to console. The client will read a message from console then send it to the server.
The program is designed such that the server can handle any number of clients on a single thread. This design is ideal for any small scale server that only needs to respond to basic commands from a client.
It is also a good starting point for creating more complex programs such as relays or databases.