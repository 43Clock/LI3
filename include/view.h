#ifndef view_h
#define view_h

#include "macros.h"

void printMenuPaginas(char *titulo,char **str,int total,int nLinhas,int nColunas);
void printTabela(const char *linhasTab[],const char *colunasTab[],int nLinhas, int nColunas,int dados[nLinhas][nColunas]);


#endif