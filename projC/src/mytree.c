/**
 * @file   mytree.c
 * @brief  Funções relativas a árvores.
 */
#include "mytree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct AVBin { 
    char* key;            /**<Chave do nodo topo da árvore*/
    void *str;            /**<Apontador para uma estrutura*/
    struct AVBin *left;   /**<Árvore da esquerda*/
    struct AVBin *right;  /**<Árvore da direira*/
    int altura;           /**<Variável que guarda a altura da árvore*/
};

/**
 * @brief      Função que determina o maior entre 2 elementos.
 *
 * @return     Retorna o maior elemento da árvore.
 */
int max(int a, int b){  
    return (a > b)? a : b;  
}

/**
 * @brief      Função que determina a altura de uma árvore.
 *
 * @return     Retorna a variável altura da árvore.
 */
int altura (AVL *a){
	if (a == NULL)  
        return 0;  
    return a->altura;
}

/**
 * @brief      Função que cria um novo nodo.
 *
 * @return     Retorna a árvore com esse novo nodo no topo e com as árvores da esquerda e direita a NULL.
 */
AVL* novoNode(char *key,void *inst){
	AVL *node = (struct AVBin*)malloc(sizeof(struct AVBin));
	node->key = key;
	node->str = inst;
	node->left = NULL;
	node->right = NULL;
	node->altura = 1;
	return node;
}

/**
 * @brief      Função que executa uma rotação à direita na árvore.
 *
 * @return     Retorna a árvore após a rotação ter sido feita.
 */
AVL *rotateRight(AVL *y)  
{  
    AVL *x = y->left;  
    AVL *T2 = x->right;  

    x->right = y;  
    y->left = T2;  
  
    y->altura = max(altura(y->left),altura(y->right)) + 1;  
    x->altura = max(altura(x->left),altura(x->right)) + 1;  
   
    return x;  
}  

/**
 * @brief      Função que executa uma rotação à esquerda na árvore.
 *
 * @return     Retorna a árvore após a rotação ter sido feita.
 */
AVL* rotateLeft(AVL *x)  {  
    AVL *y = x->right;  
    AVL *T2 = y->left;  

    y->left = x;  
    x->right = T2;  
 
    x->altura = max(altura(x->left),altura(x->right)) + 1;  
    y->altura = max(altura(y->left),altura(y->right)) + 1;   
    return y;  
}

/**
 * @brief      Função que determina o balanceamento duma árvore.
 *
 * @return     Retorna a diferença de alturas entre a árvore da esquerda e da direita de uma árvore.
 */
int getBalance(AVL *a){
	if (a == NULL)  
        return 0;  
    return altura(a->left) - altura(a->right);
}

/**
 * @brief      Função que insere um nodo numa árvore.
 *
 * @param      node   Árvore na qual será inserido o novo nodo.
 * @param      key    Chave do novo nodo.
 * @param      inst   Estrutura presente no novo nodo.
 *
 * @return     Retorna a árvore após a inserção do nodo.
 */
AVL* insert(AVL *node,char *key,void *inst){
	if(node == NULL)
		return novoNode(key,inst);
	if(strcmp(key,node->key)<0)
		node->left = insert(node->left,key,inst);
	else if(strcmp(key,node->key)>0)
		node->right = insert(node->right,key,inst);
	
	node->altura = 1+max(altura(node->left),altura(node->right));

	int balance = getBalance(node);

	if(balance>1 && strcmp(key,node->left->key)<0)
		return rotateRight(node);
	if(balance<-1 && strcmp(key,node->right->key)>=0)
		return rotateLeft(node);
	if(balance >1 && strcmp(key,node->left->key)>=0){
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	if(balance <-1 && strcmp(key,node->right->key)<0){
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}
	return node;
}

/**
 * @brief      Função que determina se existe um nodo com uma dada chave.
 *
 * @return     Retorna 1 caso exista e 0 caso contrário.
 */
int searchAVL(AVL *node,char *key){
	if(!node) return 0;
	if(strcmp(node->key,key) == 0) return 1;
	if(strcmp(node->key,key)<0) return searchAVL(node->right,key);
	return searchAVL(node->left,key);
}

/**
 * @brief      Função que determina se, na árvore, existe um nodo com uma dada chave.
 *
 * @return     Retorna a árvore caso exista e NULL caso contrário.
 */
AVL *searchAVLr(AVL *node,char *key){
	if(!node) return NULL;
	if(strcmp(node->key,key) == 0) return node;
	if(strcmp(node->key,key)<0) return searchAVLr(node->right,key);
	return searchAVLr(node->left,key);
}

/**
 * @brief      Função que determina o número de nodos duma árvore.
 *
 * @return     Retorna o número de nodos da árvore.
 */
int numNodos(AVL *node){
    if(node)
        return 1+numNodos(node->left)+numNodos(node->right);
    return 0;
}

/**
 * @brief      Função que liberta o espaço de memória que uma árvore ocupa,libertando também a estrutura presente no nodo da árvore.
 * 
 * @param      node   Árvore da qual será libertado o espaço.
 */
void freeAVL(AVL *node,void (*f) (void *)){
	if(node){
		free(node->key);
		f(node->str);
		freeAVL(node->right,f);
		freeAVL(node->left,f);
		free(node);
	}
}

/**
 * @brief      Função que liberta o espaço de memória que uma árvore ocupa.
 * 
 * @param      node   Árvore da qual será libertado o espaço.
 */
void freeAVLsimple(AVL *node){
	if(node){
		free(node->key);
		free(node->str);
		freeAVLsimple(node->right);
		freeAVLsimple(node->left);
		free(node);
	}
}

/**
 * @brief      Função que determina a árvore esquerda duma árvore.
 * 
 * @return     Retorna a árvore da esquerda, da árvore presente.
 */
AVL *getLeft(AVL *node){
	return node->left;
}

/**
 * @brief      Função que determina a árvore direita duma árvore.
 * 
 * @return     Retorna a árvore da direita, da árvore presente.
 */

AVL *getRight(AVL *node){
	return node->right;
}

/**
 * @brief      Função que determina a chave do nodo topo duma árvore.
 * 
 * @return     Retorna a chave do nodo topo.
 */

char *getKey(AVL *node){
	return node->key;
}

/**
 * @brief      Função que determina a estrutura utilizada no parãmetro str duma árvore.
 * 
 * @return     Retorna um apontador para a estrutura utilizada no parâmetro str.
 */

void *getStr(AVL *node){
	return node->str;
}
