  
/**
 * @file   interface.c
 * @brief  Funções relativas ao sgv.
 */

#include "interface.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct sgv {
	LISTAS *clientes; /**<Lista de todos os clientes*/
	LISTAS *produtos; /**<Lista de todos os produtos*/
	Faturas *faturas; /**<Estrutura faturas*/
	Filiais *filiais; /**<Estrutura filiais*/
	Infos * infos; /**<Estrutura infos*/
};

struct infos{
	char *fileC; /**<Caminho para o ficheiro C*/
	int linhasC; /**<Número de linhas lidas do ficheiro C*/
	int validasC; /**<Número de linhas válidas do ficheiro C*/
	char *fileP; /**<Caminho para o ficheiro P*/
	int linhasP; /**<Número de linhas lidas do ficheiro P*/
	int validasP; /**<Número de linhas válidas do ficheiro P*/
	char *fileV; /**<Caminho para o ficheiro V*/
	int linhasV; /**<Número de linhas lidas do ficheiro V*/
	int validasV; /**<Número de linhas válidas do ficheiro V*/
};

/**
 * @brief      Função de comparação de duas strings.
 *
 * @param[in]  a     Void pointer que depos será casted para uma string.
 * @param[in]  b     Void pointer que depos será casted para uma string.
 *
 * @return     Retorna positivo caso b seja maior que a. Ordena por ordem decrescente.
 */

int myCompare (const void * a, const void * b ) {
    const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;

    return strcmp(pa,pb);
}

/**
 * @brief      Função de inicialização da estrutura SGV.
 *
 * @return     Retorna a estrutura SGV com todas as estruturas que a constituem vazias.
 */
SGV *initSGV(){
	SGV *sgv = malloc(sizeof(SGV));
	sgv->clientes = initLista();
	sgv->produtos = initLista();
	sgv->faturas = initFaturas();
	sgv->filiais = initFiliais();
	sgv->infos = NULL;
	return sgv;
}

/**
 * @brief      Função de inicialização da estrutura infos que está na SGV.
 *
 * @param      sgv     Apontador para a estrutura sgv onde iremos inicializar a estrutura infos.
 */
void initSGVinfos(SGV *sgv){
	sgv->infos = malloc(sizeof(Infos));
	sgv->infos->linhasC = 0;
	sgv->infos->linhasP = 0;
	sgv->infos->linhasV = 0;
	sgv->infos->validasC = 0;
	sgv->infos->validasP = 0;
	sgv->infos->validasV = 0;
}

/**
 * @brief      Função que dá free á estrutura infos.
 *
 * @param      f     Apontador para a estrutura infos que será libertada.
 */
void freeInfos(Infos *f){
	free(f->fileC);
	free(f->fileP);
	free(f->fileV);
	free(f);
}

/**
 * @brief      Função de inicialização da estrutura sgv com os dados de ficheiros.
 *
 * @param      sgv       Apontador para a estrutura sgv que irá ser inicializada.
 * @param      pathC     Path para o ficheiro C que vai inicializar a estrutura sgv.
 * @param      pathP     Path para o ficheiro P que vai inicializar a estrutura sgv.
 * @param      pathV     Path para o ficheiro V que vai inicializar a estrutura sgv.
 *
 * @return     Retorna a estrutura sgv atualizada com os dados dos ficheiros.
 */
SGV *loadSGVFromFiles(SGV *sgv,char *pathC,char *pathP,char *pathV){
	FILE *file;

	file = fopen(pathC,"r");
	char test[MAX];
	clock_t start,end;
	start = clock();

	
	while(fgets(test,MAX,file)!= NULL){
		sgv->infos->linhasC++;
		if(checkClientes(test)){
			filterStr(test);
			if(getSize(sgv->clientes) == getOcupados(sgv->clientes)) reallocLista(sgv->clientes);
			addLista(sgv->clientes,test);
			sgv->infos->validasC++;
		}
	}

	qsort(getLista(sgv->clientes),sgv->infos->validasC,sizeof(char*),myCompare);
	fclose(file);
	
	file = fopen(pathP,"r");

	while(fgets(test,MAX,file)!= NULL){
		sgv->infos->linhasP++;
		if(checkProdutos(test)){
			filterStr(test);
			if(getSize(sgv->produtos) == getOcupados(sgv->produtos)) reallocLista(sgv->produtos);
			addLista(sgv->produtos,test);
			sgv->infos->validasP++;
		}
	}

	qsort(getLista(sgv->produtos),sgv->infos->validasP,sizeof(char *),myCompare);
	
	fclose(file);
	
	VENDA *venda = NULL;

	file =  fopen(pathV,"r");
	while(fgets(test,MAX,file)!=NULL){
		sgv->infos->linhasV++;
		filterStr(test);
		venda = createVenda(test,sgv->clientes,sgv->produtos);
		if(venda){
			addVendaToFilial(venda,sgv->filiais);
			addVendaToFaturas(sgv->faturas,venda);
			sgv->infos->validasV++;
		}
		free(venda);
	}

	fclose(file);
	end = clock();
	if(system("clear"));
   	printf(BOLDBLUE"\nLoad done in %f seconds\n"RESET, ((double)(end - start) / CLOCKS_PER_SEC));
    getchar();

	return sgv;
}

