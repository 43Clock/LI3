  
/**
 * @file   listas.c
 * @brief  Funções relativas ás listas.
 */

#include "listas.h"
#include <string.h>
#include <stdlib.h>

struct listas{
	int size; /**<Número de elementos com espaço alocado */
	int ocup; /**<Número de elementos da lista*/
	char **listas; /**<Array de apontadores para Strings*/
};

/**
 * @brief      Função que verifica se um cliente é válido.
 *
 * @return     Retorna 1 caso seja válido e 0 caso seja inválido.
 */
int checkClientes(char *test){
	int i = 0 ,j;
	char num[4];
	if(!(test[0]>='A' && test[0]<='Z')) return 0;
	while(!(test[i]>='0' && test[i]<='9')) i++;
	for(j = 0;j<4;i++,j++)
		num[j] = test[i];
	if(!(atoi(num)>= 1000 && atoi(num)<=5000)) return 0;
	return 1;
}


/**
 * @brief      Função que verifica se um produto é válido.
 *
 * @return     Retorna 1 caso seja válido e 0 caso seja inválido.
 */
int checkProdutos(char *test){
	int i = 0 ,j;
	char num[4];
	if(!(test[0]>='A' && test[0]<='Z')) return 0;
	while(!(test[i]>='0' && test[i]<='9')) i++;
	for(j = 0;j<4;i++,j++)
		num[j] = test[i];
	if(!(atoi(num)>= 1000 && atoi(num)<=9999)) return 0;
	return 1;
}

/**
 * @brief      Função que inicializa a estrutura LISTAS.
 *
 * @return     Retorna uma estrutura Lista inicializada com listas a NUll e os parametros size e ocup a 1 e 0, respetivamente. 
 */
LISTAS* initLista(){
	LISTAS *listas = malloc(sizeof(LISTAS));
	listas->size = 1;
	listas->ocup = 0;
	char **tmp = malloc(listas->size*sizeof(char*));
	listas->listas = tmp;
	return listas;
}

/**
 * @brief      Função que realoca o espaço na memória para a estrututa LISTAS, duplicando-o.
 *
 * @param      lista      Estrutura do tipo LISTAS à qual será realocado o espaço. 
 */
void reallocLista(LISTAS *lista){
	int i;
	char **tmp = malloc(2*lista->size*sizeof(char*));
	for(i = 0;i<lista->size;i++){
		tmp[i] = lista->listas[i];
	}
	free(lista->listas);
	lista->listas = tmp;
	lista->size *=2;
}

/**
 * @brief      Função que adiciona uma string á estrutura LISTAS.
 *
 * @param      str        String que será adicionada à estrutura Lista, na ultima posição da mesma.
 * @param      lista      Estrutura à qual será adicionada a String.
 */
void addLista(LISTAS *lista,char *str){
	lista->listas[lista->ocup] = strdup(str);
	lista->ocup++;
}

/**
 * @brief      Função que filtra apenas uma linha de uma String.
 *
 * @param      str    String percorrida até mudar de linha.
 */
void filterStr(char *str){
	int i;
	for(i = 0;str[i] != '\n' && str[i] != '\r';i++);
	str[i] = '\0';
}

/**
 * @brief      Função que liberta o espaço alocado para uma estrutura do tipo LISTAS.
 *
 * @param      l      Estrutura da qual será libertado o espaço na memória.
 */
void freeLista(LISTAS *l){
	int i;
	for(i = 0;i<l->ocup;i++)
		free(l->listas[i]);
	free(l->listas);
	free(l);
}

/**
 * @brief      Função que determina a lista dos Produtos começados por uma determinada letra.
 *
 * @param      prod       Estrutura LISTAS da qual iremos retirar apenas os produtos começados pela letra dada.
 * @param      letra      Letra inicial dos produtos que pretendemos.
 *
 * @return     Retorna uma estrutura do tipo LISTAS composta apenas pelos produtos começados pela letra dada.
 */
LISTAS *getProductsStartedByLetter(LISTAS *prod, char letra) {
	LISTAS *res = initLista();
    int i;
    for(i=0; i < prod->ocup && prod->listas[i][0]<=letra; i++){
    	if(prod->listas[i][0] == letra){
    		if(res->ocup==res->size) reallocLista(res);
    		addLista(res, prod->listas[i]);
    	}
    }
    return res;
}

/**
 * @brief      Função que executa uma procura binária entre dois indices numa estrutura do tipo LISTAS.
 *
 * @param[in]      l          indice menor
 * @param[in]          r          indice maior 
 * @param          str        String que queremos procurar na estrutura.
 * @param          lista      Estrutura na qual irá ser feita a procura binaria da String dada.
 *
 * @return     Retorna uma string com o produto da venda.
 */
int searchMatch(LISTAS *lista,int l, int r,char *str){
	while(l<=r){
		int m = l +(r-l)/2;
		if(strcmp(lista->listas[m],str) == 0) return m;
		if(strcmp(lista->listas[m],str)<0) l = m+1;
		else r =m-1;
	}
	return -1;
}

/**
 * @brief      Função que verifica se um produto exite numa dada lista de produtos.
 *
 * @return     Retorna o resultado da procura binária (função anterior).
 */
int existeNaLista(LISTAS *prod,char *pr){
	return searchMatch(prod,0,prod->ocup-1,pr)>0;
}

int getOcupados(LISTAS *l){
	return l->ocup;
}

int getSize(LISTAS *l){
	return l->size;
}

char *getIndex(LISTAS *l,int i){
	return l->listas[i];
}

char **getLista(LISTAS *l){
	return l->listas;
}
