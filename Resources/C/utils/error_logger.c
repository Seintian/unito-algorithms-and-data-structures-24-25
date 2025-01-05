#define _POSIX_C_SOURCE 200809L

#include "error_logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <errno.h>


static size_t calculate_formatted_width(const char* format, va_list args) {
    if (!format)
        return 0;

    // Format the string into a temporary buffer to measure the actual length
    char temp[1024]; // Assuming the formatted message won't exceed this size
    vsnprintf(temp, sizeof(temp), format, args);

    // Split the formatted message into lines to find the longest line
    size_t max_width = 0;
    char* line = strtok(temp, "\n");
    while (line) {
        size_t line_len = strlen(line);
        if (line_len > max_width)
            max_width = line_len;

        line = strtok(NULL, "\n");
    }

    return max_width;
}

// Helper to log the error
void print_error_internal(const char* caller_func, const char* file, int line, const char* format, ...) {
    if (!format)
        format = errno ? strerror(errno) : "No Error";

    // Get current timestamp
    time_t now = time(NULL);
    struct tm time_info;
    char time_str[20]; // "YYYY-MM-DD HH:MM:SS"
    if (localtime_r(&now, &time_info))
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &time_info);
    else
        snprintf(time_str, sizeof(time_str), "Unknown Time");

    // Start measuring the required width
    size_t caller_func_len = strlen("Caller Function : ") + strlen(caller_func);
    size_t location_len    = strlen("Location        : ") + strlen(file) + 10; // ":<line>"
    size_t errno_len       = strlen("Errno           : No Error (0)");

    // Measure the formatted message's width
    va_list args;
    va_start(args, format);
    size_t message_width = calculate_formatted_width(format, args);
    va_end(args);

    // Find the maximum width
    size_t max_width = caller_func_len > location_len ? caller_func_len : location_len;
    max_width = max_width > errno_len ? max_width : errno_len;
    max_width = max_width > message_width ? max_width : message_width;

    // Include padding for "| " and " |"
    max_width += 4;

    // Print the horizontal ruler
    char* hr = malloc(max_width - 1);
    memset(hr, '-', max_width - 2);
    hr[max_width - 2] = '\0';

    fprintf(stderr, "\n+%s+\n", hr);
    fprintf(stderr, "| [!] Error at %s\n", time_str);
    fprintf(stderr, "|\n");
    fprintf(stderr, "| Caller Function : %s\n", caller_func);
    fprintf(stderr, "| Location        : %s:%d\n", file, line);
    fprintf(stderr, "| Errno           : %s (%d)\n", errno ? strerror(errno) : "No Error", errno);
    fprintf(stderr, "|\n");

    // Print the message
    if (format) {
        fprintf(stderr, "+ Message ");
        for (size_t i = 0; i < max_width - 11; i++)
            fprintf(stderr, "-");

        fprintf(stderr, "+\n| \n");

        // Print formatted message
        va_start(args, format);
        char formatted_message[1024];
        vsnprintf(formatted_message, sizeof(formatted_message), format, args);
        va_end(args);

        // Split and print each line of the message
        char *line = strtok(formatted_message, "\n");
        while (line) {
            fprintf(stderr, "| %s\n", line);
            line = strtok(NULL, "\n");
        }

        fprintf(stderr, "|\n");
    }

    fprintf(stderr, "+%s+\n\n", hr);
    fprintf(stderr, "[!] Exiting the program...\n");

    free(hr);
}

