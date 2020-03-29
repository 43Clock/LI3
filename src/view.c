#include "view.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int howManyDigits(int n){
	int r = (n>0)?0:1;
	while(n!=0){
		n /= 10;
		r++;
	}
	return r;
}

void replicar(char *s,int n){//função para meter o num de espacos corretos para ficar tudo alinhado
	if(n != 0){
		char *buffer = malloc(sizeof(char)*strlen(s)*n+1);
		buffer[0] = '\0';
		while(n--){
			strcat(buffer,s);
		}
		printf("%s",buffer);
		free(buffer);
		//fflush(stdout);
	}
}

void printStrings(char **str,int total,int nLinhas,int nColunas,int pagina){
	int i,j,pos,r  = 0;

	for(i = nLinhas*pagina;i<nLinhas*(pagina+1);i++){
		for(j = 0;j<nColunas;j++){
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

void printMenuPaginas(char **str,int total,int nLinhas,int nColunas){
	char option;
	int page = 0;

	int nPaginas = (total%(nLinhas*nColunas))?(total/(nLinhas*nColunas)):total/(nColunas*nLinhas)-1;
	while(1){
		system("clear");
		//printf("%s\n", ); mete o titulo
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