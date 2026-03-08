#include "apps.h"

#include <stdlib.h>
#include <string.h>

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