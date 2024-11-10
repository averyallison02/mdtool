/**
 * Avery Allison 2024
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USAGE   "Usage: mdtool child parent\n"

/*
ensure args are correct
return:
    -1 if not
    0 if correct
*/
int parseargs(int argc, char** argv)
{
    // incorrect number of args
    if (argc != 3)
    {
        fprintf(stderr, USAGE);
        return -1;
    }

    // child already exists
    FILE* tempf = NULL;
    if ((tempf = fopen(argv[1], "r")) != NULL)
    {
        fprintf(stderr, "%s: File already exists\n%s", argv[1], USAGE);
        fclose(tempf);
        return -1;
    }

    // parent does not exist
    if ((tempf = fopen(argv[2], "r")) == NULL)
    {
        fprintf(stderr, "%s: File does not exist\n%s", argv[2], USAGE);
        return -1;
    }
    else fclose(tempf);

    // proper filenames
    if (strchr(argv[1], '_') == NULL || strchr(argv[2], '_') == NULL)
    {
        fprintf(stderr, "Incorrect filename(s)\nMust contain an underscore before their title\n");
        return -1;
    }

    return 0;
}

/*
parse only name from filename string
return:
    result on success (must be freed)
    NULL on failure
*/
char* getname(char* line)
{
    // go to _
    char* name = strchr(line, '_') + 1;
    name = strcpy(malloc(strlen(name) + 1), name);

    // change . to null
    char* dot = strchr(name, '.');
    if (dot == NULL)
    {
        free(name);
        fprintf(stderr, "No filename extension\n");
        return NULL;
    }
    *dot = '\0';

    return realloc(name, strlen(name) + 1);
}

/*
write base data to child
return:
    -1 for error
    0 for success
*/
int writechild(char* child, char* parent)
{
    FILE* fp = NULL;
    if ((fp = fopen(child, "w")) == NULL)
    {
        fprintf(stderr, "%s: Error opening file for writing\n", child);
        return -1;
    }

    // child links to index
    if (fprintf(fp, "[Index](0_Index.md)\n") < 0)
    {
        fprintf(stderr ,"%s: Error writing to file\n", child);
        fclose(fp);
        return -1;
    }

    // child links to parent if not index
    char* pname = getname(parent);
    if (pname == NULL) return -1;
    if (strcmp(pname, "Index") == 0);
    else if (fprintf(fp, "[%s](%s)\n", pname, parent) < 0)
    {
        fprintf(stderr, "%s: Error writing to file\n", child);
        fclose(fp);
        free(pname);
        return -1;
    }

    // add children heading
    if (fprintf(fp, "### Children\n") < 0)
    {
        fprintf(stderr, "%s: Error writing to file\n", child);
        fclose(fp);
        free(pname);
        return -1;
    }

    fclose(fp);
    free(pname);
    return 0;
}

/*
update parent with link to new child
return:
    -1 for error
    0 for success
*/
int updateparent(char* child, char* parent)
{
    FILE* fp = NULL;
    if ((fp = fopen(parent, "a+")) == NULL)
    {
        fprintf(stderr, "%s: Error opening file for writing\n", parent);
        return -1;
    }
    rewind(fp);

    // read until after children header
    char* line = NULL;
    size_t linesz = 0;
    do
    {
        if (line != NULL)
        {
            free(line);
            line = NULL;
        }
        if (getline(&line, &linesz, fp) == -1)
        {
            free(line);
            fprintf(stderr, "Unable to get line from parent file\n");
            fclose(fp);
            return -1;
        }
    }
    while (strcmp(line, "### Children\n") != 0);
    if (line != NULL) free(line);

    // read until # after line
    line = NULL;
    linesz = 0;
    char c;
    do
    {
        if (line != NULL)
        {
            free(line);
            line = NULL;
        }
        if (getline(&line, &linesz, fp) == -1)
        {
            free(line);
            fprintf(stderr, "Unable to get line from parent file\n");
            fclose(fp);
            return -1;
        }
        if ((c = fgetc(fp)) == EOF)
            {
                free(line);
                fprintf(stderr, "Unable to get char from parent file\n");
                fclose(fp);
                return -1;
            }
    }
    while (c != '#');
    if (line != NULL) free(line);
    line = NULL;

    fseek(fp, -1, SEEK_CUR);

    // TODO: Insert child link

    fclose(fp);
    return 0;
}

int main(int argc, char** argv)
{
    if (parseargs(argc, argv) == -1) return EXIT_FAILURE;

    if (writechild(argv[1], argv[2]) == -1) return EXIT_FAILURE;
    if (updateparent(argv[1], argv[2]) == -1) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
