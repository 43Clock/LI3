  
/**
 * @file   queryInterface.c
 * @brief  Funções de interface das querys.
 */

#include "queryInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
@brief DONE : Query 1
*/
SGV *escolherPathFicheirosQuery(SGV *sgv) {
	char *bufferC = malloc(sizeof(char) * 64);
	char *bufferP = malloc(sizeof(char) * 64);
	char *bufferV = malloc(sizeof(char) * 64);
	FILE *file;

	int flag = 0, path = 0;

	if (getSGVInfos(sgv) != NULL) {
		destroySGV(sgv);
		sgv = initSGV();
	}
	initSGVinfos(sgv);

	while (1) {
		if(system("clear"));
		if (!flag)
			printf("\n\n");
		else {
			printf(BOLDRED"Path invalido\n"RESET);
		}
		if (path == 0) {
			printf(BOLDWHITE"Inserir path para o fichero de clientes: "RESET);
			if (fgets(bufferC, 64, stdin)) {
				if (strlen(bufferC) == 1) {
					flag = 0;
					path = 1;
					setSGVclientePath(sgv, strdup("../DadosIniciais/Clientes.txt"));
				}
				else if (strtok(bufferC, "\n")) {
					file = fopen(bufferC, "r");
					if (file != NULL) {
						fclose(file);
						flag = 0;
						path = 1;
						setSGVclientePath(sgv, strdup(bufferC));
					}
					else flag = 1;
				}
			}
		}
		else if (path == 1) {
			printf(BOLDWHITE"Inserir path para o fichero de produtos: "RESET);
			if (fgets(bufferP, 64, stdin)) {
				if (strlen(bufferP) == 1) {
					setSGVprodutoPath(sgv, strdup("../DadosIniciais/Produtos.txt"));
					flag = 0;
					path = 2;
				}
				else if (strtok(bufferP, "\n")) {
					file = fopen(bufferP, "r");
					if (file != NULL) {
						fclose(file);
						flag = 0;
						path = 2;
						setSGVprodutoPath(sgv, strdup(bufferP));
					}
					else flag = 1;
				}
			}
		}
		else if (path == 2) {
			printf(BOLDWHITE"Inserir path para o fichero de vendas: "RESET);
			if (fgets(bufferV, 64, stdin)) {
				if (strlen(bufferV) == 1) {
					setSGVvendaPath(sgv, strdup("../DadosIniciais/Vendas_1M.txt"));
					break;
				}
				else if (strtok(bufferV, "\n")) {
					file = fopen(bufferV, "r");
					if (file != NULL) {
						fclose(file);
						setSGVvendaPath(sgv, strdup(bufferV));
						break;
					}
					else flag = 1;
				}
			}
		}
	}
	free(bufferC);
	free(bufferP);
	free(bufferV);
	return sgv;
}

/**
@brief DONE : Query 2
*/
void prodStartedByLetterQuery(SGV * sgv) {
	char search;
	while (1) {
		if(system("clear"));
		printf(BOLDGREEN"\t\t-- Produtos começados por letra _--\n\n"RESET);
		printf("Caracter a procurar:\n");
		search = getchar();
		if (search >= 'A' && search <= 'Z')
			break;
	}
	clock_t start, end;
	start = clock();
	LISTAS *l = getSGVprodStartedByLetter(sgv, search);
	end = clock();
	printf(BOLDBLUE"\nQuery done in %f seconds\n"RESET, ((double)(end - start) / CLOCKS_PER_SEC));
	getchar();
	printMenuPaginas("Produtos começados por letra", getLista(l), getOcupados(l), 12, 6);
	freeLista(l);
}

