#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpretador.h"


void printMenu() {
	printf(BOLDBLUE"\t\t-- Menu Inicial --\n\n"RESET);
	printf(BOLDCYAN"[1]"RESET" - Carregar ficheiros\n");
	printf(BOLDCYAN"[2]"RESET" - Navegar produtos por letra\n");
	printf(BOLDCYAN"[3]"RESET" - Informação de produto por mês\n");
	printf(BOLDCYAN"[4]"RESET" - Produtos não comprados\n");
	printf(BOLDCYAN"[5]"RESET" - Clientes em todas as filiais\n");
	printf(BOLDCYAN"[6]"RESET" - Clientes não compradores e Produtos não comprados\n");
	printf(BOLDCYAN"[7]"RESET" - Tabela de informação por cliente durante um ano\n");
	printf(BOLDCYAN"[8]"RESET" - Total faturado num intervalo de tempo\n");
	printf(BOLDCYAN"[9]"RESET" - Stats de um produto por filial\n");
	printf(BOLDCYAN"[10]"RESET" - Produtos mais comprados por cliente por mês\n");
	printf(BOLDCYAN"[11]"RESET" - Produtos mais vendidos\n");
	printf(BOLDCYAN"[12]"RESET" - Produtos em que cliente mais dinheiro gastou\n");
	printf(BOLDCYAN"[13]"RESET" - Informações dos ficheiros lidos\n");
	printf(BOLDCYAN"[q]"RESET" - Sair do programa\n");
}

void interpreter(SGV *sgv) {
	int loop = 1, flag = 0, comando;
	char *buffer = malloc(sizeof(char) * 10);
	while (loop) {
		while (1) {
			fflush(stdout);
			comando = -1;
			if(system("clear"));
			printMenu();
			if (flag == 0) {
				printf("\n\n");
			}
			else if (flag == 1) {
				printf(BOLDRED "\n\nComando Inválido\n\n"RESET);
			}
			else printf(BOLDRED "\n\nEstrutura ainda não foi inicializada\n\n"RESET);
			printf("\nInserir Comando: \n");
			if (fgets(buffer, 10, stdin)) {
				if (strtok(buffer, "\n")) {
					if (strlen(buffer) == 1 && buffer[0] == 'q') {
						comando = 99;
						break;
					}
					comando = atoi(buffer);
					if (getSGVInfos(sgv) == NULL && comando != 1)
						flag = 2;
					else {
						comando = atoi(buffer);
						if (comando > 0 && comando < 15)
							break;
						else flag = 1;
					}
				}
			}
		}
		switch (comando) {
		case 1:
			sgv = escolherPathFicheirosQuery(sgv);
			if(system("clear"));
			printf(HIDE_CURSOR);
			printf(BLINK"\nLOADING ...\n"RESET);
			printf(SHOW_CURSOR);
			sgv = loadSGVFromFiles(sgv, getInfoCliPath(sgv), getInfoProdPath(sgv), getInfoVendaPath(sgv));
			break;
		case 2:
			prodStartedByLetterQuery(sgv);
			break;
		case 3:
			faturacaoAndVendasFilialQuery(sgv);
			break;
		case 4:
			prodNCompradosQuery(sgv);
			break;
		case 5:
			clientesTodosFilQuery(sgv);
			break;
		case 6:
			prodEclientesNcompQuery(sgv);
			break;
		case 7:
			clientesMesEFilialQuery(sgv);
			break;
		case 8:
			totVendaseFatIntMesQuery(sgv);
			break;
		case 9:
			produtoClientetipoQuery(sgv);
			break;
		case 10:
			prodMaisCompradosCliMesQuery(sgv);
			break;
		case 11:
			nMaisVendidosQuery(sgv);
			break;
		case 12:
			clientTopProfitquery(sgv);
			break;
		case 13:
			lastQuery(sgv);
			break;
		case 99:
			loop = 0;
		default:
			break;
		}
	}
	free(buffer);
	if (getSGVInfos(sgv) != NULL)
		destroySGV(sgv);
}