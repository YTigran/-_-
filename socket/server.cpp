#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        return -1;
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Bind failed");
        close(server_socket);
        return -1;
    }

    if (listen(server_socket, 10) == -1) {
        perror("Listen failed");
        close(server_socket);
        return -1;
    }

    std::cout << "Server is listening on port 8080..." << std::endl;

    int client_socket = accept(server_socket, nullptr, nullptr);
    if (client_socket == -1) {
        perror("Accept failed");
        close(server_socket);
        return -1;
    }

    const char* response = "Hello, Client!";

    char buffer[1024] = {0};
    ssize_t bytes_received;
    while (true) {
        bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        send(client_socket, response, strlen(response), 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            std::cout << "Received from client: " << buffer << std::endl;
        }
    }

    close(client_socket);
    close(server_socket);
    return 0;
}
