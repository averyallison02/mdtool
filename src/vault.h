#ifndef VAULT_H
#define VAULT_H

typedef struct node node_t;

typedef struct vault 
{
    char* name;
    size_t namesz;
    node_t* index;

    // meta
    char delim;
    char prename;
} vault_t;

typedef struct node
{
    char* pos;
    char* name;
    node_t* parent;
    node_t* children;
} node_t;

/*
create vault and store in vp
return:
    0 on success
    -1 on error
*/
int init_vault(vault_t* vp);

#endif