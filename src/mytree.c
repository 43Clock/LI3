#include "vendas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int max(int a, int b){  
    return (a > b)? a : b;  
}


int altura (AVL *a){
	if (a == NULL)  
        return 0;  
    return a->altura;
}

AVL* novoNode(char *key,void *inst){
	AVL *node = (struct AVBin*)malloc(sizeof(struct AVBin));
	node->key = key;
	node->str = malloc(sizeof(void *));
	node->str = inst;
	node->left = NULL;
	node->right = NULL;
	node->altura = 1;
	return node;
}


/*AVL* addToNode(AVL *node,void *inst){
	node->str = realloc(node->str,sizeof(void*)*(node->numElemts+1));
	node->str[node->numElemts++] = inst;
	return node;
}*/

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

AVL* rotateLeft(AVL *x)  {  
    AVL *y = x->right;  
    AVL *T2 = y->left;  

    y->left = x;  
    x->right = T2;  
 
    x->altura = max(altura(x->left),altura(x->right)) + 1;  
    y->altura = max(altura(y->left),altura(y->right)) + 1;   
    return y;  
}

int getBalance(AVL *a){
	if (a == NULL)  
        return 0;  
    return altura(a->left) - altura(a->right);
}

AVL* insert(AVL *node,char *key,void *inst){
	if(node == NULL)
		return novoNode(key,inst);
	if(strcmp(key,node->key)<0)
		node->left = insert(node->left,key,inst);
	else if(strcmp(key,node->key)>0)
		node->right = insert(node->right,key,inst);
	//else addToNode(node,inst);
	
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

int searchAVL(AVL *node,char *key){
	if(!node) return 0;
	if(strcmp(node->key,key) == 0) return 1;
	if(strcmp(node->key,key)<0) return searchAVL(node->right,key);
	return searchAVL(node->left,key);
}

int numNodos(AVL *node){
    if(node)
        return 1+numNodos(node->left)+numNodos(node->right);
    return 0;
}

void freeAVL(AVL *node,void (*f) (void *)){
	if(node){
		free(node->key);
		f(node->str);
		freeAVL(node->right,f);
		freeAVL(node->left,f);
		free(node);
	}
}

void freeAVLsimple(AVL *node){
	if(node){
		free(node->key);
		free(node->str);
		freeAVLsimple(node->right);
		freeAVLsimple(node->left);
		free(node);
	}
}