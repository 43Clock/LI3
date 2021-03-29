/**
 * @file   view.c
 * @brief  Funções usadas para apresentação de tabelas e listas.
 */

#include "view.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief      Função que calcula o número de digitos de um certo numero. Usada para calcular os espaçamentos corretos.
 *
 * @param[in]  n     O número que vai ser utilizado.
 *
 * @return     Retorna o número de digitos do inteiro n:
 */
int howManyDigits(int n){
	int r = (n>0)?0:1;
	while(n!=0){
		n /= 10;
		r++;
	}
	return r;
}

/**
 * @brief      Função que replica uma string um determinado número de vezes. Usado para fazer o espaçamento correto.
 *
 * @param      s     A string que vai ser replicada.
 * @param[in]  n     O número de vez que a string vai ser replicada.
 */
void replicar(char *s,int n){
	if(n != 0){
		char *buffer = malloc(sizeof(char)*strlen(s)*n+1);
		buffer[0] = '\0';
		while(n--){
			strcat(buffer,s);
		}
		printf("%s",buffer);
		free(buffer);
	}
}

/**
 * @brief      Função que imprime no ecrã as "strings" que estão num array de "strings". Função auxiliar para @ref printMenuPaginas.
 *
 * @param      str       O array de strings para apresentar.
 * @param[in]  total     O tamanho total do array de strings.
 * @param[in]  nLinhas   O número de linhas a apresentar.
 * @param[in]  nColunas  O número de colunas a apresentar.
 * @param[in]  pagina    A pagina atual a apresentar.
 */
void printStrings(char **str,int total,int nLinhas,int nColunas,int pagina){
	int i,j,pos,r  = 0;

	for(i = nLinhas*pagina;i<nLinhas*(pagina+1);i++){
		for(j = 0;j<nColunas && j+i*nColunas<total;j++){
			pos = j+i*nColunas;
			printf("%d.",pos+1);
			replicar(" ",howManyDigits(total)+1-howManyDigits(pos+1));
			printf("%s      ",str[pos]);
		}
		r++;
		printf("\n");
	}
	replicar("\n",nLinhas-r+2);
}

/**
 * @brief      Função que cria uma lista com várias paginas que representam um array de strings.
 *
 * @param      titulo    O titulo que fica no topo do ecrã.
 * @param      str       O array de "strings" a imprimir.
 * @param[in]  total     O número total de "strings" no array.
 * @param[in]  nLinhas   O número de linhas de cada página.
 * @param[in]  nColunas  O número de colunas de cada página.
 */
void printMenuPaginas(char *titulo,char **str,int total,int nLinhas,int nColunas){
	char option;
	int page = 0;

	int nPaginas = (total%(nLinhas*nColunas))?(total/(nLinhas*nColunas)):total/(nColunas*nLinhas)-1;
	while(1){
		if(system("clear"));
		printf(BOLDGREEN "\t-- %s --\n\n" RESET,titulo); 
		printf("Total: %d\n",total);
		printStrings(str,total,nLinhas,nColunas,page);
		printf("\t%d/%d [(n)ext/(p)revious/(b)ack)]\n",page+1,nPaginas+1);
		option = getchar();
		switch(option){
			case 'n':
				page = (page+1<=nPaginas)?page+1:page;
				break;

			case 'p':
				page =(page-1>=0)?page-1:page;
				break;
			
			case 'b':
				return;

			default:
				break;
		}
	}
}

/**
 * @brief      Função que imprime um separadar de linhas de uma tabela, dependendo do tamanho que cada colunas tem.
 *
 * @param      sizeCols  Array de inteiros com informação do tamanho que cada coluna deve ter.
 * @param[in]  nColunas  Número total de colunas.
 */
void printSeparador(int *sizeCols,int nColunas){
	int j;
	for(j = 0;j<=nColunas;j++){
		printf("+");
		replicar("-",sizeCols[j]);
	}
	printf("+\n");
}

/**
 * @brief      Função que imprime uma tabela no ecrã.
 *
 * @param      linhasTab   O nome de cada linha da tabela.
 * @param      colunasTab  O nome de cada coluna da tabela.
 * @param[in]  nLinhas     O número de linhas da tabela.
 * @param[in]  nColunas    O número de colunas da tabela.
 * @param      dados       Um array de inteiros com a informação do que colocar em cada posição da tabela.
 */
void printTabela(const char *linhasTab[],const char *colunasTab[],int nLinhas, int nColunas,int dados[nLinhas][nColunas]){
	int i,j,size = 0;
	int sizeCols[nColunas+1];
	memset(sizeCols,0,sizeof(int)*(nColunas+1));

	for(i = 0;i<nLinhas;i++)
		size = (size<(int)strlen(linhasTab[i]))?(int)strlen(linhasTab[i]):size;
	sizeCols[0] = size+2;
	for(j = 0;j<nColunas;j++){
		sizeCols[j+1] = strlen(colunasTab[j])+2;
		for(i = 0;i<nLinhas;i++)
			sizeCols[j+1] = (sizeCols[j+1]< howManyDigits(dados[i][j])+2)?howManyDigits(dados[i][j])+2:sizeCols[j+1];
	}

	printSeparador(sizeCols,nColunas);
	printf("|");
	replicar(" ",sizeCols[0]);
	for(j = 0;j<nColunas;j++){
		printf("| %s",colunasTab[j]);
		replicar(" ",sizeCols[j+1]-strlen(colunasTab[j])-1);
	}
	printf("|\n");
	printSeparador(sizeCols,nColunas);

	for(i = 0;i<nLinhas;i++){
		printf("| %s",linhasTab[i]);
		replicar(" ",sizeCols[0]-strlen(linhasTab[i])-1);
		for(j = 0;j<nColunas;j++){
			printf("| %d",dados[i][j]);
			replicar(" ",sizeCols[j+1]-howManyDigits(dados[i][j])-1);
		}
		printf("|\n");
		printSeparador(sizeCols,nColunas);
	}
}