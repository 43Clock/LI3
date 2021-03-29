  
/**
 * @file   fatura.c
 * @brief  Funções relativas a uma fatura.
 */
#include <stdlib.h>
#include <string.h>
#include "fatura.h"
#include "mytree.h"

struct fatura {
	char *produto; /**<O código do produto*/
	int numVendas[2][12][3]; /**<Numero de vendas de um produto organizado por tipo, mês e filial*/
	double fatTotal[2][12][3]; /**<Total faturado por um produto organizado por tipo, mês e filial*/
	int quantPorFilial[3];/**< Array com as quantidades de um produto vendidas por filial*/
};


/**
 * @brief      Função que inicializa a estrutura Fatura com uma venda.
 *
 *  @param      v     VENDA que será adicionada à estrutura.
 *
 * @return     Retorna a estrutura inicializada com as informações da venda.
 */
Fatura * initFat(VENDA *v) {
	Fatura *f = malloc(sizeof(struct fatura));
	f->produto = getProdVenda(v);
	memset(f->numVendas, 0, 2 * 12 * 3 * sizeof(int));
	memset(f->fatTotal, 0, 2 * 12 * 3 * sizeof(double));
	memset(f->quantPorFilial, 0, 3 * sizeof(int));
	addFat(f, v);
	return f;
}

/**
 * @brief      Função que adiciona uma estrutura VENDA na estrutura Fatura.
 *
 *  @param      f     Estrutura Fatura que vai ser atualizada.
 *  @param      v     Estrutura VENDA que vai ser adicionada à Fatura.
 */
void addFat(Fatura *f, VENDA *v) {
	int mes, filial, tipo;
	mes = getMesVenda(v);
	filial = getFilialVenda(v);
	tipo = getTipoVenda(v);
	f->numVendas[tipo][mes - 1][filial - 1]++;
	f->fatTotal[tipo][mes - 1][filial - 1] += getTotalVenda(v);
	f->quantPorFilial[filial - 1] += getQuantVenda(v);
}

/**
 * @brief      Função de comparação das quantidades de duas faturas.
 *
 * @param[in]  a     Void pointer que depos será casted para a estrutura Fatura.
 * @param[in]  b     Void pointer que depos será casted para a estrutura Fatura.
 *
 * @return     Retorna positivo caso b seja maior que a.Ordena por ordem decrescente.
 */
int comparaQuantFatura(const void *a, const void *b) {
	Fatura *aa = *(Fatura **) a;
	Fatura *bb = *(Fatura **) b;
	return getQuantFatura(bb, 0) - getQuantFatura(aa, 0);
}

/**
 * @brief      Função que determina o numero de Vendas de um produto de um certo tipo num certo mes e filial.
 *
 * @param      f      Estrutra Fatura.
 * @param[in]  filial filial onde procurar.    
 * @param[in]  mes    mes onde procurar.
 * @param[in]  tipo   tipo  do produto onde procurar.
 *
 * @return     Retorna o numero de Vendas na Fatura.
 */
int getnumVendasFatura(Fatura *f, int filial, int mes, int tipo) {
	if (filial == 0) 
		return f->numVendas[tipo][mes - 1][0] + f->numVendas[tipo][mes - 1][1] + f->numVendas[tipo][mes - 1][2];
	return f->numVendas[tipo][mes - 1][filial - 1];
}

/**
* @brief      Função que Determina a quantidade vendida de um produto numa certa filial.
 *
 * @param      f      Estrutra Fatura.
 * @param[in]  filial filial onde procurar.
 *
 * @return     Retorna a quantidade vendida na filial.
 */
int getQuantFatura(Fatura *f, int filial) {
	if (filial == 0) 
		return f->quantPorFilial[0] + f->quantPorFilial[1] + f->quantPorFilial[2];
	return f->quantPorFilial[filial - 1];
}

/**
* @brief      Função que Determina a faturação de um produto de um certo tipo num certo mês e filial.
 *
 * @param      f      Estrutra Fatura.
 * @param[in]  filial filial onde procurar.
 * @param[in]  mes    mes onde procurar.
 * @param[in]  tipo   tipo  do produto onde procurar.
 *
 * @return     Retorna a faturação total do produto de um certo tipo num certo mês e filial.
 */
double getFaturacaoFatura(Fatura *f, int filial, int mes, int tipo) {
	if (filial == 0) 
		return f->fatTotal[tipo][mes - 1][0] + f->fatTotal[tipo][mes - 1][1] + f->fatTotal[tipo][mes - 1][2];
	return f->fatTotal[tipo][mes - 1][filial - 1];
}

/**
* @brief      Função que Determina o produto numa Fatura.
 *
 * @param      f      Estrutra Fatura.
 *
 * @return     Retorna o produto na Fatura.
 */
char *getProdutoFatura(Fatura *f) {
	return strdup(f->produto);
}

/**
 * @brief      Função que cria um clone de uma Fatura.
 *
 * @param      f     Fatura a ser colonada.
 *
 * @return     Retorna o clone.
 */
Fatura *cloneFatura(Fatura *f) {
	int i,j,k;
	Fatura *r = malloc(sizeof(Fatura));
	for (i = 0; i < 3; i++) {
		r->quantPorFilial[i] = f->quantPorFilial[i];
		for (j = 0; j < 12; j++)
			for (k = 0; k < 2; k++) {
				r->fatTotal[k][j][i] = f->fatTotal[k][j][i];
				r->numVendas[k][j][i] = f->numVendas[k][j][i];
			}
	}
	r->produto = strdup(f->produto);
	return r;
}

 /**
 * @brief      Função dá free á estruta Fatura.
 *
 * @param      f    Void pointer que vai ser casted para estrutura Fatura a dar free.
 */
void freeFatura(void *f) {
	Fatura *ff = (Fatura *)f;
	free(ff->produto);
	free(f);
}
