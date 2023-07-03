# TCPServer
Basic TCPServer/Client in several languages

All implementations should be compatible and have the same behavior.

The server will create a TCP server on port 3721, listen for incoming connections, read the first packet from any connection, then close the connection.

The client will read a message from the console, create a TCP client, connect to 127.0.0.1:3721 (loopback address), send the message to the server, then close the connection.

This design is simple and effective for handling messages from multiple clients without needing to worry about keeping track of multiple connections or multithreading.
