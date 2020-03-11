#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listas.h"
#include "vendas.h"

#define MAX 64

int myCompare (const void * a, const void * b ) { // a e b são apontadores para alguma coisa (void)
    const char *pa = *(const char**)a;
    				  // Esta parte que dizer um apontador para uma string(por exemplo char *a),
    				 // mas tem de ter ** por o a ja é um apontador
    const char *pb = *(const char**)b;

    return strcmp(pa,pb);
}

int main (){
	FILE *file;
	int i,nclientes = 0,nprodutos = 0;
	file = fopen("../DadosIniciais/Clientes.txt","r");
	char test[MAX];

	LISTAS clientes,produtos;
	initLista(&clientes);

	//Ciclo que percorre o ficheiro de clientes e colocaos todos num array
	while(fgets(test,MAX,file)!= NULL){
		if(!checkClientes(test)){
			puts("Ficheiro Invalido");
			return -1;
		}
		filterStr(test);
		if(clientes.size == clientes.ocup) reallocLista(&clientes);
		addLista(&clientes,test);
		nclientes++;
	}
	//Sorting 
	qsort(clientes.listas,nclientes,sizeof(char*),myCompare);
	

	fclose(file);
	file = fopen("../DadosIniciais/Produtos.txt","r");
	initLista(&produtos);

	//Ciclo que percorre o ficheiro de clientes e colocaos todos num array
	while(fgets(test,MAX,file)!= NULL){
		if(!checkProdutos(test)){
			puts("Ficheiro Invalido");
			//return -1;
		}
		filterStr(test);
		if(produtos.size == produtos.ocup) reallocLista(&produtos);
		addLista(&produtos,test);
		nprodutos++;
	}
	//Sorting 
	qsort(produtos.listas,nprodutos,sizeof(char *),myCompare);

	fclose(file);
	VENDAS vendas; 
	initVendas(&vendas);
	fopen("../DadosIniciais/Vendas_1M.txt","r");
	while(fgets(test,MAX,file)!=NULL){
		filterStr(test);
		if(vendas.size == vendas.ocup) reallocVendas(&vendas);
		addVenda(&vendas,test,&clientes,&produtos);
	}
	fclose(file);
	//printf("%d\n",vendas.ocup );
	file = fopen("../DadosIniciais/Vendas_1MValidas.txt","w");
	for(i = 0;i<vendas.ocup;i++){
		fprintf(file, "%s %f %d %c %s %d %d\n",
			vendas.vendas[i].prod,
			vendas.vendas[i].preco,
			vendas.vendas[i].unidades,
			vendas.vendas[i].tipo,
			vendas.vendas[i].cliente,
			vendas.vendas[i].mes,
			vendas.vendas[i].filial);
	}
	fclose(file);
}