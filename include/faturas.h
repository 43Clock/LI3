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
int getSalesMes(AVL *f,int mes,int tipo);
int getProductSales(Faturas *f, char *prod, int mes,int tipo);
int getProductSalesaux (AVL *f, char *prod, int mes,int tipo);
double getProfitMes(AVL *f, int mes,int tipo);
double getProductProfit(Faturas *f, char *prod, int mes,int tipo);
double getProductProfitaux (AVL *f, char *prod, int mes, int tipo);
Fatura **getNMaisVendidos(Faturas *f, int n);
int totalVendasIntMes (Faturas *f, int mes1, int mes2);
double totalFaturacaoIntMes (Faturas *f, int mes1, int mes2);


#endif