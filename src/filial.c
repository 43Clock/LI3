#include "filial.h"
#include <stdlib.h>
#include <string.h>

struct filiais {
	AVL* cliVendas; /**<Avl que relaciona os clientes com todas as compras feitas por ele>*/
	AVL* prodVendas; /**<Avl que relaciona os produtos com todas as vendas que o contem>*/
};

Filiais *initFiliais(){
	Filiais *f = malloc(sizeof(struct filiais));
	f->cliVendas = NULL;
	f->prodVendas = NULL;
	return f;
}

void addVendaToFilial(VENDA *v,Filiais *f){
    f->cliVendas = insert(f->cliVendas,v->cliente,v);
    f->prodVendas = insert(f->prodVendas,v->prod,v);
}

void listaProdNcomprados(Filiais* f,int filial,LISTAS *prod,LISTAS *res){
    AVL *aux;
    int flag = 0;
    if(filial == 0){//Caso em que só queremos ver se o prod foi comprado ou não
        for(int i = 0;i<prod->ocup;i++){
            if(!searchAVL(f->prodVendas,prod->listas[i])){
                if(res->size == res->ocup) reallocLista(res);
                addLista(res,prod->listas[i]);
            }
        }
    }
    else{
        for(int i = 0;i<prod->ocup;i++){
            if(!searchAVL(f->prodVendas,prod->listas[i])){
                if(res->size == res->ocup) reallocLista(res);
                addLista(res,prod->listas[i]);
            }
            else{
                aux = f->prodVendas;
                flag = 0;
                while(strcmp(aux->key,prod->listas[i])!=0){
                    if(strcmp(prod->listas[i],aux->key)>0) aux = aux->right;
                    else aux = aux->left;
                }
                for(int j = 0;j<aux->numElemts && !flag;j++){
                    VENDA **x = (VENDA **)aux->str;
                    if(x[j]->filial == filial) flag = 1;
                }
                if(!flag){
                    if(res->size == res->ocup) reallocLista(res);
                    addLista(res,prod->listas[i]);
                }
            }
        }
    }
}

LISTAS *listaClientesTodosFliais(AVL *clientes){}

void freeFiliais(Filiais *f){
    freeAVL(f->cliVendas,freeVenda);
    freeAVLsimple(f->prodVendas);
    free(f);
}