#include "listas.h"
#include <string.h>
#include <stdlib.h>


int checkClientes(char *test){
	int i = 0 ,j;
	char num[4];
	while(!(test[i]>='0' && test[i]<='9')) i++;
	for(j = 0;j<4;i++,j++)
		num[j] = test[i];
	if(!(atoi(num)>= 1000 && atoi(num)<=5000)) return 0;
	return 1;
}

int checkProdutos(char *test){
	int i = 0 ,j;
	char num[4];
	while(!(test[i]>='0' && test[i]<='9')) i++;
	for(j = 0;j<4;i++,j++)
		num[j] = test[i];
	if(!(atoi(num)>= 1000 && atoi(num)<=9999)) return 0;
	return 1;
}

LISTAS* initLista(){
	LISTAS *listas = malloc(sizeof(LISTAS));
	listas->size = 1;
	listas->ocup = 0;
	char **tmp = malloc(listas->size*sizeof(char*));
	listas->listas = tmp;
	return listas;
}

void reallocLista(LISTAS *lista){
	char **tmp = malloc(2*lista->size*sizeof(char*));
	for(int i = 0;i<lista->size;i++){
		tmp[i] = strdup(lista->listas[i]);
		free(lista->listas[i]);
	}
	free(lista->listas);
	lista->listas = tmp;
	lista->size *=2;
}

void addLista(LISTAS *lista,char *str){
	lista->listas[lista->ocup] = strdup(str);
	lista->ocup++;
}

void filterStr(char *str){
	int i;
	for(i = 0;str[i] != '\n' && str[i] != '\r';i++);
	str[i] = '\0';
}

void freeLista(LISTAS *l){
	for(int i = 0;i<l->ocup;i++)
		free(l->listas[i]);
	free(l->listas);
	free(l);
}