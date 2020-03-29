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

int numProdNcomprados(Filiais *f,LISTAS *prod){
    int res = 0;
    for(int i = 0;i<prod->ocup;i++){
        if(!searchAVL(f->prodVendas,prod->listas[i])){
            res++;
        }
    }
    return res;
}

int numCliNcompradores(Filiais *f,LISTAS *clientes){
    int res = 0;
    for(int i = 0;i<clientes->ocup;i++){
        if(!searchAVL(f->cliVendas,clientes->listas[i])){
            res++;
        }
    }
    return res;
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
                    VENDA **x = (VENDA **)aux->str;
                for(int j = 0;j<aux->numElemts && !flag;j++){
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

void filialAllCheck(AVL *clientes,LISTAS *res){
    if(clientes){
        int f1 = 0,f2 = 0,f3 = 0;
        AVL *aux = clientes;
        VENDA **x = (VENDA **)aux->str;
        for(int i = 0;i<clientes->numElemts && (!f1 || !f2 || !f3);i++){
            if(x[i]->filial == 1) f1 = 1;
            if(x[i]->filial == 2) f2 = 1;
            if(x[i]->filial == 3) f3 = 1;
        }
        if(f1 && f2 && f3){
            if(res->size == res->ocup) reallocLista(res);
            addLista(res,aux->key);
        }
        filialAllCheck(aux -> left,res);
        filialAllCheck(aux->right,res);
    }
}
  
//Função para a query 5  
LISTAS *listaClientesTodosFliais(Filiais *f){ //Lista n ordenada é preciso dps usar o qsort no output
    LISTAS *res = initLista();
    filialAllCheck(f->cliVendas,res);
    return res;
}

void freeFiliais(Filiais *f){
    freeAVL(f->cliVendas,freeVenda);
    freeAVLsimple(f->prodVendas);
    free(f);
}