#ifndef VENDAS_H
#define VENDAS_H

typedef struct listas LISTAS;

typedef struct venda{
	char *prod;
	float preco;
	int unidades;
	char tipo;
	char *cliente;
	int mes;
	int filial;
}VENDA;

typedef struct vendas{
	int size;
	int ocup;
	VENDA *vendas;
}VENDAS;

void initVendas(VENDAS *vendas);
void reallocVendas(VENDAS *vendas);
void addVenda(VENDAS *vendas,char *linha,LISTAS *cliente,LISTAS *prod);
void filterStr(char *str);

#endif