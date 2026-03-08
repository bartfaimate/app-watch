
/**********************************************************+
 * Brief:
 *  This C file contains all network related function 
 *  implementations
 * 
 * Author:
 *  Mate Bartfai
 * 
 **********************************************************/
#include "network.h"
#include "constants.h"


#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

/** CONSTANTS */
const int PORT = 7777;


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
  serv_addr.sin_port = htons(PORT);

  printf("[SRV] Waiting for incomming connection on %d....\n", PORT);
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

  return len;
}