#ifndef filial_h
#define filial_h

#include "mytree.h"
#include "listas.h"
#include "vendas.h"

typedef struct prodCliente ProdCliente;
typedef struct filiais Filiais;
typedef struct cliVendas CliVendas;


void listaProdNcomprados(Filiais* produtos,int filial,LISTAS *prod,LISTAS *res);
void addVendaToFilial(VENDA *v,Filiais *f);
Filiais *initFiliais();
void freeFiliais(Filiais *f);
void freeProdCli(ProdCliente *p);
int comparaQuantProdCliente (const void *a, const void *b);
int comparaFatProdCliente (const void *a, const void *b);
LISTAS *listaClientesTodosFliais(Filiais * f, LISTAS *clientes);
int numProdNcomprados(Filiais *f,LISTAS *prod);
int numCliNcompradores(Filiais *f,LISTAS *clientes);
int nVendaProduto(Filiais *f, int filial, char *prod);
int nprodClienteMes (Filiais * f, char * cliente, int mes, int filial);
int nprodClienteMesAux ( AVL *f, char * cliente, int mes);
LISTAS  *lClienteProdFilialN (Filiais * f, char *prod, int filial);
LISTAS *lClienteProdFilialNAux  (AVL *f , char *prod);
LISTAS  *lClienteProdFilialP (Filiais * f, char *prod, int filial);
LISTAS *lClienteProdFilialPAux  (AVL *f , char *prod);
CliVendas *clientFavouriteProducts (Filiais *f, char *cliente, int mes);
CliVendas *clientTopProfit (Filiais *f, char *cliente, int n);
int valorAlocar(AVL *f, char *cliente, int mes);
ProdCliente **clientFavouriteProductsAux (AVL *f, char *cliente, int mes, ProdCliente **array);
void addProdCliente (ProdCliente **array, ProdCliente *a, int j);
ProdCliente *cloneProdCliente(ProdCliente *a);
void freeCliVendas(void *cv);
int getClienteVendaOcup(CliVendas *c);
char *getProdAtInxdexCliVenda(CliVendas *c,int index);
int getQuantAtIndexMesCliVenda(CliVendas *c,int index,int mes);
double getFatAtIndexCliVenda(CliVendas *c,int index);
ProdCliente **getProdCliente(CliVendas *c);
#endif