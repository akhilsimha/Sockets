This project implements a basic TCP/IP server-client communication system using the Winsock library in C++. It demonstrates fundamental network programming concepts like socket creation, connection establishment, data exchange, and socket closure.

**Functionality:**

Server:
- Initializes Winsock for network communication.
- Creates a TCP/IP socket.
- Binds the socket to a specific port.
- Listens for incoming client connections.
- Accepts a connection from a client.
- Receives data from the connected client.
- Closes the client socket.
- Cleans up Winsock resources.

Client:
- Initializes Winsock.
- Creates a TCP/IP socket.
- Connects the socket to the server's IP address and port.
- Sends data to the server.
- Closes the socket.
- Cleans up Winsock resources.
