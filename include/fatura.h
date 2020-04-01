#ifndef fatura_h
#define fatura_h

#include "vendas.h"

typedef struct fatura Fatura;

Fatura* initFat(VENDA *v);

void addFat(Fatura *f,VENDA *v);

int getnumVendasFatura(Fatura *f,int filial,int mes,int tipo);

int getQuantFatura(Fatura *f,int filial);

double getFaturacaoFatura(Fatura *f,int filial,int mes,int tipo);

int comparaQuantFatura(const void *a,const void *b);

Fatura *cloneFatura(Fatura *f);

void freeFatura(void *f);

char *getProdutoFatura(Fatura *f);



#endif