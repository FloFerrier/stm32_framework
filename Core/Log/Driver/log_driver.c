#include "log_driver.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define LOG_LEN_MAX (255U)

typedef struct {
    log_level_e level;
    bool color;
    bool isInitialized;
    log_fcnt_t send_interface;
} log_instance_s;

LOG_STATIC log_instance_s log_instance = {
    .isInitialized = false,
};

const char *log_level_table[] = {
    [LOG_FATAL] = "FATAL", [LOG_ERROR] = "ERROR", [LOG_WARN] = "WARN",
    [LOG_INFO] = "INFO",   [LOG_TRACE] = "TRACE", [LOG_DEBUG] = "DEBUG",
};

typedef enum {
    ANSI_COLOR_NONE = 0,
    ANSI_COLOR_RESET = 1,
    ANSI_COLOR_RED = 2,
    ANSI_COLOR_GREEN = 3,
    ANSI_COLOR_YELLOW = 4,
    ANSI_COLOR_BLUE = 5,
    ANSI_COLOR_MAGENTA = 6,
    ANSI_COLOR_CYAN = 7,
} ansi_color_e;

const char *ansi_color_table[] = {
    [ANSI_COLOR_NONE] = "",
    [ANSI_COLOR_RESET] = "\x1b[0m",
    [ANSI_COLOR_RED] = "\x1b[31m",
    [ANSI_COLOR_GREEN] = "\x1b[32m",
    [ANSI_COLOR_YELLOW] = "\x1b[33m",
    [ANSI_COLOR_BLUE] = "\x1b[34m",
    [ANSI_COLOR_MAGENTA] = "\x1b[35m",
    [ANSI_COLOR_CYAN] = "\x1b[36m",
};

void LOG_Init(log_interface_s interface) {
    if (NULL != interface.send_data) {
        log_instance.color = true;
#ifndef DEBUG
        log_instance.level = LOG_INFO;
#else
        log_instance.level = LOG_DEBUG;
#endif
        log_instance.send_interface = interface.send_data;
        log_instance.isInitialized = true;
    }
}

void LOG_SetLevel(log_level_e level) {
    if ((LOG_FATAL <= level) && (LOG_DEBUG >= level)) {
        log_instance.level = level;
    }
}

log_level_e LOG_GetLevel(void) { return log_instance.level; }

void LOG_DisableColor(void) { log_instance.color = false; }

void LOG_EnableColor(void) { log_instance.color = true; }

LOG_STATIC void LOG_GenerateIndex(log_level_e level, const char *file, int line,
                                  char *index, uint32_t *len) {
    if ((NULL != file) && (NULL != index) && (NULL != len)) {
        ansi_color_e color_level = ANSI_COLOR_NONE;
        if (true == log_instance.color) {
            switch (level) {
                case LOG_FATAL:
                    color_level = ANSI_COLOR_MAGENTA;
                    break;
                case LOG_ERROR:
                    color_level = ANSI_COLOR_RED;
                    break;
                case LOG_WARN:
                    color_level = ANSI_COLOR_YELLOW;
                    break;
                case LOG_INFO:
                    color_level = ANSI_COLOR_CYAN;
                    break;
                case LOG_TRACE:
                    color_level = ANSI_COLOR_BLUE;
                    break;
                case LOG_DEBUG:
                    color_level = ANSI_COLOR_GREEN;
                    break;
                default:
                    color_level = ANSI_COLOR_NONE;
                    break;
            }
        }

        if (LOG_DEBUG == level) {
            *len = (uint32_t)snprintf(index, LOG_LEN_MAX, "%s[%s] (%s:%d) ",
                                      ansi_color_table[color_level],
                                      log_level_table[level], file, line);
        } else {
            *len = (uint32_t)snprintf(index, LOG_LEN_MAX, "%s[%s] ",
                                      ansi_color_table[color_level],
                                      log_level_table[level]);
        }
    }
}

LOG_STATIC void LOG_GenerateEndOfLine(char *endOfLine, uint32_t *len) {
    if ((NULL != endOfLine) && (NULL != len)) {
        if (true == log_instance.color) {
            *len = snprintf(endOfLine, 10, "%s\r\n",
                            ansi_color_table[ANSI_COLOR_RESET]);
        } else {
            *len = snprintf(endOfLine, 10, "\r\n");
        }
    }
}

void LOG_Send(log_level_e level, const char *file, int line, const char *fmt,
              ...) {
    if ((true == log_instance.isInitialized) && (log_instance.level >= level)) {
        char index[LOG_LEN_MAX + 1] = "";
        uint32_t index_len = 0;
        LOG_GenerateIndex(level, file, line, index, &index_len);
        char endOfLine[10 + 1] = "";
        uint32_t endOfLine_len = 0;
        LOG_GenerateEndOfLine(endOfLine, &endOfLine_len);
        char message[LOG_LEN_MAX + 1] = "";
        uint32_t message_len_max = LOG_LEN_MAX - index_len - endOfLine_len;
        va_list args;
        va_start(args, fmt);
        vsnprintf(message, message_len_max, fmt, args);
        va_end(args);
        char buffer[LOG_LEN_MAX + 1] = "";
        uint32_t buffer_size = 0;
        buffer_size =
            snprintf(buffer, LOG_LEN_MAX, "%s%s%s", index, message, endOfLine);
        log_instance.send_interface(buffer, buffer_size);
    }
}