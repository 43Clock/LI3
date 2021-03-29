#ifndef VENDAS_H
#define VENDAS_H

#include "listas.h"

typedef struct venda VENDA;


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

void freeVenda(void *v);


#endif