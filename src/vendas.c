#include "vendas.h"
#include "mytree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void initVendas(VENDAS *vendas){
	vendas->size = 1;
	vendas->ocup = 0;
	vendas->vendas = malloc(sizeof(struct venda));
}

void reallocVendas(VENDAS *vendas){
	VENDA *tmp = malloc(2*vendas->size*sizeof(struct venda));
	for(int i = 0;i<vendas->size;i++){
		tmp[i].prod = strdup(vendas->vendas[i].prod);
		tmp[i].preco = vendas->vendas[i].preco;
		tmp[i].unidades = vendas->vendas[i].unidades;
		tmp[i].tipo = vendas->vendas[i].tipo;
		tmp[i].cliente = strdup(vendas->vendas[i].cliente);
		tmp[i].mes = vendas->vendas[i].mes;
		tmp[i].filial = vendas->vendas[i].filial;
	}
	free(vendas->vendas);
	vendas->vendas = tmp;
	vendas->size *= 2;
}

int searchMatch(LISTAS *lista,int l, int r,char *str){
	while(l<=r){
		int m = l +(r-l)/2;
		if(strcmp(lista->listas[m],str) == 0) return m;
		if(strcmp(lista->listas[m],str)<0) l = m+1;
		else r =m-1;
	}
	return -1;
}


void addVenda(VENDAS *vendas,char *linha, LISTAS *clientes, LISTAS *prodts){
	char *prod,*cliente,tipo,*p;
	double preco;
	int unidades,mes,filial;
	p = strtok(linha," ");
	prod = strdup(p);
	p = strtok(NULL," ");
	preco = (double)atof(p);
	p = strtok(NULL," ");
	unidades = atoi(p);
	p = strtok(NULL," ");
	tipo = p[0];
	p = strtok(NULL," ");
	cliente = strdup(p);
	p = strtok(NULL," ");
	mes = atoi(p);
	p = strtok(NULL," ");
	filial = atoi(p);

	if((searchMatch(clientes,0,clientes->ocup-1,cliente) !=-1)  && (searchMatch(prodts,0,prodts->ocup-1,prod)!=-1)){
		vendas->vendas[vendas->ocup].prod = prod;
		vendas->vendas[vendas->ocup].preco = preco;
		vendas->vendas[vendas->ocup].unidades = unidades;
		vendas->vendas[vendas->ocup].tipo = tipo;
		vendas->vendas[vendas->ocup].cliente = cliente;
		vendas->vendas[vendas->ocup].mes = mes;
		vendas->vendas[vendas->ocup].filial = filial;
		vendas->ocup++;
	}
}

VENDA* createVenda(char *linha, LISTAS *clientes, LISTAS *prodts){
	char *prod,*cliente,tipo,*p;
	double preco;
	int unidades,mes,filial;
	p = strtok(linha," ");
	prod = strdup(p);
	p = strtok(NULL," ");
	preco = (double)atof(p);
	p = strtok(NULL," ");
	unidades = atoi(p);
	p = strtok(NULL," ");
	tipo = p[0];
	p = strtok(NULL," ");
	cliente = strdup(p);
	p = strtok(NULL," ");
	mes = atoi(p);
	p = strtok(NULL," ");
	filial = atoi(p);

	if((searchMatch(clientes,0,clientes->ocup-1,cliente) !=-1)  && (searchMatch(prodts,0,prodts->ocup-1,prod)!=-1)){
		VENDA *venda = malloc(sizeof(VENDA));
		venda->prod = prod;
		venda->preco = preco;
		venda->unidades = unidades;
		venda->tipo = tipo;
		venda->cliente = cliente;
		venda->mes = mes;
		venda->filial = filial;
		return venda;
	}
	return NULL;
}

char *getClienteVenda(VENDA *v){
	char *aux = malloc(strlen(v->cliente)+1);
	strcpy(aux,v->cliente);
	return aux;
}

char *getProdVenda(VENDA *v){
	//char *aux = malloc(strlen(v->prod)+1);
	//strcpy(aux,v->prod);
	return v->prod;
}

int getMesVenda(VENDA *v){
	return v->mes;
}

int getQuantVenda(VENDA *v){
	return v->unidades;
}

int getFilialVenda(VENDA *v){
	return v->filial;
}

int getTipoVenda(VENDA *v){
	return (v->tipo == 'N')?0:1;
}

double getPrecoVenda(VENDA *v){
	return v->preco;
}

double getTotalVenda(VENDA *v){
	return v->preco*v->unidades;
}

void freeVenda(void *v){
	VENDA *vd = (VENDA *) v;
	free(vd->cliente);
	free(vd->prod);
	free(v);
}