#include <stdlib.h>
#include <string.h>
#include "fatura.h"
#include "mytree.h"

struct fatura {
	char *produto;
	int numVendas[2][12][3]; /**<Numero de vendas de um prod organizador por Tipo,Mes e filial>*/
	double fatTotal[2][12][3]; /**<Total faturado por prod>*/
	int quantPorFilial[3];
};

Fatura * initFat(VENDA *v) {
	Fatura *f = malloc(sizeof(struct fatura));
	f->produto = getProdVenda(v);
	memset(f->numVendas, 0, 2 * 12 * 3 * sizeof(int));
	memset(f->fatTotal, 0, 2 * 12 * 3 * sizeof(double));
	memset(f->quantPorFilial, 0, 3 * sizeof(int));
	addFat(f, v);
	return f;
}

void addFat(Fatura *f, VENDA *v) {
	int mes, filial, tipo;
	mes = getMesVenda(v);
	filial = getFilialVenda(v);
	tipo = getTipoVenda(v);
	f->numVendas[tipo][mes - 1][filial - 1]++;
	f->fatTotal[tipo][mes - 1][filial - 1] += getTotalVenda(v);
	f->quantPorFilial[filial - 1] += getQuantVenda(v);
}

int comparaQuantFatura(const void *a, const void *b) {
	Fatura *aa = *(Fatura **) a;
	Fatura *bb = *(Fatura **) b;
	return getQuantFatura(bb, 0) - getQuantFatura(aa, 0);
}

int getnumVendasFatura(Fatura *f, int filial, int mes, int tipo) {
	if (filial == 0) // É 0 quando se quer de todos os filiais
		return f->numVendas[tipo][mes - 1][0] + f->numVendas[tipo][mes - 1][1] + f->numVendas[tipo][mes - 1][2];
	return f->numVendas[tipo][mes - 1][filial - 1];
}

int getQuantFatura(Fatura *f, int filial) {
	if (filial == 0) // É 0 quando se quer de todos os filiais
		return f->quantPorFilial[0] + f->quantPorFilial[1] + f->quantPorFilial[2];
	return f->quantPorFilial[filial - 1];
}

double getFaturacaoFatura(Fatura *f, int filial, int mes, int tipo) {
	if (filial == 0) // É 0 quando se quer de todos os filiais
		return f->fatTotal[tipo][mes - 1][0] + f->fatTotal[tipo][mes - 1][1] + f->fatTotal[tipo][mes - 1][2];
	return f->fatTotal[tipo][mes - 1][filial - 1];
}

char *getProdutoFatura(Fatura *f) {
	return strdup(f->produto);
}

Fatura *cloneFatura(Fatura *f) {
	Fatura *r = malloc(sizeof(Fatura));
	for (int i = 0; i < 3; i++) {
		r->quantPorFilial[i] = f->quantPorFilial[i];
		for (int j = 0; j < 12; j++)
			for (int k = 0; k < 2; k++) {
				r->fatTotal[k][j][i] = f->fatTotal[k][j][i];
				r->numVendas[k][j][i] = f->numVendas[k][j][i];
			}
	}
	r->produto = strdup(f->produto);
	return r;
}

void freeFatura(void *f) {
	Fatura *ff = (Fatura *)f;
	free(ff->produto);
	free(f);
}