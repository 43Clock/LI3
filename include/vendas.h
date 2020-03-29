#ifndef VENDAS_H
#define VENDAS_H

#include "listas.h"
#include "mytree.h"

typedef struct listas LISTAS;

typedef struct venda{
	char *prod;
	double preco;
	int unidades;
	char tipo;
	char *cliente;
	int mes;
	int filial;
}VENDA;

typedef struct vendas{
	int size;
	int ocup;
	VENDA *vendas;
}VENDAS;

void initVendas(VENDAS *vendas);
void reallocVendas(VENDAS *vendas);
void addVenda(VENDAS *vendas,char *linha,LISTAS *cliente,LISTAS *prod);
VENDA* createVenda(char *linha, LISTAS *clientes, LISTAS *prodts);

void filterStr(char *str);
char *getClienteVenda(VENDA *v);

char *getProdVenda(VENDA *v);

int getMesVenda(VENDA *v);

int getQuantVenda(VENDA *v);

int getFilialVenda(VENDA *v);

int getTipoVenda(VENDA *v);

double getPrecoVenda(VENDA *v);

double getTotalVenda(VENDA *v);


#endif