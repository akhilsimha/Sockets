#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>

using namespace std;

int main() {
  // Initialize Winsock
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2, 2), &wsaData);

  // Create socket
  int clientSocket = WSASocketA(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);

  // Specify server address
  SOCKADDR_IN serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8080);
  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); 

  // Connect to server
  connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

  // Send message
  const char* message = "Hello, server!";
  send(clientSocket, message, strlen(message), 0);

  // Print confirmation
  cout << "Message sent to server: " << message << endl;

  // Close socket
  closesocket(clientSocket);

  // Cleanup Winsock
  WSACleanup();

  return 0;
}
