#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mytree.h"
#include "listas.h"
#include "vendas.h"
#include "faturas.h"
#include "filial.h"
#include "view.h"

#include "sgv.h"

#define MAX 64


/*int main (){
	FILE *file;
	int i,nclientes = 0,nprodutos = 0;
	file = fopen("/home/luis43/Aulas/LI3/Aula1/DadosIniciais/Clientes.txt","r");
	char test[MAX];

	LISTAS clientes,produtos;
	initLista(&clientes);

	//Ciclo que percorre o ficheiro de clientes e colocaos todos num array
	while(fgets(test,MAX,file)!= NULL){
		if(checkClientes(test)){
			filterStr(test);
			if(clientes.size == clientes.ocup) reallocLista(&clientes);
			addLista(&clientes,test);
			nclientes++;
		}
	}
	//Sorting 
	qsort(clientes.listas,nclientes,sizeof(char*),myCompare);
	

	fclose(file);
	file = fopen("/home/luis43/Aulas/LI3/Aula1/DadosIniciais/Produtos.txt","r");
	initLista(&produtos);

	//Ciclo que percorre o ficheiro de clientes e colocaos todos num array
	while(fgets(test,MAX,file)!= NULL){
		if(checkProdutos(test)){
			filterStr(test);
			if(produtos.size == produtos.ocup) reallocLista(&produtos);
			addLista(&produtos,test);
			nprodutos++;
		}
	}
	//Sorting 
	qsort(produtos.listas,nprodutos,sizeof(char *),myCompare);
	fclose(file);
	
	VENDAS vendas; 
	initVendas(&vendas);
	file =  fopen("/home/luis43/Aulas/LI3/Aula1/DadosIniciais/Vendas_1M.txt","r");
	while(fgets(test,MAX,file)!=NULL){
		filterStr(test);
		if(vendas.size == vendas.ocup) reallocVendas(&vendas);
		addVenda(&vendas,test,&clientes,&produtos);
	}
	fclose(file);
	//printf("%d\n",vendas.ocup );
	file = fopen("/home/luis43/Aulas/LI3/Aula1/DadosIniciais/Vendas_1MValidas.txt","w");
	for(i = 0;i<vendas.ocup;i++){
		fprintf(file, "%s %.2f %d %c %s %d %d\n",
			vendas.vendas[i].prod,
			vendas.vendas[i].preco,
			vendas.vendas[i].unidades,
			vendas.vendas[i].tipo,
			vendas.vendas[i].cliente,
			vendas.vendas[i].mes,
			vendas.vendas[i].filial);
	}
	fclose(file);
	clock_t start,end;
	start = clock();
	AVL *arvoreVendas = NULL;
	AVL *aux = NULL;
	for(i = 0;i<vendas.ocup;i++){
		arvoreVendas = insert(arvoreVendas,vendas.vendas[i].prod,(VENDA *)&vendas.vendas[i]);
	}
	end = clock();
	printf("%f\n",((double)(end-start)/CLOCKS_PER_SEC));

	/*LISTAS bipbop;
	initLista(&bipbop);
	listaProdNcomprados(arvoreVendas,3,&produtos,&bipbop);
	printf("%d\n",bipbop.ocup);*/

	/*printMenuPaginas(clientes.listas,clientes.ocup,10,5);

	Faturas *fat = initFaturas();
	for(i = 0;i<vendas.ocup;i++){
		addVendaToFaturas(fat,&vendas.vendas[i]);
	}
    calculaValoresFaturas(fat);
	
	Fatura *f = getFatura(fat,"NR1091");
	printf("%f\n %d",calculaTotalFaturado(fat),calculaTotalVendido(fat));
}*/

int main(){
	SGV *sgv = initSGV();
}