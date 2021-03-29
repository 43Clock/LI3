#ifndef MYTREE_H
#define MYTREE_H

typedef struct AVBin AVL;

AVL* insert(AVL *node,char *key,void *inst);
int searchAVL(AVL *node,char *cliente);
AVL *searchAVLr(AVL *node,char *key);
int numNodos(AVL *node);
int getBalance(AVL *a);
void freeAVL(AVL *node,void (*f) (void *));
void freeAVLsimple(AVL *node);

AVL *getLeft(AVL *node);
AVL *getRight(AVL *node);
char *getKey(AVL *node);
void *getStr(AVL *node);

#endif