/**
 * @brief      Função que obtém o caminho para o ficheiro C com o qual a sgv foi inicializada.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 *
 * @return     Caminho para o ficheiro C com o qual a sgv foi inicializada.
 */

char *getInfoCliPath(SGV *sgv){
	return sgv->infos->fileC;
}

/**
 * @brief      Função que obtém o caminho para o ficheiro P com o qual a sgv foi inicializada.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 *
 * @return     Caminho para o ficheiro P com o qual a sgv foi inicializada.
 */

char *getInfoProdPath(SGV *sgv){
	return sgv->infos->fileP;
}

/**
 * @brief      Função que obtém o caminho para o ficheiro V com o qual a sgv foi inicializada.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 *
 * @return     Caminho para o ficheiro V com o qual a sgv foi inicializada.
 */

char *getInfoVendaPath(SGV *sgv){
	return sgv->infos->fileV;
}

/**
 * @brief      Função que obtém o número de linhas do ficheiro C com o qual a sgv foi inicializada.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 *
 * @return     Número de linhas do ficheiro C com o qual a sgv foi inicializada.
 */

int getInfoLinhasCPath(SGV *sgv){
	return sgv->infos->linhasC;
}

/**
 * @brief      Função que obtém o número de linhas do ficheiro P com o qual a sgv foi inicializada.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 *
 * @return     Número de linhas do ficheiro P com o qual a sgv foi inicializada.
 */

int getInfoLinhasPPath(SGV *sgv){
	return sgv->infos->linhasP;
}

/**
 * @brief      Função que obtém o número de linhas do ficheiro V com o qual a sgv foi inicializada.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 *
 * @return     Número de linhas do ficheiro V com o qual a sgv foi inicializada.
 */

int getInfoLinhasVPath(SGV *sgv){
	return sgv->infos->linhasV;
}

/**
 * @brief      Função que obtém o número de linhas válidas do ficheiro C com o qual a sgv foi inicializada.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 *
 * @return     Número de linhas válidas do ficheiro C com o qual a sgv foi inicializada.
 */

int getInfoValidasCPath(SGV *sgv){
	return sgv->infos->validasC;
}

/**
 * @brief      Função que obtém o número de linhas válidas do ficheiro P com o qual a sgv foi inicializada.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 *
 * @return     Número de linhas válidas do ficheiro P com o qual a sgv foi inicializada.
 */

int getInfoValidasPPath(SGV *sgv){
	return sgv->infos->validasP;
}

/**
 * @brief      Função que obtém o número de linhas válidas do ficheiro V com o qual a sgv foi inicializada.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 *
 * @return     Número de linhas válidas do ficheiro V com o qual a sgv foi inicializada.
 */

int getInfoValidasVPath(SGV *sgv){
	return sgv->infos->validasV;
}


/**
 * @brief      Função que inicializa o caminho para o ficheiro C na estrutura infos.
 *
 * @param      i       Apontador para a estrutura infos.
 * @param      path    Caminho para o ficheiro C.
 */

void setInfoClientePath(Infos *i,char *path){
	i->fileC = path;
}

/**
 * @brief      Função que inicializa o caminho para o ficheiro P na estrutura infos.
 *
 * @param      i       Apontador para a estrutura infos.
 * @param      path    Caminho para o ficheiro P.
 */

void setInfoProdutoPath(Infos *i,char *path){
	i->fileP = path;	
}

/**
 * @brief      Função que inicializa o caminho para o ficheiro V na estrutura infos.
 *
 * @param      i       Apontador para a estrutura infos.
 * @param      path    Caminho para o ficheiro V.
 */

void setInfoVendaPath(Infos *i,char *path){
	i->fileV = path;
}

/**
 * @brief      Função que inicializa o caminho para o ficheiro C na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 * @param      path    Caminho para o ficheiro C.
 */

void setSGVclientePath(SGV *sgv,char * path){
	setInfoClientePath(sgv->infos,path);
}

/**
 * @brief      Função que inicializa o caminho para o ficheiro P na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 * @param      path    Caminho para o ficheiro P.
 */

void setSGVprodutoPath(SGV *sgv,char * path){
	setInfoProdutoPath(sgv->infos,path);
}

/**
 * @brief      Função que inicializa o caminho para o ficheiro V na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 * @param      path    Caminho para o ficheiro V.
 */

