#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(void) {
    int listen_fd = 0, conn_fd = 0;
    struct sockaddr_in serv_addr;

    char send_buffer[1025];

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_fd <= 0) {
        printf("Could not create a socket\n");
        return 1;
    }

    printf("Socket Created\n");

    memset(&serv_addr, 0x00, sizeof(serv_addr));
    memset(send_buffer, 0x00, sizeof(send_buffer));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    if (bind(listen_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr))
            < 0) {
        printf("Coult not bind this port\n");
        return 1;
    }

    printf("Bind Ok...\n");

    if (listen(listen_fd, 10) == -1) {
        printf("Failed to Listen\n");
        return 1;
    }

    printf("Listen Ok...\n");

    while(1) {
        conn_fd = accept(listen_fd, NULL, NULL);
        strcpy(send_buffer, "Message from the Server");
        write(conn_fd, send_buffer, strlen(send_buffer));
        close(conn_fd);
        sleep(1);
    }

    return 0;
}
