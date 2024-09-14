#ifndef PROMPT_H
#define PROMPT_H

#define MAX_IN      8
#define MAX_NAME    100

typedef enum {
    QUIT = -1,
    SUCCESS = 0,
    ERROR = 1
} status_t;

/*
parse and run the command from buffer "in"
returns:
    -1 for quit
    0 for success
    1 if unable to parse
*/
status_t do_command(const char* in);

#endif
