#ifndef faturas_h
#define faturas_h

#include "fatura.h"
#include "mytree.h"
typedef struct faturas Faturas;

Faturas * initFaturas();
void addVendaToFaturas(Faturas *f,VENDA *v);
int calculaTotalVendido(Faturas *f);
double calculaTotalFaturado(Faturas *f);
void calculaValoresFaturas(Faturas *f);
Fatura *getFatura(Faturas *f,char *produto);

#endif