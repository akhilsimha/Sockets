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
  // TCP Implementation
  //int serverSocket = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
  //UDP Implementation
  int serverSocket = WSASocketA(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);

  // Specify address
  SOCKADDR_IN serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8080);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  // Bind socket
  bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

  // Listen for connections (only for TCP Connection)
  // listen(serverSocket, 5);

  // Accept connection
  //int clientSocket = accept(serverSocket, nullptr, nullptr);

  // Receive data
  char buffer[1024] = {0};
  //recv(clientSocket, buffer, sizeof(buffer), 0);
  struct sockaddr_in clientAddress;
  int clientAddressLength = sizeof(clientAddress);
  recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddress, &clientAddressLength);

  // Print message
  cout << "Message from client: " << buffer << endl;

  // Close sockets
  //closesocket(clientSocket);
  closesocket(serverSocket);

  // Cleanup Winsock
  WSACleanup();

  return 0;
}
