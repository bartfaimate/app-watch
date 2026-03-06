

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <termios.h>
#include <netinet/in.h>
#include <unistd.h>
char buf[256]; // waht we receive from socket

enum USBStates
{
    IDLE = 0,
    CONNECTING,
    CONNECTED,
    READY,
    DISCONNECTED,
};

enum NetworkStates {
    IDLE = 0,
    INITING,
    CONNECTING,
    CONNECTED,
    READY,
    DISCONNECTED,
};

const int portno = 7777;


int receive(char * buf) ;

int main()
{

    struct sockaddr_in serv_addr, cli_addr;
    int sockfd; /*erver file descriptor*/
    int client_sock_fd;
    int clilen; /* size of the client address */
    int len;    /* length of received data */

    printf("[SRV] Initialising....\n");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        perror("[SRV] ERROR opening socket");

    memset(&serv_addr, 0, sizeof(serv_addr)); /* clearing  */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    printf("[SRV] Waiting for incomming connection....\n");
    int opt = 1;
    /* resue address. do not block port */
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        return 1;
    }

    if (listen(sockfd, 5) < 0)
    {
        perror("listen");
        return 1;
    }
    clilen = sizeof(cli_addr);
    client_sock_fd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (client_sock_fd < 0)
    {
        perror("ERROR on accept");
    }

    len = recv(client_sock_fd, &buf, 256, 0);
    if (len > 0)
    {
        buf[len] = '\0';
        printf("Received %d characters with : '%s' \n", len, buf);
    }

    /* initialise server socket */
    /* initialise usb */
    /* listen for usb connections and disconnect */

    /* if usb connected send Operating System */
    /* send active app name */
    /* on change send active app name */
    close(sockfd);
    close(client_sock_fd);

    return 0;
}
