#include "error_logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>


// Helper to log the error
void raise_error_internal(const char *caller_func, const char *file, int line, const char *format, ...) {
    // Get the current timestamp
    time_t now = time(NULL);
    struct tm time_info;
    char time_str[20]; // Buffer for "YYYY-MM-DD HH:MM:SS"

    // Use localtime_s for thread-safe time conversion
    if (localtime_s(&time_info, &now) == 0) {
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &time_info);
    } else {
        snprintf(time_str, sizeof(time_str), "Unknown Time");
    }

    // Print the formatted error log
    fprintf(stderr, "+----------------------------------------------+\n");
    fprintf(stderr, "| [!] Error at %s\n", time_str);
    fprintf(stderr, "| \n");
    fprintf(stderr, "| Caller Function : %s\n", caller_func);
    fprintf(stderr, "| Location        : %s:%d\n", file, line);
    fprintf(stderr, "| Errno           : %s (%d)\n", strerror(errno), errno);
    
    if (format) {
        // Handle variadic arguments for the message
        va_list args;
        va_start(args, format);
        fprintf(stderr, "| Message         : ");
        vfprintf(stderr, format, args);
        fprintf(stderr, "\n");
        va_end(args);
    }

    fprintf(stderr, "+----------------------------------------------+\n\n");

    fprintf(stderr, "[!] Exiting the program...\n");

    // Exit the program with a failure code
    exit(EXIT_FAILURE);
}

