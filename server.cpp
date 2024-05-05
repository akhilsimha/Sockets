#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>

using namespace std;

int main() {
  // Initialize Winsock
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    cerr << "WSAStartup failed with error: " << WSAGetLastError() << endl;
    return 1;
  }

  // Create socket
  int serverSocket = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
  if (serverSocket == INVALID_SOCKET) {
    cerr << "WSASocketA failed with error: " << WSAGetLastError() << endl;
    WSACleanup();
    return 1;
  }

  // Specify address
  SOCKADDR_IN serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8080);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  // Bind socket
  if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
    cerr << "bind failed with error: " << WSAGetLastError() << endl;
    closesocket(serverSocket);
    WSACleanup();
    return 1;
  }

  // Listen for connections
  if (listen(serverSocket, 5) == SOCKET_ERROR) {
    cerr << "listen failed with error: " << WSAGetLastError() << endl;
    closesocket(serverSocket);
    WSACleanup();
    return 1;
  }

  // Accept connection
  int clientSocket = accept(serverSocket, nullptr, nullptr);
  if (clientSocket == INVALID_SOCKET) {
    cerr << "accept failed with error: " << WSAGetLastError() << endl;
    closesocket(serverSocket);
    WSACleanup();
    return 1;
  }

  // Receive data
  char buffer[1024] = {0};
  int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
  if (bytesReceived == SOCKET_ERROR) {
    cerr << "recv failed with error: " << WSAGetLastError() << endl;
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 1;
  }

  cout << "Message from client: " << buffer << endl;

  // Close sockets
  closesocket(clientSocket);
  closesocket(serverSocket);

  // Cleanup Winsock
  WSACleanup();

  return 0;
}
