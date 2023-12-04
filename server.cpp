// UDP Server
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
  // Create a UDP socket
  int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (serverSocket < 0)
  {
    perror("Failed to create socket");
    return 1;
  }

  // Bind the socket to a specific address and port
  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(12345); // Choose a port
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
  {
    perror("Failed to bind");
    return 1;
  }

  char buffer[1024];
  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);

  while (true)
  {
    // Receive data from the client
    ssize_t bytesRead = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (bytesRead < 0)
    {
      perror("Error in recvfrom");
      break;
    }

    // Print received message
    buffer[bytesRead] = '\0';
    std::cout << "Received: " << buffer << std::endl;

    // Send a response back to the client
    const char* response = "Hello from server!";
    sendto(serverSocket, response, strlen(response), 0, (struct sockaddr*)&clientAddr, clientAddrLen);
  }

  // Close the socket
  close(serverSocket);

  return 0;
}
