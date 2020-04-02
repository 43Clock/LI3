#include "faturas.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct faturas {
	double totalFatMes[12]; /**<Total faturado/mês,Tipo,Mes,Filial>*/
	int totalVendasMes[12];	/**<Total vendido/mês>*/
	AVL *avlF; /**<Avl de faturas, em que a key é um produto>*/
};

Faturas * initFaturas(){
    Faturas *temp = malloc(sizeof(struct faturas));
	memset(temp->totalFatMes,0,12*sizeof(double));
	memset(temp->totalVendasMes,0,12*sizeof(int));
	temp->avlF = NULL;
    return temp;
}

void addVendaToFaturas(Faturas *f,VENDA *v){
	AVL *aux = f->avlF;
	char * produto = getProdVenda(v);
	while(aux && strcmp(aux->key,produto) != 0){
		if(strcmp(produto,aux->key)<0) aux = aux->left;
		else aux = aux->right;
	}
	if(aux == NULL) {
		Fatura *fat = initFat(v);
		f->avlF = insert(f->avlF,produto,fat);
	}
	else{
        Fatura *fats = getFatura(f,produto);
		addFat(aux->str,v);
        fats = getFatura(f,produto);
	}
    f->totalFatMes[getMesVenda(v)-1] += getQuantVenda(v) * getPrecoVenda(v);
    f->totalVendasMes[getMesVenda(v)-1] ++;
}

double calculaFatMes(AVL *f,int mes){
    double r = 0;
    if(f){
        r+= getFaturacaoFatura(f->str,0,mes+1,0)+getFaturacaoFatura(f->str,0,mes+1,1);
        r+= calculaFatMes(f->right,mes)+calculaFatMes(f->left,mes);
        return r;
    }
    return 0;
}

int calculaVendasMes(AVL *f,int mes){
    int r = 0;
    if(f){
        r+= getnumVendasFatura(f->str,0,mes+1,0)+getnumVendasFatura(f->str,0,mes+1,1);
        r+= calculaVendasMes(f->right,mes)+calculaVendasMes(f->left,mes);
        return r;
    }
    return 0;
}

void calculaValoresFaturas(Faturas *f){
    for(int i = 0;i<12;i++){
        f->totalFatMes[i] = calculaFatMes(f->avlF,i);
        f->totalVendasMes[i] = calculaVendasMes(f->avlF,i);
    }
}

double calculaTotalFaturado(Faturas *f) {
    double r = 0;
    for (int i = 0; i < 12; i++)
        r += f->totalFatMes[i];
    return r;
}

int calculaTotalVendido(Faturas *f){
    int r = 0;
    for(int i = 0;i<12;i++)
        r+=f->totalVendasMes[i];
    return r;
}

Fatura *getFatura(Faturas *f,char *produto){
    AVL *aux = f->avlF;
    while(aux && strcmp(aux->key,produto) != 0){
        if(strcmp(produto,aux->key)<0) aux = aux->left;
        else aux = aux->right;
    }
    return aux->str;
}

void freeFaturas(Faturas *f){
    freeAVL(f->avlF,freeFatura);
    free(f);
}


int getSalesMes(AVL *f,int mes,int tipo){
    int r = 0;
    if(f){
        r+= getnumVendasFatura(f->str,0,mes,tipo);
        return r;
    }
    return 0;
}

int getProductSales(Faturas *f, char *prod, int mes,int tipo) {
    return getProductSalesaux(f->avlF,prod,mes,tipo);
}    

int getProductSalesaux (AVL *f, char *prod, int mes,int tipo) {
    if(f==NULL) return 0;
    if(strcmp(f->key,prod)==0) return getSalesMes(f,mes,tipo);      
    else if (strcmp(f->key,prod)<0) return getProductSalesaux(f->right,prod,mes,tipo);
    else return getProductSalesaux(f->left,prod,mes,tipo);
}    

double getProfitMes(AVL *f, int mes,int tipo){
    double r = 0;
    if(f){
        r+= getFaturacaoFatura(f->str,0,mes,tipo);
        return r;
    }
    return 0;
}

double getProductProfit(Faturas *f, char *prod, int mes, int tipo) {
    return getProductProfitaux(f->avlF,prod,mes,tipo);
}  

double getProductProfitaux (AVL *f, char *prod, int mes, int tipo) {
    if(f==NULL) return 0;
    if(strcmp(f->key,prod)==0) return getProfitMes(f,mes,tipo);
    else if (strcmp(f->key,prod)<0) return getProductProfitaux(f->right,prod,mes,tipo);
    else return getProductProfitaux(f->left,prod,mes,tipo);      
}

Fatura **getAllFat(AVL *f,Fatura **array,int *n){
    if(f){
        array[*n] = cloneFatura((Fatura *)f->str);
        *n = *n+1;
        array = getAllFat(f->left,array,n);
        array = getAllFat(f->right,array,n);
    }
    return array;
}

Fatura **getNMaisVendidos(Faturas *f, int n){
    int size = numNodos(f->avlF);
    int a = 0;
    Fatura ** array = malloc(size*sizeof(Fatura *));
    array = getAllFat(f->avlF,array,&a);
    qsort(array,size,sizeof(Fatura *),comparaQuantFatura);
    //printf("%s\n",getProdutoFatura(array[0]));
    for(int i = n;i<size;i++){
        freeFatura(array[i]);
    }
    return array;
}


int totalVendasIntMes (Faturas *f, int mes1, int mes2) {
    int i = mes1-1;
    int res = 0;
    if (mes1<0 || mes2>12) return 0;
    for (i ; i<mes2 ; i++) {
        res += f->totalVendasMes[i];
    }
    return res;
}

double totalFaturacaoIntMes (Faturas *f, int mes1, int mes2) {
    int i = mes1-1;
    double res = 0;
    if (mes1<0 || mes2>12) return 0;
    for (i ; i<mes2; i++) {
        res += f->totalFatMes[i];
    }
    return res;
}
