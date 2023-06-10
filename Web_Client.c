#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8000
#define BUFFER_SIZE 1024

void Client_Init() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    const char *request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP address from text to binary format
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    // Send the request to the server
    send(sock, request, strlen(request), 0);
    printf("Request sent to the server\n");

    // Receive and print the response from the server
    while ((valread = read(sock, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[valread] = '\0';
        printf("%s", buffer);
    }

    close(sock);
}
