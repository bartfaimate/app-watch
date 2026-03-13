#ifndef NETWORK_H
#define NETWORK_H

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
  NET_IDLE = 0,
  NET_INITING,
  NET_INITED,
  NET_CONNECTING,
  NET_CONNECTED,
  NET_READY,
  NET_DISCONNECTED,
  NET_FAIL,
} NetworkStates_t;


/***************************************
 *  FUNCTIONS
 */
uint8_t init_server();
int receive(int *client, char *buf, int buf_len);

#endif