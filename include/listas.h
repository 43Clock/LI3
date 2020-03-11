#ifndef LISTAS_H
#define LISTAS_H

typedef struct listas{
	int size;
	int ocup;
	char **listas;
}LISTAS;

int checkClientes(char *test);
int checkProdutos(char *test);
void initLista(LISTAS *lista);
void reallocLista(LISTAS *lista);
void addLista(LISTAS *lista,char *str);
void filterStr(char *str);

#endif