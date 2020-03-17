#ifndef MYTREE_H
#define MYTREE_H

#include "vendas.h"

typedef struct AVBin { 
    char* key;
    void **str; 
    struct AVBin *left; 
    struct AVBin *right; 
    int altura;
    int numElemts;
}AVL;

AVL* insert(AVL *node,char *key,void *inst);
int searchAVL(AVL *node,void *cliente);

#endif