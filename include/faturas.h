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
void freeFaturas(Faturas *f);
int getSalesMes(AVL *f,int mes);
int getProductSales(Faturas *f, char *prod, int mes);
int getProductSalesaux (AVL *f, char *prod, int mes);
double getProfitMes(AVL *f, int mes);
double getProductProfit(Faturas *f, char *prod, int mes);
double getProductProfitaux (AVL *f, char *prod, int mes);
Fatura **getNMaisVendidos(Faturas *f, int n);


#endif