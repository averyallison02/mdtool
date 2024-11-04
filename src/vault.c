#include <stdio.h>
#include <stdlib.h>

#include "vault.h"

int init_vault(vault_t* vp)
{
    // NULL everything
    vp->name = NULL;
    vp->namesz = 0;
    vp->index = NULL;
    vp->delim = '\0';
    vp->prename = '\0';

    // check for .mdtool
    FILE* mdtool;
    if ((mdtool = fopen(".mdtool", "r")) == NULL)
    {
        printf("No .mdtool: creating file\n");
        if ((mdtool = fopen(".mdtool", "w")) == NULL)
        {
            fprintf(stderr, "Unable to write to .mdtool\n");
            return -1;
        }

        // get vault name
        printf("Enter vault name: ");
        if (getline(&(vp->name), &(vp->namesz), stdin) == -1)
        {
            free(vp->name);
            fprintf(stderr, "Error getting vault name\n");
            return -1;
        }
        if (fputs(vp->name, mdtool) == EOF)
        {
            free(vp->name);
            fprintf(stderr, "Error writing name to .mdtool\n");
            return -1;
        }

        // get delimiter
        char delim[1];
        printf("Enter delimiter between positions: ");
        if (fgets(delim, 1, mdtool) == NULL)
        {
            free(vp->name);
            fprintf(stderr, "Error getting delimiter\n");
            return -1;
        }
        vp->delim = delim[0];
    }

    return 0;
}