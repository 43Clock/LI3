  
/**
 * @file   vendas.c
 * @brief  Funções relativas ás vendas.
 */

#include "vendas.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct venda{
	char *prod;    /**<Nome do Produto da venda>*/ 
	double preco;  /**<Preco do produto nesta venda>*/
	int unidades;  /**<Quantidade do produto em unidades>*/
	char tipo;     /**<Tipo da venda>*/
	char *cliente; /**<Nome do Cliente>*/
	int mes;       /**<Mes da venda>*/
	int filial;    /**<Filial a que a venda pertence>*/
};

/**
 * @brief      Função que cria uma venda verificando se o cliente e o produto são validos.
 *
 * @return     Retorna a venda criada.
 */
VENDA* createVenda(char *linha, LISTAS *clientes, LISTAS *prodts){
	char *prod,*cliente,tipo,*p;
	double preco;
	int unidades,mes,filial;
	p = strtok(linha," ");
	prod = p;
	p = strtok(NULL," ");
	preco = (double)atof(p);
	p = strtok(NULL," ");
	unidades = atoi(p);
	p = strtok(NULL," ");
	tipo = p[0];
	p = strtok(NULL," ");
	cliente = p;
	p = strtok(NULL," ");
	mes = atoi(p);
	p = strtok(NULL," ");
	filial = atoi(p);

	if((searchMatch(clientes,0,getOcupados(clientes)-1,cliente) !=-1)  && (searchMatch(prodts,0,getOcupados(prodts)-1,prod)!=-1)){
		VENDA *venda = malloc(sizeof(VENDA));
		venda->prod = prod;
		venda->preco = preco;
		venda->unidades = unidades;
		venda->tipo = tipo;
		venda->cliente = cliente;
		venda->mes = mes;
		venda->filial = filial;
		return venda;
	}
	return NULL;
}

/**
 * @brief      Função que retorna o cliente da venda
 *
 * @return     Retorna uma string com o cliente da venda.
 */
char *getClienteVenda(VENDA *v){
	return strdup(v->cliente);
}

/**
 * @brief      Função que retorna o produto da venda
 *
 * @return     Retorna uma string com o produto da venda.
 */
char *getProdVenda(VENDA *v){
	return strdup(v->prod);
}

/**
 * @brief      Função que retorna o mes da venda
 *
 * @return     Retorna o mes da venda.
 */
int getMesVenda(VENDA *v){
	return v->mes;
}

/**
 * @brief      Função que retorna a quantidade da venda
 *
 * @return     Retorna a quantidade(nº de unidades do produto) da venda.
 */
int getQuantVenda(VENDA *v){
	return v->unidades;
}

/**
 * @brief      Função que retorna a filial da venda
 *
 * @return     Retorna a filial da venda.
 */
int getFilialVenda(VENDA *v){
	return v->filial;
}

/**
 * @brief      Função que retorna o tipo da venda
 *
 * @return     Retorna o tipo da venda.
 */
int getTipoVenda(VENDA *v){
	return (v->tipo == 'N')?0:1;
}

/**
 * @brief      Função que retorna o preco do produto
 *
 * @return     Retorna o preco do produto.
 */
double getPrecoVenda(VENDA *v){
	return v->preco;
}

/**
 * @brief      Função que retorna o preco total da venda
 *
 * @return     Retorna o preco total da venda.
 */
double getTotalVenda(VENDA *v){
	return v->preco*v->unidades;
}

/**
 * @brief      Função que liberta o espaço alocado para a Venda.
 */
void freeVenda(void *v){
	VENDA *vd = (VENDA *) v;
	free(vd->cliente);
	free(vd->prod);
	free(v);
}