void setSGVvendaPath(SGV *sgv,char * path){
	setInfoVendaPath(sgv->infos,path);
}

/**
 * @brief      Função que devolve a estrutura infos presente na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 *
 * @return     Estrutura infos presente na estrutura sgv.
 */

Infos *getSGVInfos(SGV *sgv){
	return sgv->infos;
}


/**
 * @brief      Função que devolve a lista dos produtos começados por uma determinada letra na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 * @param      letter    letra.
 *
 * @return     Lista dos produtos começados pela letra.
 */

LISTAS *getSGVprodStartedByLetter(SGV *sgv,char letter){
	return getProductsStartedByLetter(sgv->produtos,letter);
}

/**
 * @brief      Função que devolve o número de Nodos presentes na estrutura faturas presente na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 *
 * @return     Número de Nodos.
 */

int getSGVNumeroNodos (SGV *sgv) {
	return numeroNodosAux (sgv->faturas);
}

/**
 * @brief      Função que determina o número de vendas feitas para um determinado produto num determinado mês com um determinado tipo numa determinada filial presentes na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 * @param      prod      String com o produto a procurar.
 * @param[in]  mes       Mês a procurar.
 * @param[in]  tipo      Tipo a procurar.
 * @param[in]  filial    Filial a procurar
 *
 * @return     Número de vendas feitas para o produto no mês com o tipo na filial, presente na estrutura sgv.
 */

int getSGVvendasProdutoMesFilialTipo(SGV *sgv,char *prod,int mes,int tipo,int filial){
	return getProductSales(sgv->faturas,prod,mes,tipo,filial);
}

/**
 * @brief      Função que determina a faturação total de um determinado produto num determinado mês com um determinado tipo numa determinada filial presente na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 * @param      prod      String com o produto a procurar.
 * @param[in]  mes       Mês a procurar.
 * @param[in]  tipo      Tipo a procurar.
 * @param[in]  filial    Filial a procurar
 *
 * @return     Faturação total do produto no mês com o tipo na filial, presente na estrutura sgv.
 */

double getSGVfaturacaoProdutosMesFilialTipo(SGV *sgv,char *prod,int mes,int tipo,int filial){
	return getProductProfit(sgv->faturas,prod,mes,tipo,filial);
}

/**
 * @brief      Função que determina a lista de produtos não comprados presentes na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 * @param[in]  filial    Filial a procurar
 *
 * @return     Lista de produtos não comprados presentes na estrutura sgv.
 */

LISTAS *getSGVprodutosNComprados(SGV *sgv,int filial){
	LISTAS *res = initLista(); 
	listaProdNcomprados(sgv->filiais,filial,sgv->produtos,res);
	return res;
}

/**
 * @brief      Função que determina a lista dos clientes que compraram em todas as filiais presentes na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 *
 * @return     Lista dos clientes que compraram em todas as filiais.
 */

LISTAS *getSGVclientesTodosFiliais(SGV *sgv){
	LISTAS *r = listaClientesTodosFliais(sgv->filiais,sgv->clientes);
	qsort(getLista(r),getOcupados(r),sizeof(char *),myCompare);
	return r;
}

/**
 * @brief      Função que determina o número de clientes que compraram um determinado produto numa determinada filial presentes na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 * @param[in]  filial    Filial a procurar.
 * @param      prod      Produto a procurar.
 *
 * @return     Número de clientes que compraram o produto na filial.
 */

int getSGVquantCliQueCompraramProd(SGV *sgv,int filial,char *prod){
	return nVendaProduto(sgv->filiais,filial,prod);
}

/**
 * @brief      Função que determina uma lista de fatura com os N produtos mais vendidos presentes na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 * @param[in]  n         Número de produtos que queremos obter.
 *
 * @return     Lista de fatura com os N produtos mais vendidos.
 */

Fatura **getSGVNmaisVendidos(SGV *sgv,int n){
	return getNMaisVendidos(sgv->faturas,n);
}

/**
 * @brief      Função que determinao número de clientes que não compraram nenhum produto presentes na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 *
 * @return      Número de clientes que não compraram nenhum produto.
 */

int getClientesNaoCompradores(SGV *sgv){
	return numCliNcompradores(sgv->filiais,sgv->clientes);
}

/**
 * @brief      Função que determinao número de produtos que não foram comprados presentes na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 *
 * @return      Número de produtos que não foram comprados.
 */

int getProdutosNaoComprados(SGV *sgv){
	return numProdNcomprados(sgv->filiais,sgv->produtos);
}

/**
 * @brief      Função que calcula a quantidade comprada por um cliente num determinado mês e filial presente na estrutura sgv.
 *
 * @param      sgv      Apontador para a estrutura sgv.
 * @param      cliente  O cliente a procurar.
 * @param[in]  mes      O mês a procurar
 * @param[in]  filial   A filial a procurar
 *
 * @return     Retorna a quantidade comprada por um cliente.
 */

