#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "prompt.h"
#include "vault.h"

status_t do_command(const char* in) {
    if (strcmp("q", in) == 0 || strcmp("quit", in) == 0)
    {
        return QUIT;
    }
    else if (strcmp("i", in) == 0 || strcmp("init", in) == 0)
    {
        // TODO init
        return SUCCESS;
    }
    else if (strcmp("cn", in) == 0)
    {
        // TODO cn
        return SUCCESS;
    }
    else if (strcmp("create", in) == 0 || strcmp("c", in) == 0)
    {
        // TODO create
        return SUCCESS;
    }
    else if (strcmp("archive", in) == 0 || strcmp("a", in) == 0)
    {
        // TODO archive
        return SUCCESS;
    }
    else if (strcmp("delete", in) == 0 || strcmp("d", in) == 0)
    {
        // TODO delete
        return SUCCESS;
    }
    else if (strcmp("rename", in) == 0 || strcmp("rn", in) == 0)
    {
        // TODO rename
        return SUCCESS;
    }
    else if (strcmp("cd", in) == 0)
    {
        // TODO cd
        return SUCCESS;
    }
    else if (strcmp("pwd", in) == 0)
    {
        // TODO pwd
        return SUCCESS;
    }
    return ERROR;
}

int main(int argc, char** argv)
{
    // mdtool [pathname]
    if (argc == 2)
    {
        if (chdir(argv[1]) == -1)
        {
            fprintf(stderr, "%s: No such directory\n", argv[1]);
            return 1;
        }
    }

    // mdtool
    else if (argc != 1)
    {
        fprintf(stderr, "Usage: mdtool [pathname]\n");
        return 1;
    }

    // create vault with nodes
    vault_t vault;
    init_vault(&vault);
    if (vault.index == NULL) return 1;
    node_t cnode = *(vault.index);

    bool is_running = true;
    char in[MAX_IN];
    while (is_running)
    {
        // prompt
        printf("MDTool(%s %s): ", vault.name, cnode.name);
        scanf("%7s", in);

        // parse and run
        switch(do_command(in))
        {
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
