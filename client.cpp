// UDP Client
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
  // Create a UDP socket
  int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (clientSocket < 0)
  {
    perror("Failed to create socket");
    return 1;
  }

  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(12345);                  // Use the same port as the server
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

  const char* message = "Hello from client!";
  ssize_t messageLength = strlen(message);

  // Send the message to the server
  sendto(clientSocket, message, messageLength, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

  // char buffer[1024];

  // // Receive the response from the server
  // ssize_t bytesRead = recvfrom(clientSocket, buffer, sizeof(buffer), 0, NULL, NULL);
  // if (bytesRead < 0)
  // {
  //   perror("Error in recvfrom");
  // }
  // else
  // {
  //   buffer[bytesRead] = '\0';
  //   std::cout << "Received from server: " << buffer << std::endl;
  // }

  // Close the socket
  close(clientSocket);

  return 0;
}
