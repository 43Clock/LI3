#include "queryInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
@brief DONE : Query 4
*/
void prodNCompradosQuery(SGV *sgv) {

	char *buffer = malloc(sizeof(char) * 10);
	int filial;

	while (1) {
		system("clear");
		printf( BOLDWHITE "Produtos não comprados:\n\n" RESET );
		printf("0 - Todas as filiais\n");
		printf("1 - Filial 1\n");
		printf("2 - Filial 2\n");
		printf("3 - Filial 3\n");

		fgets(buffer, 10, stdin);

		if (strtok(buffer, "\n")) {
			filial = atoi(buffer);
			if (filial >= 0 && filial <= 3)
				break;
		}
	}
	LISTAS * prods = getSGVprodutosNComprados(sgv, filial);
	printMenuPaginas("Produtos não comprados", prods->listas, prods->ocup, 12, 6);
	freeLista(prods);
	free(buffer);
}

/**
@brief DONE : Query 5
*/
void clientesTodosFilQuery(SGV *sgv) {

	LISTAS *clientes = getSGVclientesTodosFiliais(sgv);
	printMenuPaginas("Clientes em todas as filiais", clientes->listas, clientes->ocup, 12, 6);
	freeLista(clientes);
}

void prodEclientesNcompQuery(SGV *sgv) {
	system("clear");
	printf(BOLDGREEN "\t--Numero de Produtos não comprados e Clientes não compradores --\n\n" RESET);
	printf(BOLDWHITE"Clientes não compradores: " RESET "%d\n", getClientesNaoCompradores(sgv));
	printf(BOLDWHITE"Produtos não comprados  : " RESET "%d\n", getProdutosNaoComprados(sgv));
	getchar();
}

/**
@brief DONE : Query 11
*/
void nMaisVendidosQuery(SGV *sgv) {
	char *buffer = malloc(sizeof(char) * 32);
	int flag = 0;
	int nProd;
	while (1) {
		system("clear");
		printf( BOLDGREEN "--N Produtos mais Vendidos--\n"RESET );
		if (!flag) {
			printf("\n\n");
		}
		else {
			printf(BOLDRED "Número Invalido\n\n"RESET);
		}
		printf("Número de produtos a apresentar: \n");
		fgets(buffer, 32, stdin);
		nProd = atoi(buffer);
		if (nProd > 0)
			break;
		else flag = 1;
	}
	free(buffer);
	system("clear");
	char *lista[nProd];
	int dados[nProd][6];
	Fatura **fats = getSGVNmaisVendidos(sgv, nProd);
	for (int i = 0; i < nProd; i++) {
		lista[i] = getProdutoFatura(fats[i]);
		for (int j = 0; j < 3; j++) {
			dados[i][2 * j] = getQuantFatura(fats[i],j+1);
			dados[i][2 * j + 1] = getSGVquantCliQueCompraramProd(sgv, j + 1, lista[i]);
		}
	}
	printf(BOLDGREEN "\t\t-- %d Produtos mais vendidos--\n\n"RESET,nProd);
	printTabela((const char**)lista, (const char *[]) {
		"F1 Unidades",
		"F1 Clientes",
		"F2 Unidades",
		"F2 Clientes",
		"F3 Unidades",
		"F3 Clientes",
	}, nProd, 6, dados);
	for (int i = 0; i < nProd; i++) {
		free(lista[i]);
		freeFatura(fats[i]);
	}
	getchar();
}