int getSGVNProdClienteMes (SGV *sgv, char *cliente, int mes, int filial){
	return nprodClienteMes(sgv->filiais,cliente,mes,filial);
}

/**
 * @brief      Função que determina se um produto está presente na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 * @param      prod      O produto a procurar.
 *
 * @return     Retorna 1 ou 0 se o produto existir ou não existir na sgv respetivamente.
 */

int checkSGVprodValido(SGV *sgv,char *prod){
	return existeNaLista(sgv->produtos,prod);
}

/**
 * @brief      Função que determina se um cliente está presente na estrutura sgv.
 *
 * @param      sgv       Apontador para a estrutura sgv.
 * @param      prod      O cliente a procurar.
 *
 * @return     Retorna 1 ou 0 se o cliente existir ou não existir na sgv respetivamente.
 */

int checkSGVclienteValido(SGV *sgv,char *prod){
	return existeNaLista(sgv->clientes,prod);
}

/**
 * @brief      Função que determina o número total de vendas num intervalo de meses presentes na estrutura sgv.
 *
 * @param      sgv      Apontador para a estrutura sgv.
 * @param[in]  mes1     O primeiro mês do intervalo.
 * @param[in]  mes2     O segundo mês do intervalo.
 *
 * @return     Retorna o número total de vendas no intervalo de meses.
 */

int getSGVtotalVendasIntMes(SGV *sgv,int mes,int mes2){
	return totalVendasIntMes(sgv->faturas,mes,mes2);
}

/**
 * @brief      Função que determina a faturação total num intervalo de meses presentes na estrutura sgv.
 *
 * @param      sgv      Apontador para a estrutura sgv.
 * @param[in]  mes1     O primeiro mês do intervalo.
 * @param[in]  mes2     O segundo mês do intervalo.
 *
 * @return     Retorna a faturação total no intervalo de meses.
 */

double getSGVtotalFaturacaoIntMes(SGV *sgv,int mes,int mes2){
	return totalFaturacaoIntMes(sgv->faturas,mes,mes2);
}

/**
 * @brief      Função que devolve a lista de todos os clientes que compraram um produto sem ser em promoção presentes na sgv.
 *
 * @param      sgv     Apontador para a estrutura sgv.
 * @param      prod    O produto que se quer procurar.
 * @param[in]  filial  A filial que se quer procurar.
 *
 * @return     Retorna a lista de clientes que compraram um produto não em promoção.
 */

LISTAS *getSGVlClienteProdFilialN(SGV *sgv,char *prod,int filial){
	return lClienteProdFilialN(sgv->filiais,prod,filial);
}

/**
 * @brief      Função que devolva a lista de todos os clientes que compraram um produto em promoção presentes na  estrutura sgv.
 *
 * @param      sgv     Apontador para a estrutura sgv.
 * @param      prod    O produto que se quer procurar.
 * @param[in]  filial  A filial que se quer procurar.
 *
 * @return     Retorna a lista de clientes que compraram um produto em promoção.
 */

LISTAS *getSGVlClienteProdFilialP(SGV *sgv,char *prod,int filial){
	return lClienteProdFilialP(sgv->filiais,prod,filial);
}

/**
 * @brief      Função que retorna a lista ordenada dos produtos mais comprados por um cliente presentes na estrutura sgv.
 *
 * @param      sgv      Apontador para a estrutura sgv.
 * @param      cliente  Cliente a procurar.
 * @param[in]  mes      Mês a procurar.
 *
 * @return     Retorna uma estrutura CliVendas ordenada com os produtos mais comprados por um cliente.
 */

CliVendas *getSGVclientFavouriteProducts(SGV *sgv,char *cliente,int mes){
	return clientFavouriteProducts(sgv->filiais,cliente,mes);
}

/**
 * @brief      Função que retorna a lista ordenada dos produtos em que foram gastados mais dinheiro por um cliente presente na estrutura sgv.
 *
 * @param      sgv      Apontador para a estrutura sgv.
 * @param      cliente  Cliente a procurar.
 * @param[in]  n        Mês a procurar.
 *
 * @return     Retorna uma estrutura CliVendas com a lista ordenada dos produtos em que um cliente gastou mais dinheiro.
 */

CliVendas *getSGVclientTopProfit(SGV *sgv,char *cliente,int n){
	return clientTopProfit(sgv->filiais,cliente,n);
}


/**
 * @brief      Função que dá free á estrutura sgv.
 *
 * @param      sgv     Apontador para a estrutura sgv que se pretende libertar.
 */

void destroySGV(SGV *sgv){
	freeLista(sgv->clientes);
	freeLista(sgv->produtos);
	freeFaturas(sgv->faturas);
	freeFiliais(sgv->filiais);
	freeInfos(sgv->infos);
	free(sgv);
}
