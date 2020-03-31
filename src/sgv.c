#include "sgv.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct sgv {
	LISTAS *clientes;
	LISTAS *produtos;
	Faturas *faturas;
	Filiais *filiais;
};

int myCompare (const void * a, const void * b ) { // a e b são apontadores para alguma coisa (void)
    const char *pa = *(const char**)a;
    				  // Esta parte que dizer um apontador para uma string(por exemplo char *a),
    				 // mas tem de ter ** por o a ja é um apontador
    const char *pb = *(const char**)b;

    return strcmp(pa,pb);
}

SGV *initSGV(){
	FILE *file;
	int i,nclientes = 0,nprodutos = 0,nvendas = 0;
	file = fopen("../DadosIniciais/Clientes.txt","r");
	char test[MAX];

	SGV *sgv = malloc(sizeof(struct sgv));

	sgv->clientes = initLista();

	//Ciclo que percorre o ficheiro de clientes e colocaos todos num array
	while(fgets(test,MAX,file)!= NULL){
		if(checkClientes(test)){
			filterStr(test);
			if(sgv->clientes->size == sgv->clientes->ocup) reallocLista(sgv->clientes);
			addLista(sgv->clientes,test);
			nclientes++;
		}
	}
	//Sorting 
	qsort(sgv->clientes->listas,nclientes,sizeof(char*),myCompare);
	fclose(file);
	
	file = fopen("../DadosIniciais/Produtos.txt","r");
	sgv->produtos = initLista();

	//Ciclo que percorre o ficheiro de clientes e colocaos todos num array
	while(fgets(test,MAX,file)!= NULL){
		if(checkProdutos(test)){
			filterStr(test);
			if(sgv->produtos->size == sgv->produtos->ocup) reallocLista(sgv->produtos);
			addLista(sgv->produtos,test);
			nprodutos++;
		}
	}
	//Sorting 
	qsort(sgv->produtos->listas,nprodutos,sizeof(char *),myCompare);
	
	fclose(file);
	
	VENDA *venda = NULL;
	sgv->faturas = initFaturas();
	sgv->filiais = initFiliais();

	file =  fopen("../DadosIniciais/Vendas_1M.txt","r");
	while(fgets(test,MAX,file)!=NULL){
		filterStr(test);
		venda = createVenda(test,sgv->clientes,sgv->produtos);
		if(venda){
			addVendaToFilial(venda,sgv->filiais);
			addVendaToFaturas(sgv->faturas,venda);
			nvendas++;
		}
	}
	calculaValoresFaturas(sgv->faturas);
	//printf("%f\n",calculaTotalFaturado(sgv->faturas));
	fclose(file);


	/*clock_t start,end;
	start = clock();
	
	
	
	end = clock();
	printf("%f\n",((double)(end-start)/CLOCKS_PER_SEC));*/

	//printMenuPaginas(allF->clientes,clientes.ocup,15,6);	
	return sgv;
}

LISTAS *getSGVprodutosNComprados(SGV *sgv,int filial){
	LISTAS *res = initLista(); 
	listaProdNcomprados(sgv->filiais,filial,sgv->produtos,res);
	return res;
}

LISTAS *getSGVclientesTodosFiliais(SGV *sgv){
	LISTAS *r = listaClientesTodosFliais(sgv->filiais,sgv->clientes);
	qsort(r->listas,r->ocup,sizeof(char *),myCompare);
	return r;
}

int getClientesNaoCompradores(SGV *sgv){
	return numCliNcompradores(sgv->filiais,sgv->clientes);
}

int getProdutosNaoComprados(SGV *sgv){
	return numProdNcomprados(sgv->filiais,sgv->produtos);
}

void destroySGV(SGV *sgv){
	freeLista(sgv->clientes);
	freeLista(sgv->produtos);
	freeFaturas(sgv->faturas);
	freeFiliais(sgv->filiais);
	free(sgv);
}