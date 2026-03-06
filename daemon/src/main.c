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

typedef enum { LINUX, OSX, WINDOWS } OS_t;

typedef enum {
  APP_VS_CODE = 0,
  APP_PYCHARM,
  APP_CLION,
  APP_QT_CREATOR,
  /* VIDEO EDITING */
  APP_KDENLIVE,
  /* MUSIC PRODUCTION */
  APP_AUDACITY,
  APP_ABLETON,
  /* BROWSERS */
  APP_SAFARI,
  APP_FIREFOX,
  APP_CHROME,
  APP_VIVALDI,
  APP_EDGE,

  /* UNDEFINED */
  APP_UNDEFINED,

} application_t;

typedef struct {
  const char *name;
  application_t app;
} app_map_t;

static const app_map_t app_map[] = {
  {"code", APP_VS_CODE},
  {"vscode", APP_VS_CODE},
  {"pycharm", APP_PYCHARM},
  {"clion", APP_CLION},
  {"qtcreator", APP_QT_CREATOR},

  {"kdenlive", APP_KDENLIVE},

  {"audacity", APP_AUDACITY},
  {"ableton", APP_ABLETON},

  {"safari", APP_SAFARI},
  {"firefox", APP_FIREFOX},
  {"chrome", APP_CHROME},
  {"vivaldi", APP_VIVALDI},
  {"edge", APP_EDGE},
};

/************************************************************************
 *  Global variables
 ************************************************************************/
const int PORT = 7777;
const uint16_t BUFSIZE = 256;
static NetworkStates_t s_network_state = NET_IDLE;

/************************************************************************
 *  Function definitions
 ************************************************************************/
uint8_t init_server();
int receive(int *client, char *buf, int buf_len);

application_t parse_app_name(char *buf, int len);

uint8_t send_usb(application_t app);

int modify(int *pint) {

  *pint = 12;

  return 0;
}

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
  if (client_sock_fd > 0)
    close(client_sock_fd);

  close(sockfd);

  return 0;
} /* end main */

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

/**
 * Process incoming app name and get the related command
 */
application_t parse_app_name(char *buf, int len) {
  size_t size = sizeof(app_map) / sizeof(app_map[0]); /* length of lookup table */

    for (size_t i = 0; i < size; i++) {
        if (strcmp(buf, app_map[i].name) == 0) {
            return app_map[i].app;
        }
    }

    return APP_UNDEFINED;
}

/**
 * Send the APP command via USB to the keyboard
 */
uint8_t send_usb(application_t app) {

  printf("[SRV] Sending via USB: 'APP' %d\n", app);
}