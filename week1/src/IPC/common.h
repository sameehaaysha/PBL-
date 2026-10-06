#ifndef COMMON_H
#define COMMON_H

#define UI_TO_CORE "/ui_to_core"
#define CORE_TO_UI "/core_to_ui"
#define CORE_TO_LOG "/core_to_log"

#define MAX_TEXT 256

#define MSG_COMMAND 1
#define MSG_RESULT 2
#define MSG_ERROR 3
#define MSG_SHUTDOWN 4

typedef struct
{
    int type;
    char text[MAX_TEXT];
} Message;

#endif