/**
@brief DONE : Query 3
*/
void faturacaoAndVendasFilialQuery(SGV * sgv) {
	char *bufferP = malloc(sizeof(char) * 32);
	char *bufferM = malloc(sizeof(char) * 32);
	char *buffer = malloc(sizeof(char) * 32);
	int mes;
	int flag = 0;
	int filial;

	while (1) {
		if(system("clear"));
		printf(BOLDGREEN"\t\t-- Informação produto/mês--\n\n"RESET);
		printf( BOLDWHITE "Faturação e numero de Vendas:\n\n" RESET );
		printf("0 - Todas as filiais\n");
		printf("1 - Filial a Filial\n\n");

		if (fgets(buffer, 10, stdin)) {

			if (strtok(buffer, "\n")) {
				filial = atoi(buffer);
				if (filial == 0 || filial == 1)
					break;
			}
		}
	}

	while (1) {
		if(system("clear"));
		printf(BOLDGREEN"\t\t-- Informação produto/mês--"RESET);
		if (!flag) {
			printf("\n\n");
		}
		else {
			printf(BOLDRED "\n\nProduto Inválido\n\n"RESET);
		}
		printf("Inserir Produto a procurar: \n");
		if (fgets(bufferP, 32, stdin)) {
			if (strtok(bufferP, "\n")) {
				if (checkSGVprodValido(sgv, bufferP)) {
					flag = 0;
					break;
				}
				else flag = 1;
			}
		}
	}

	while (1) {
		if(system("clear"));
		printf(BOLDGREEN"\t\t-- Informação produto/mês--"RESET);
		if (!flag) {
			printf("\n\n");
		}
		else {
			printf(BOLDRED "\n\nMes Invalido\n\n"RESET);
		}
		printf("Inserir Mês a procurar: \n");
		if (fgets(bufferM, 32, stdin)) {
			if (strtok(bufferM, "\n")) {
				mes = atoi(bufferM);
				if (mes > 0 && mes <= 12)
					break;
			}
		}
	}

	clock_t start, end;
	int i, j;
	if (filial == 0) {
		if(system("clear"));
		int quantidade[2];
		double faturacao[2];
		start = clock();
		for (i = 0; i < 2; i++) {
			quantidade[i] = getSGVvendasProdutoMesFilialTipo(sgv, bufferP, mes, i, 0);
			faturacao[i] = getSGVfaturacaoProdutosMesFilialTipo(sgv, bufferP, mes, i, 0);
		}
		end = clock();
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
		if(system("clear"));
		printf(BOLDGREEN"\t\t-- Informação produto/mês--\n\n"RESET);
		printf(BOLDGREEN"Produto: " RESET "%s\n\n", bufferP);
		int quantidade[2][3];
		double faturacao[2][3];
		start = clock();
		for (i = 0; i < 2; i++)
			for (j = 0; j < 3; j++) {
				quantidade[i][j] = getSGVvendasProdutoMesFilialTipo(sgv, bufferP, mes, i, j + 1);
				faturacao[i][j] = getSGVfaturacaoProdutosMesFilialTipo(sgv, bufferP, mes, i, j + 1);
			}
		end = clock();
		j = 0;
		for (i = 0; i < 3; i++, j = 0) {
			printf(BOLDCYAN"Filial %d:\n" RESET, i + 1);
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
	printf(BOLDBLUE"\nQuery done in %f seconds\n"RESET, ((double)(end - start) / CLOCKS_PER_SEC));
	getchar();
	free(buffer);
	free(bufferP);
	free(bufferM);
}

/**
@brief DONE : Query 4
*/
void prodNCompradosQuery(SGV * sgv) {

	char *buffer = malloc(sizeof(char) * 32);
	int filial;

	while (1) {
		if(system("clear"));
		printf( BOLDWHITE "Produtos não comprados:\n\n" RESET );
		printf("0 - Todas as filiais\n");
		printf("1 - Filial 1\n");
		printf("2 - Filial 2\n");
		printf("3 - Filial 3\n");

		if (fgets(buffer, 10, stdin)) {

			if (strtok(buffer, "\n")) {
				filial = atoi(buffer);
				if (filial >= 0 && filial <= 3)
					break;
			}
		}
	}
	clock_t start, end;
	start = clock();
	LISTAS * prods = getSGVprodutosNComprados(sgv, filial);
	end = clock();
	printf(BOLDBLUE"\nQuery done in %f seconds\n"RESET, ((double)(end - start) / CLOCKS_PER_SEC));
	getchar();
	printMenuPaginas("Produtos não comprados", getLista(prods), getOcupados(prods), 12, 6);
	freeLista(prods);
	free(buffer);
}

/**
@brief DONE : Query 5
*/
void clientesTodosFilQuery(SGV * sgv) {
	if(system("clear"));
	clock_t start, end;
	start = clock();
	LISTAS *clientes = getSGVclientesTodosFiliais(sgv);
	end = clock();
	printf(BOLDBLUE"\nQuery done in %f seconds\n"RESET, ((double)(end - start) / CLOCKS_PER_SEC));
	getchar();
	printMenuPaginas("Clientes em todas as filiais", getLista(clientes), getOcupados(clientes), 12, 6);
	freeLista(clientes);
}

/**
@brief DONE : Query 6
*/
void prodEclientesNcompQuery(SGV * sgv) {
	if(system("clear"));
	clock_t start, end;
	start = clock();
	printf(BOLDGREEN "\t--Numero de Produtos não comprados e Clientes não compradores --\n\n" RESET);
	printf(BOLDWHITE"Clientes não compradores: " RESET "%d\n", getClientesNaoCompradores(sgv));
	printf(BOLDWHITE"Produtos não comprados  : " RESET "%d\n", getProdutosNaoComprados(sgv));
	end = clock();
	printf(BOLDBLUE"\nQuery done in %f seconds\n"RESET, ((double)(end - start) / CLOCKS_PER_SEC));
	getchar();
}

/**
@brief DONE : Query 7
*/
void clientesMesEFilialQuery(SGV * sgv) {
	char *buffer = malloc(sizeof(char) * 32);
	int flag = 0;

	while (1) {
		if(system("clear"));
		printf(BOLDGREEN"\t\t-- Informação de cliente por mês e filial--"RESET);
		if (!flag) {
			printf("\n\n");
		}
		else {
			printf(BOLDRED "\n\nCliente Invalido\n\n"RESET);
		}
		printf("Inserir Cliente a procurar: \n");
		if (fgets(buffer, 10, stdin)) {
			if (strtok(buffer, "\n")) {
				if (checkSGVclienteValido(sgv, buffer)) {
					flag = 0;
					break;
				}
				else flag = 1;
			}
		}
	}
	clock_t start, end;
	int i, j;
	start = clock();
	int quantidades[3][12];
	for (i = 0; i < 3; i++)
		for (j = 0; j < 12; j++)
			quantidades[i][j] = getSGVNProdClienteMes(sgv, buffer, j + 1, i + 1);
	end = clock();
	printf(BOLDBLUE"\nQuery done in %f seconds\n"RESET, ((double)(end - start) / CLOCKS_PER_SEC));
	getchar();
	if(system("clear"));
	printf(BOLDGREEN"\t\t-- Informação do cliente %s--\n\n"RESET, buffer);
	printTabela((const char*[]) {"Filial 1", "Filial 2", "Filial 3"}, (const char *[]) {
		"JAN", "FEV",
		"MAR", "ABR",
		"MAI", "JUN",
		"JUL", "AGO",
		"SET", "OUT",
		"NOV", "DEZ",
	}, 3, 12, quantidades);
	getchar();
	free(buffer);
}

/**
@brief DONE : Query 8
*/

void totVendaseFatIntMesQuery(SGV * sgv) {
	char *buffer1 = malloc(sizeof(char) * 32);
	char *buffer2 = malloc(sizeof(char) * 32);
	int flag = 0;
	int j, i;

	while (1) {
		if(system("clear"));
		printf(BOLDGREEN"\t\t-- Informação do número de vendas e total faturado num intervalo de meses--"RESET);
		if (!flag) {
			printf("\n\n");
		}
		else {
			printf(BOLDRED "\n\nIntervalo de meses invalido\n\n"RESET);
		}
		printf("Inserir o mes inicial: \n");
		if (fgets(buffer1, 10, stdin)) {
			if (strtok(buffer1, "\n")) {
				j = atoi(buffer1);
				if (j > 0 && j < 12) {
					flag = 0;
					printf("Inserir o mes final: \n");
					if (fgets(buffer2, 10, stdin)) {
						if (strtok(buffer2, "\n")) {
							i = atoi(buffer2);
							if (i > 1 && i <= 12 && j < i) {
								flag = 0;
								break;
							}
							else flag = 1;
						}
					}
				}
				else {
					flag = 1;
				}
			}
		}
	}
	clock_t start, end;
	start = clock();
	printf(BOLDWHITE"Total de vendas no intervalo de meses: " RESET "%d\n", getSGVtotalVendasIntMes(sgv, j, i));
	printf(BOLDWHITE"Total faturado no intervalo de meses: " RESET "%lf\n", getSGVtotalFaturacaoIntMes(sgv, j, i));
	end = clock();
	printf(BOLDBLUE"\nQuery done in %f seconds\n"RESET, ((double)(end - start) / CLOCKS_PER_SEC));
	getchar();
	if(system("clear"));
	free(buffer1);
	free(buffer2);
}

/**
@brief DONE : Query 9
*/

void produtoClientetipoQuery (SGV *sgv) {
	char *buffer = malloc(sizeof(char) * 32);
	char *buffer2 = malloc(sizeof(char) * 32);
	int flag = 0;
	int filial;

	while (1) {
		if(system("clear"));
		printf(BOLDGREEN"\t\t-- Número e lista de clientes que compraram o produto de um certo tipo numa certa filial--"RESET);
		if (!flag) {
			printf("\n\n");
		}
		else {
			printf(BOLDRED "\n\n Produto Invalido\n\n"RESET);
		}
		printf("Inserir Produto a procurar: \n");
		if (fgets(buffer, 10, stdin)) {
			if (strtok(buffer, "\n")) {
				if (checkSGVprodValido(sgv, buffer)) {
					flag = 0;
					break;
				}
				else flag = 1;
			}
		}
	}
	flag = 0;
	while(1) {
		if(system("clear"));
		if (!flag) {
			printf("\n\n");
		}
		else {
			printf (BOLDRED "\n\n Filial Invalida\n\n"RESET);
		}
		printf("Inserir a Filial a procurar: \n");
		if (fgets(buffer2, 10, stdin)) {
			if (strtok(buffer2, "\n")) {
				filial = atoi(buffer2);
				if (filial > 0 && filial <= 3) {	
					flag = 0;
					break;
				}
				else flag = 1;
			}
		}
	}
	char search;
	while (1) {
		if(system("clear"));
		if (!flag) {
			printf("\n\n");
		}
		else {
			printf (BOLDRED "\n\n Tipo Invalido\n\n"RESET);
		}
		printf("Inserir o tipo do Produto: \n");
		search = getchar();
		if (search == 'N' || search == 'P'){
			flag = 0;
			break;
		}
		else flag = 1;
	}
	clock_t start, end;
	start = clock();
	LISTAS *lN = getSGVlClienteProdFilialN(sgv, buffer, filial);
	LISTAS *lP = getSGVlClienteProdFilialP(sgv, buffer, filial);
	end = clock();
	printf(BOLDBLUE"\nQuery done in %f seconds\n"RESET, ((double)(end - start) / CLOCKS_PER_SEC));
	getchar();
	if (search == 'N') {
		printMenuPaginas("Clientes que compraram o produto do tipo N", getLista(lN), getOcupados(lN), 12, 6);
	}
	else {
		printMenuPaginas("Clientes que compraram o produto do tipo P", getLista(lP), getOcupados(lP), 12, 6);
	}
	free(buffer);
	free(buffer2);
	if(system("clear"));
}

/**
@brief DONE : Query 10
*/
void prodMaisCompradosCliMesQuery(SGV * sgv) {
	char *cliente = malloc(sizeof(char) * 32);
	char *mes = malloc(sizeof(char) * 32);
	int flag = 0;
	int m,i;

	while (1) {
		if(system("clear"));
		printf(BOLDGREEN"\t\t-- Informação por ordem decrescente dos produtos mais comprados (quantidade) por um cliente num mes--"RESET);
		if (!flag) {
			printf("\n\n");
		}
		else if (flag == 1) {
			printf(BOLDRED "\n\nCliente invalido\n\n"RESET);
		}
		else {
			printf(BOLDRED "\n\nMes invalido\n\n"RESET);
		}
		printf("Inserir o Cliente a procurar: \n");
		if (fgets(cliente, 10, stdin)) {
			if (strtok(cliente, "\n")) {
				if (checkSGVclienteValido(sgv, cliente)) {
					flag = 0;
					printf("Inserir o mes a procurar: \n");
					if (fgets(mes, 10, stdin)) {
						if (strtok(mes, "\n")) {
							m = atoi(mes);
							if (m > 0 && m <= 12) {
								flag = 0;
								break;
							}
							else flag = 2;
						}
					}
				}
				else {
					flag = 1;
				}
			}
		}
	}
	clock_t start, end;
	start = clock();
	if(system("clear"));
	printf(BOLDGREEN"\t\t-- Informação por ordem decrescente dos produtos mais comprados (quantidade) do cliente %s--\n\n"RESET, cliente);
	CliVendas *a = getSGVclientFavouriteProducts(sgv, cliente, m);
	for(i = 0; i < getClienteVendaOcup(a); i++){
	    printf("%s : %d\n",getProdAtInxdexCliVenda(a,i),getQuantAtIndexMesCliVenda(a,i,m));
	}
	end = clock();
	printf(BOLDBLUE"\nQuery done in %f seconds\n"RESET, ((double)(end - start) / CLOCKS_PER_SEC));
	getchar();
	free(getProdCliente(a));
	free(a);
	free(cliente);
	free(mes);
}

/**
@brief DONE : Query 11
*/
void nMaisVendidosQuery(SGV * sgv) {
	char *buffer = malloc(sizeof(char) * 32);
	int flag = 0;
	int nProd;
	while (1) {
		if(system("clear"));
		printf( BOLDGREEN "--N Produtos mais Vendidos--\n"RESET );
		if (!flag) {
			printf("\n\n");
		}
		else {
			printf(BOLDRED "Número Invalido\n\n"RESET);
		}
		printf("Número de produtos a apresentar: \n");
		if (fgets(buffer, 32, stdin)) {
			nProd = atoi(buffer);
			if (nProd > 0)
				break;
			else flag = 1;
		}
	}
	free(buffer);
	if(system("clear"));
	clock_t start, end;
	start = clock();
	Fatura **fats = getSGVNmaisVendidos(sgv, nProd);
	int size = getSGVNumeroNodos (sgv);
	if (nProd > size) nProd = size;
	char *lista[nProd];
	int dados[nProd][6];
	int i, j;
	for (i = 0; i < nProd; i++) {
		lista[i] = getProdutoFatura(fats[i]);
		for (j = 0; j < 3; j++) {
			dados[i][2 * j] = getQuantFatura(fats[i], j + 1);
			dados[i][2 * j + 1] = getSGVquantCliQueCompraramProd(sgv, j + 1, lista[i]);
		}
	}
	end = clock();
	printf(BOLDBLUE"\nQuery done in %f seconds\n"RESET, ((double)(end - start) / CLOCKS_PER_SEC));
	getchar();
	printf(BOLDGREEN "\t\t-- %d Produtos mais vendidos--\n\n"RESET, nProd);
	printTabela((const char**)lista, (const char *[]) {
		"F1 Unidades",
		"F1 Clientes",
		"F2 Unidades",
		"F2 Clientes",
		"F3 Unidades",
		"F3 Clientes",
	}, nProd, 6, dados);
	for (i = 0; i < nProd; i++) {
		free(lista[i]);
		freeFatura(fats[i]);
	}
	free(fats);
	getchar();
}
/**
@brief DONE : Query 12
*/
void clientTopProfitquery (SGV *sgv) {
	char *cliente = malloc(sizeof(char) * 32);
	char *buffer = malloc(sizeof(char) * 32);
	int flag = 0;
	int nProd;
	while (1) {
		if(system("clear"));
		printf( BOLDGREEN "--N produtos em que o cliente gastou mais dinheiro--\n"RESET );
		if (!flag) {
			printf("\n\n");
		}
		else {
			printf(BOLDRED "\n\nCliente Invalido\n\n"RESET);
		}
		printf("Inserir Cliente a procurar: \n");
		if (fgets(cliente, 10, stdin)) {
			if (strtok(cliente, "\n")) {
				if (checkSGVclienteValido(sgv, cliente)) {
					flag = 0;
					break;
				}
				else flag = 1;
			}
		}
	}
	while (1) {
		if (!flag) {
			printf("\n\n");
		}
		else {
			printf(BOLDRED "Número Invalido\n\n"RESET);
		}
		printf("Número de produtos a apresentar: \n");
		if (fgets(buffer, 32, stdin)) {
			nProd = atoi(buffer);
			if (nProd > 0)
				break;
			else flag = 1;
		}
	}
	free(buffer);
	if(system("clear"));
	clock_t start, end;
	int i;
	start = clock();
	printf(BOLDGREEN"\t\t-- Informação por ordem decrescente dos produtos nos quais o cliente %s gastou mais dinheiro: --\n\n"RESET, cliente);
	CliVendas *a = getSGVclientTopProfit(sgv, cliente, nProd);
	for (i = 0; i < getClienteVendaOcup(a); i++) {
		printf("%s : %.2f\n", getProdAtInxdexCliVenda(a, i), getFatAtIndexCliVenda(a, i));
	}
	end = clock();
	printf(BOLDBLUE"\nQuery done in %f seconds\n"RESET, ((double)(end - start) / CLOCKS_PER_SEC));
	getchar();
	fflush(stdout);
	freeCliVendas(a);
	free(cliente);
}

/**
@brief DONE : Query 13
*/

void lastQuery (SGV *sgv){
	if(system("clear"));
	printf(BOLDGREEN"\t\t-- Informações dos ficheiros lidos --\n\n"RESET);
	printf("%s\n", getInfoCliPath(sgv));
	printf("%d\n", getInfoLinhasCPath(sgv));
	printf("%d\n\n", getInfoValidasCPath(sgv));

	printf("%s\n", getInfoProdPath(sgv));
	printf("%d\n", getInfoLinhasPPath(sgv));
	printf("%d\n\n", getInfoValidasPPath(sgv));

	printf("%s\n", getInfoVendaPath(sgv));
	printf("%d\n", getInfoLinhasVPath(sgv));
	printf("%d\n\n", getInfoValidasVPath(sgv));

	getchar();
}
