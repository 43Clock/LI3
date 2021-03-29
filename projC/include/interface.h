#ifndef interface_h
#define interface_h 

#include "listas.h"
#include "vendas.h"
#include "faturas.h"
#include "filial.h"
#include "macros.h"

#define MAX 64

typedef struct sgv SGV;
typedef struct infos Infos;

SGV *initSGV();
SGV *loadSGVFromFiles(SGV *sgv,char *pathC,char *pathP,char *pathV);
void destroySGV(SGV *sgv);
void initSGVinfos(SGV *sgv);

void setSGVclientePath(SGV *sgv,char * path);
void setSGVprodutoPath(SGV *sgv,char * path);
void setSGVvendaPath(SGV *sgv,char * path);

char *getInfoCliPath(SGV *sgv);
char *getInfoProdPath(SGV *sgv);
char *getInfoVendaPath(SGV *sgv);
int getInfoLinhasCPath(SGV *sgv);
int getInfoLinhasPPath(SGV *sgv);
int getInfoLinhasVPath(SGV *sgv);
int getInfoValidasCPath(SGV *sgv);
int getInfoValidasPPath(SGV *sgv);
int getInfoValidasVPath(SGV *sgv);

Infos *getSGVInfos(SGV *sgv);

LISTAS *getSGVprodStartedByLetter(SGV *sgv,char letter);

int getSGVvendasProdutoMesFilialTipo(SGV *sgv,char *prod,int mes,int tipo,int filial);
double getSGVfaturacaoProdutosMesFilialTipo(SGV *sgv,char *prod,int mes,int tipo,int filial);

LISTAS *getSGVprodutosNComprados(SGV *sgv,int filial);
LISTAS *getSGVclientesTodosFiliais(SGV *sgv);

int getClientesNaoCompradores(SGV *sgv);
int getProdutosNaoComprados(SGV *sgv);

Fatura **getSGVNmaisVendidos(SGV *sgv,int n);
int getSGVNumeroNodos (SGV *sgv);
int getSGVquantCliQueCompraramProd(SGV *sgv,int filial,char *prod);
int getSGVNProdClienteMes (SGV *sgv, char *cliente, int mes, int filial);

int checkSGVprodValido(SGV *sgv,char *prod);
int checkSGVclienteValido(SGV *sgv,char *prod);

int getSGVtotalVendasIntMes(SGV *sgv,int mes,int mes2);
double getSGVtotalFaturacaoIntMes(SGV *sgv,int mes,int mes2);

LISTAS *getSGVlClienteProdFilialN(SGV *sgv,char *prod,int filial);
LISTAS *getSGVlClienteProdFilialP(SGV *sgv,char *prod,int filial);

CliVendas *getSGVclientFavouriteProducts(SGV *sgv,char *cliente,int mes);

CliVendas *getSGVclientTopProfit(SGV *sgv,char *cliente,int n);
#endif