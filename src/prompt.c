#include <stdio.h>
#include <stdbool.h>

#include "prompt.h"

status_t do_command(char* in) {
    return QUIT;
}

int main(int argc, char** argv) {
    // get path

    // get initial vault and node
    char vault[MAX_NAME];
    vault[0] = '\0';
    char node[MAX_NAME];
    node[0] = '\0';

    bool is_running = true;
    char in[MAX_IN];
    while (is_running) {
        // prompt
        printf("MDTool(%s %s): ", vault, node);
        scanf("%7s", in);

        // parse and run
        switch(do_command(in)) {
            case QUIT:
                is_running = false;
                break;
            case SUCCESS:
                break;
            case ERROR:
                printf("Invalid command\n");
                break;
        }
    }

    return 0;
}
