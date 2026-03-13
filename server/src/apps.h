#ifndef APPS_H
#define APPS_H

typedef enum { LINUX, OSX, WINDOWS } OS_t;

// we have to define values. protocol has to be fixed on the different machines
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

    {"darktable", APP_DARKTABLE},
    {"gimp", APP_GIMP},

    {"kdenlive", APP_KDENLIVE},

    {"audacity", APP_AUDACITY},
    {"ableton", APP_ABLETON},
    {"garageband", APP_GARAGEBAND},

    {"safari", APP_SAFARI},
    {"firefox", APP_FIREFOX},
    {"chrome", APP_CHROME},
    {"vivaldi", APP_VIVALDI},
    {"edge", APP_EDGE},
};

application_t parse_app_name(char *buf, int len);

#endif