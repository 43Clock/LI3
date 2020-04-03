#include "queryInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
@brief DONE : Query 3
*/

void faturacaoAndVendasFilialQuery(SGV *sgv) {
	char *bufferP = malloc(sizeof(char) * 32);
	char *bufferM = malloc(sizeof(char) * 32);
	char *buffer = malloc(sizeof(char) * 32);
	int mes;
	int flag = 0;
	int filial;

	//Ciclo para escolher o tipo
	while (1) {
		system("clear");
		printf(BOLDGREEN"\t\t-- Informação produto/mês- -\n\n"RESET);
		printf( BOLDWHITE "Faturação e numero de Vendas:\n\n" RESET );
		printf("0 - Todas as filiais\n");
		printf("1 - Filial a Filial\n\n");

		fgets(buffer, 10, stdin);

		if (strtok(buffer, "\n")) {
			filial = atoi(buffer);
			if (filial == 0 || filial == 1)
				break;
		}
	}

	//Ciclo para verificar se produto é valido
	while (1) {
		system("clear");
		printf(BOLDGREEN"\t\t-- Informação produto/mês--"RESET);
		if (!flag) {
			printf("\n\n");
		}
		else {
			printf(BOLDRED "\n\nProduto Inválido\n\n"RESET);
		}
		printf("Inserir Produto a procurar: \n");
		fgets(bufferP, 32, stdin);
		if (strtok(bufferP, "\n")) {
			if (checkSGVprodValido(sgv, bufferP)) {
				flag = 0;
				break;
			}
			else flag = 1;
		}
	}

	//CIclo para verificar se mes é valido
	while (1) {
		system("clear");
		printf(BOLDGREEN"\t\t-- Informação produto/mês--"RESET);
		if (!flag) {
			printf("\n\n");
		}
		else {
			printf(BOLDRED "\n\nMes Invalido\n\n"RESET);
		}
		printf("Inserir Mês a procurar: \n");
		fgets(bufferM, 32, stdin);
		if (strtok(bufferM, "\n")) {
			mes = atoi(bufferM);
			if (mes > 0 && mes <= 12)
				break;
		}
	}


	if (filial == 0) {
		system("clear");
		int quantidade[2];
		double faturacao[2];
		for (int i = 0; i < 2; i++) {
			quantidade[i] = getSGVvendasProdutoMesFilialTipo(sgv, bufferP, mes, i, 0);
			faturacao[i] = getSGVfaturacaoProdutosMesFilialTipo(sgv, bufferP, mes, i, 0);
		}
		printf(BOLDGREEN"\t\t-- Informação produto/mês--\n\n"RESET);
		printf(BOLDGREEN"Produto: " RESET "%s\n\n", bufferP);
		printf(BOLDWHITE"Total faturado no mês %d\n"RESET, mes );
		printf(BOLDWHITE"\tN: "RESET"%.2f\n", faturacao[0]);
		printf(BOLDWHITE"\tP: "RESET"%.2f\n\n\n", faturacao[1]);
		printf(BOLDWHITE"Número de vendas no mês %d\n"RESET, mes );
		printf(BOLDWHITE"\tN: "RESET"%d\n", quantidade[0]);
		printf(BOLDWHITE"\tP: "RESET"%d\n", quantidade[1]);
	}
	else {
		int i,j;
		system("clear");
		printf(BOLDGREEN"\t\t-- Informação produto/mês--\n\n"RESET);
		printf(BOLDGREEN"Produto: " RESET "%s\n\n", bufferP);
		int quantidade[2][3];
		double faturacao[2][3];
		for (i = 0; i < 2; i++)
			for (j = 0; j < 3; j++) {
				quantidade[i][j] = getSGVvendasProdutoMesFilialTipo(sgv, bufferP, mes, i, j + 1);
				faturacao[i][j] = getSGVfaturacaoProdutosMesFilialTipo(sgv, bufferP, mes, i, j + 1);
			}
		j = 0;
		for (i = 0; i < 3; i++,j = 0) {
			printf(BOLDCYAN"Filial %d:\n" RESET,i+1);
			printf(BOLDWHITE"Total faturado no mês %d\n"RESET, mes);
			printf(BOLDWHITE"\tN: "RESET"%.2f\n", faturacao[j][i]);
			j++;
			printf(BOLDWHITE"\tP: "RESET"%.2f\n\n", faturacao[j][i]);
			j = 0;
			printf(BOLDWHITE"Número de vendas no mês %d\n"RESET, mes );
			printf(BOLDWHITE"\tN: "RESET"%d\n", quantidade[j][i]);
			j++;
			printf(BOLDWHITE"\tP: "RESET"%d\n\n\n", quantidade[j][i]);
		}
	}

	getchar();
	free(buffer);
	free(bufferP);
	free(bufferM);
}

/**
@brief DONE : Query 4
*/
void prodNCompradosQuery(SGV *sgv) {

	char *buffer = malloc(sizeof(char) * 32);
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

/**
@brief DONE : Query 6
*/
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
			dados[i][2 * j] = getQuantFatura(fats[i], j + 1);
			dados[i][2 * j + 1] = getSGVquantCliQueCompraramProd(sgv, j + 1, lista[i]);
		}
	}
	printf(BOLDGREEN "\t\t-- %d Produtos mais vendidos--\n\n"RESET, nProd);
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