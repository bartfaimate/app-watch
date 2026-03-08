#ifndef APPS_H
#define APPS_H



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


application_t parse_app_name(char *buf, int len);

#endif