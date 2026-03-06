/************************************************************************
 * Author:
 *      Mate Bartfai
 * Purpose:
 *      
 ************************************************************************/

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

/** */
typedef enum {
  USB_DLE = 0,
  USB_ONNECTING,
  USB_ONNECTED,
  USB_EADY,
  USB_ISCONNECTED,
} USBStates_t;

/** */
typedef enum {
  NET_IDLE = 0,
  NET_INITING,
  NET_INITED,
  NET_CONNECTING,
  NET_CONNECTED,
  NET_READY,
  NET_DISCONNECTED,
  NET_FAIL,
} NetworkStates_t;

const int portno = 7777;
const uint16_t BUFSIZE = 256;

uint8_t init_server();
int receive(int *client, char *buf, int buf_len);

int modify(int *pint) {

  *pint = 12;

  return 0;
}

static NetworkStates_t network_state = NET_IDLE;


/**
 * Main program
 */
int main() {
  struct sockaddr_in cli_addr;
  int sockfd; /*erver file descriptor*/
  int client_sock_fd;
  int clilen;        /* size of the client address */
  int len;           /* length of received data */
  char buf[BUFSIZE]; // waht we receive from socket

  int test = 0;

  modify(&test);

  if (12 != test) {

    return -1;
  }

  network_state = NET_INITING;

  printf("[SRV] Initialising....\n");
  if (0 != init_server(&sockfd)) {
    perror("ERROR on binding");
    return 1;
  }

  network_state = NET_CONNECTING;
  if (listen(sockfd, 5) < 0) {
    perror("listen");
    return 1;
  }

  clilen = sizeof(cli_addr);
  client_sock_fd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
  if (client_sock_fd < 0) {
    perror("ERROR on accept");
  }

  network_state = NET_READY;

  while (network_state == NET_READY || network_state == NET_CONNECTED) {
    len = receive(&client_sock_fd, buf, BUFSIZE);
    if (len < 0) {
      perror("[SRV][ERROR] Wrong data received");
    }
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

/**
 * Init server and return error_code.
 * fd is a pointer
 */
uint8_t init_server(int *sockfd) {
  uint8_t e_code = 0;

  struct sockaddr_in serv_addr;

  printf("[SRV] Initialising....\n");

  *sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (*sockfd < 0)
    perror("[SRV] ERROR opening socket");

  memset(&serv_addr, 0, sizeof(serv_addr)); /* clearing  */
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  printf("[SRV] Waiting for incomming connection on %d....\n", portno);
  int opt = 1;
  /* resue address. do not block port */
  setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  if (bind(*sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("ERROR on binding");
    return 1;
  }

  return e_code;
}

/**
 * Receive bytes into buf with buf_len
 */
int receive(int *client, char *buf, int buf_len) {
  int len; /* how many bytes received */

  len = recv(*client, buf, buf_len, 0);
  if (len > 0) {
    buf[BUFSIZE] = '\0';
    printf("Received %d characters with : '%s' \n", len, buf);
  }

  return 0;
}