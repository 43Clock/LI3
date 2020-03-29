#include "queryInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
@brief DONE : Query 4
*/
void prodNCompradosQuery(SGV *sgv){

	char *buffer = malloc(sizeof(char)*10);
	int filial;

	while(1){
		system("clear");
		printf( BOLDWHITE "Produtos não comprados:\n\n" RESET );
		printf("0 - Todas as filiais\n");
		printf("1 - Filial 1\n");
		printf("2 - Filial 2\n");
		printf("3 - Filial 3\n");

		fgets(buffer,10,stdin);

		if(strtok(buffer,"\n")){
			filial = atoi(buffer);
			if(filial>= 0 && filial<=3)
				break;
		}
	}
	LISTAS * prods = getSGVprodutosNComprados(sgv,filial);
	printMenuPaginas("Produtos não comprados",prods->listas,prods->ocup,12,6);
	freeLista(prods);
	free(buffer);
}

/**
@brief DONE : Query 5
*/
void clientesTodosFilQuery(SGV *sgv){

	LISTAS *clientes = getSGVclientesTodosFiliais(sgv);
	printMenuPaginas("Clientes em todas as filiais",clientes->listas,clientes->ocup,12,6);
	freeLista(clientes);
}

void prodEclientesNcompQuery(SGV *sgv){
	system("clear");
	printf(BOLDGREEN "\t--Numero de Produtos não comprados e Clientes não compradores --\n\n" RESET);
	printf(BOLDWHITE"Clientes não compradores: " RESET "%d\n",getClientesNaoCompradores(sgv));
	printf(BOLDWHITE"Produtos não comprados  : " RESET "%d\n",getProdutosNaoComprados(sgv));
	getchar();
}

