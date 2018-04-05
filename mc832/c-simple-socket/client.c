#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(void) {
    int socket_fd = 0, n = 0;
    char rec_buffer[1025];
    struct sockaddr_in serv_addr;

    memset(rec_buffer, 0x00, sizeof(rec_buffer));

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Could not create socket\n");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(socket_fd, (struct sockaddr *) &serv_addr,
                sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return 1;
    }

    while ((n = read(socket_fd, rec_buffer, sizeof(rec_buffer) -1)) > 0) {
        rec_buffer[n] = 0;
        if (fputs(rec_buffer, stdout) == EOF) {
            printf("Error\n");
        }
    }
    if (n < 0) {
        printf("Read Error\n");
    }

    return 0;
}
