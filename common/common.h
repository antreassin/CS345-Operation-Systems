#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Common macros for error handling
#define PRINT_ERROR(msg) \
    do { \
        fprintf(stderr, "Error in %s:%d - %s: %s\n", \
                __FILE__, __LINE__, msg, strerror(errno)); \
    } while(0)

#define CHECK_ERROR(condition, msg) \
    do { \
        if (condition) { \
            PRINT_ERROR(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

// Common utility functions
static inline void print_separator() {
    printf("========================================\n");
}

static inline void print_header(const char* title) {
    print_separator();
    printf("%s\n", title);
    print_separator();
}

#endif // COMMON_H
