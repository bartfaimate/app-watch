/************************************************************************
 * Author:
 *      Mate Bartfai
 * Purpose:
 *    Driver program for the Macropad
 *
 ************************************************************************/

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>

#include "network.h"
#include "constants.h"
#include "apps.h"

/** */
typedef enum {
  USB_DLE = 0,
  USB_ONNECTING,
  USB_ONNECTED,
  USB_EADY,
  USB_ISCONNECTED,
} USBStates_t;


/************************************************************************
 *  Global variables
 ************************************************************************/

static NetworkStates_t s_network_state = NET_IDLE;

/************************************************************************
 *  Function definitions
 ************************************************************************/



uint8_t send_usb(application_t app);

void parse_app_name(char* input, int len, char* output); 

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

  s_network_state = NET_INITING;

  printf("[SRV] Initialising....\n");
  if (0 != init_server(&sockfd)) {
    perror("ERROR on binding");
    return 1;
  }

  s_network_state = NET_CONNECTING;
  if (listen(sockfd, 5) < 0) {
    perror("listen");
    return 1;
  }

client_init:
  if (s_network_state == NET_DISCONNECTED ||
      s_network_state == NET_CONNECTING) {

    clilen = sizeof(cli_addr);
    client_sock_fd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (client_sock_fd < 0) {
      perror("ERROR on accept");
    }
  }

  s_network_state = NET_READY;
  application_t cmd;

  while (s_network_state == NET_READY || s_network_state == NET_CONNECTED) {

    memset(buf, 0, BUFSIZE); /* clear buffer each time */
    len = receive(&client_sock_fd, buf, BUFSIZE);
    if (len < 0) {
      perror("[SRV][ERROR] Wrong data received");
    }

    if (len == 0) {
      perror("[SRV][ERROR]Client disconnected");
      s_network_state = NET_DISCONNECTED;
      close(client_sock_fd);
      goto client_init;
    }

    if (len > 0) {
      cmd = parse_app_name(buf, len);
      send_usb(cmd);
    }
  }

  /* initialise server socket */
  /* initialise usb */
  /* listen for usb connections and disconnect */

  /* if usb connected send Operating System */
  /* send active app name */
  /* on change send active app name */
  end:
  if (client_sock_fd > 0)
    close(client_sock_fd);

  close(sockfd);

  return 0;
} /* end main */




/**
 * Send the APP command via USB to the keyboard
 */
uint8_t send_usb(application_t app) {

  printf("[SRV] Sending via USB: 'APP' %d\n", app);
}


void parse_app_name(char* input, int len, char* output) {


}