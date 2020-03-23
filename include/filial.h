#ifndef filial_h
#define filial_h

#include "mytree.h"
#include "listas.h"
#include "vendas.h"

typedef struct filiais Filiais;

void listaProdNcomprados(AVL* produtos,int filial,LISTAS *prod,LISTAS *res);

#endif