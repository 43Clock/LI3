#ifndef sgv_h
#define sgv_h 

#include "listas.h"
#include "vendas.h"
#include "mytree.h"
#include "sgv.h"
#include "faturas.h"
#include "filial.h"
#include "view.h"

#define MAX 64

typedef struct sgv SGV;

SGV *initSGV();
void destroySGV(SGV *sgv);




LISTAS *getSGVprodutosNComprados(SGV *sgv,int filial);//Query 4
LISTAS *getSGVclientesTodosFiliais(SGV *sgv);//Query 5

int getClientesNaoCompradores(SGV *sgv);
int getProdutosNaoComprados(SGV *sgv);

Fatura **getSGVNmaisVendidos(SGV *sgv,int n);
int getSGVquantCliQueCompraramProd(SGV *sgv,int filial,char *prod);

#endif