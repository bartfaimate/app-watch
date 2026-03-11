/**
 * This is a client test implementation for the receiving side
 *
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

typedef enum { LINUX, OSX, WINDOWS } OS_t;

typedef enum {
  APP_VS_CODE = 0,
  APP_PYCHARM = 1,
  APP_CLION = 2,
  APP_QT_CREATOR = 3,
  /* VIDEO EDITING */
  APP_KDENLIVE = 10,
  /* PhOTO */
  APP_GIMP = 20,
  APP_DARKTABLE = 21,
  /* MUSIC PRODUCTION */
  APP_AUDACITY = 30,
  APP_ABLETON = 31,
  APP_GARAGEBAND = 32,
  /* BROWSERS */
  APP_SAFARI = 40,
  APP_FIREFOX = 41,
  APP_CHROME = 42,
  APP_VIVALDI = 43,
  APP_EDGE = 44,

  /* UNDEFINED */
  APP_UNDEFINED = 255,

} application_t;

uint8_t load_vs_code_config();

int main() {

  application_t incomming;

  while (1) {

    switch (incomming) {
    case APP_VS_CODE:

      break;
    default:
      break;
    }
  }

  return 0;
}

uint8_t load_vs_code_config() { 
    /**
     * we have 12 buttons. we can assign 8 shortcuts
     *
     */

    char **shortcuts = {
        "Ctrl+Shift+P",
        "Ctrl+Shift+P",
    };
    return 0; 
}
