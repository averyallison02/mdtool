#include <stdio.h>
#include <stdbool.h>

int main(int argc, char** argv) {
    bool is_running = true;
    char in[100];

    while (is_running) {
        // prompt
        printf("(MDTool) : ");
        scanf("%99s", in);
        printf("\n");

        is_running = false;
    }

    printf("%s", in);

    return 0;
}
