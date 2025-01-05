#ifndef _ERROR_LOGGER_H
#define _ERROR_LOGGER_H

// Macro to capture the caller's context
#define print_error(format, ...) \
    print_error_internal(__func__, __FILE__, __LINE__, format, ##__VA_ARGS__)

void print_error_internal(const char *caller_func, const char *file, int line, const char *format, ...);

#endif // _ERROR_LOGGER_H