#ifndef MYTREE_H
#define MYTREE_H

typedef struct AVBin { 
    char* key;
    void *str; 
    struct AVBin *left; 
    struct AVBin *right; 
    int altura;
}AVL;

AVL* insert(AVL *node,char *key,void *inst);
AVL* insertNonGrowing(AVL *node,char *key,void *inst);
int searchAVL(AVL *node,char *cliente);
int numNodos(AVL *node);
int getBalance(AVL *a);
void freeAVL(AVL *node,void (*f) (void *));
void freeAVLsimple(AVL *node);

#endif