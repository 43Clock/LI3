#ifndef filial_h
#define filial_h

#include "mytree.h"
#include "listas.h"
#include "vendas.h"

typedef struct filiais Filiais;

void listaProdNcomprados(Filiais* produtos,int filial,LISTAS *prod,LISTAS *res);
void addVendaToFilial(VENDA *v,Filiais *f);
Filiais *initFiliais();
void freeFiliais(Filiais *f);

#endif