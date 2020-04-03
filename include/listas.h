#ifndef LISTAS_H
#define LISTAS_H

#include "mytree.h"

typedef struct listas{
	int size;
	int ocup;
	char **listas;
}LISTAS;

int checkClientes(char *test);
int checkProdutos(char *test);
LISTAS* initLista();
void reallocLista(LISTAS *lista);
void addLista(LISTAS *lista,char *str);
void filterStr(char *str);
void freeLista(LISTAS *l);
LISTAS *getProductsStartedByLetter(LISTAS *prod, char letra);
int searchMatch(LISTAS *lista,int l, int r,char *str);
int existeNaLista(LISTAS *prod,char *pr);

#endif