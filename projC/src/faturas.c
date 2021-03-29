  
/**
 * @file   faturas.c
 * @brief  Funções relativas ás faturas.
 */

#include "faturas.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct faturas {
    double totalFatMes[12]; /**<Total faturado organizado por mês*/
    int totalVendasMes[12]; /**<Total vendid organizado por mês*/
    AVL *avlF; /**<Avl de faturas, em que a key é um produto*/
};

/**
 * @brief      Função que inicializa a estrutura Faturas.
 *
 * @return     Retorna a estrutura inicializada com as duas listas vazias e AVL a NULL.
 */
Faturas * initFaturas() {
    Faturas *temp = malloc(sizeof(struct faturas));
    memset(temp->totalFatMes, 0, 12 * sizeof(double));
    memset(temp->totalVendasMes, 0, 12 * sizeof(int));
    temp->avlF = NULL;
    return temp;
}

/**
 * @brief      Adiciona uma estrutura VENDA na estrutura Faturas.
 *
 * @param      f     Estrutura Faturas que vai ser atualizada.
 * @param      v     Estrutura VENDA que vai ser adicionada à Faturas.
 */
void addVendaToFaturas(Faturas *f, VENDA *v) {
    AVL *aux = f->avlF;
    char * produto = getProdVenda(v);
    while (aux && strcmp(getKey(aux), produto) != 0) {
        if (strcmp(produto, getKey(aux)) < 0) aux = getLeft(aux);
        else aux = getRight(aux);
    }
    if (aux == NULL) {
        Fatura *fat = initFat(v);
        f->avlF = insert(f->avlF, strdup(produto), fat);
    }
    else {
        addFat(getStr(aux), v);
    }
    f->totalFatMes[getMesVenda(v) - 1] += getQuantVenda(v) * getPrecoVenda(v);
    f->totalVendasMes[getMesVenda(v) - 1] ++;
    free(produto);
}

/**
 * @brief      Calcula a faturação de um mês.
 *
 * @param      f     AVL de Fatura.
 * @param[in]  mes   mês onde procurar.
 *
 * @return     Retorna a faturação total de um mês.
 */
double calculaFatMes(AVL *f, int mes) {
    double r = 0;
    if (f) {
        r += getFaturacaoFatura(getStr(f), 0, mes + 1, 0) + getFaturacaoFatura(getStr(f), 0, mes + 1, 1);
        r += calculaFatMes(getRight(f), mes) + calculaFatMes(getLeft(f), mes);
        return r;
    }
    return 0;
}

/**
 * @brief      Calcula o número de vendas de um mês.
 *
 * @param      f     AVL de Fatura.
 * @param[in]  mes   mês onde procurar.
 *
 * @return     Retorna o número total vendas de um mês.
 */
int calculaVendasMes(AVL *f, int mes) {
    int r = 0;
    if (f) {
        r += getnumVendasFatura(getStr(f), 0, mes + 1, 0) + getnumVendasFatura(getStr(f), 0, mes + 1, 1);
        r += calculaVendasMes(getRight(f), mes) + calculaVendasMes(getLeft(f), mes);
        return r;
    }
    return 0;
}

/**
 * @brief      Inicializa os arrays do total faturado por mês e do total de vendas por mês.
 *
 * @param      f     Estrutura Faturas.
 */
void calculaValoresFaturas(Faturas *f) {
    int i;
    for (i = 0; i < 12; i++) {
        f->totalFatMes[i] = calculaFatMes(f->avlF, i);
        f->totalVendasMes[i] = calculaVendasMes(f->avlF, i);
    }
}

/**
 * @brief      Calcula a faturação do ano inteiro.
 *
 * @param      f     Estrutura Faturas.
 *
 * @return     Retorna a faturação total do ano.
 */
double calculaTotalFaturado(Faturas *f) {
    int i;
    double r = 0;
    for (i = 0; i < 12; i++)
        r += f->totalFatMes[i];
    return r;
}

/**
 * @brief      Calcula o número de vendas do ano inteiro.
 *
 * @param      f     Estrutura Faturas.
 *
 * @return     Retorna o número total de vendas do ano.
 */
int calculaTotalVendido(Faturas *f) {
    int r = 0,i;
    for (i = 0; i < 12; i++)
        r += f->totalVendasMes[i];
    return r;
}

/**
 * @brief      Determina a Fatura que contém um certo produto.
 *
 * @param      f         Estrutura Faturas.
 * @param      produto   O produto que se quer procurar.
 *
 * @return     Retorna a Farura que contém o produto.
 */
Fatura *getFatura(Faturas *f, char *produto) {
    AVL *aux = f->avlF;
    while (aux && strcmp(getKey(aux), produto) != 0) {
        if (strcmp(produto, getKey(aux)) < 0) aux = getLeft(aux);
        else aux = getRight(aux);
    }
    return getStr(aux);
}

/**
 * @brief      Dá free á estrutura Faturas.
 *
 * @param      f     Estrutura Faturas á qual queremos dar free.
 */
void freeFaturas(Faturas *f) {
    freeAVL(f->avlF, freeFatura);
    free(f);
}


/**
 * @brief      Calcula o número de vendas de uma Fatura.
 *
 * @param      f        AVL de Fatura.
 * @param[in]  mes      O mês a procurar.
 * @param[in]  tipo     O tipo a procurar.
 * @param[in]  filial   A filial a procurar.
 *
 * @return     Retorna o número de vendas.
 */
int getSalesMes(AVL *f, int mes, int tipo,int filial) {
    int r = 0;
    if (f) {
        if(filial == 0)
            r += getnumVendasFatura(getStr(f), 0, mes, tipo);
        else
            r += getnumVendasFatura(getStr(f), filial, mes, tipo);
        return r;
    }
    return 0;
}

/**
 * @brief      Função auxiliar da @ref getProductSales.
 *
 * @param      f        AVL de Fatura.
 * @param      prod     O produto a procurar.
 * @param[in]  mes      O mês a procurar.
 * @param[in]  tipo     O tipo a procurar.
 * @param[in]  filial   A filial a procurar.
 *
 * @return     Retorna o número de vendas.
 */
int getProductSalesaux (AVL *f, char *prod, int mes, int tipo,int filial) {
    if (f == NULL) return 0;
    if (strcmp(getKey(f), prod) == 0) return getSalesMes(f, mes, tipo,filial);
    else if (strcmp(getKey(f), prod) < 0) return getProductSalesaux(getRight(f), prod, mes, tipo,filial);
    else return getProductSalesaux(getLeft(f), prod, mes, tipo,filial);
}

/**
 * @brief      Função que calcula o número de vendas de um produto com um certo tipo num certo mês e filial.
 *
 * @param      f        Estrutura Faturas.
 * @param      prod     O produto a procurar.
 * @param[in]  mes      O mês a procurar.
 * @param[in]  tipo     O tipo a procurar.
 * @param[in]  filial   A filial a procurar.
 *
 * @return     Retorna o número de vendas.
 */
int getProductSales(Faturas *f, char *prod, int mes, int tipo,int filial) {
    AVL *aux = f->avlF;
    return getProductSalesaux(aux, prod, mes, tipo,filial);
}


/**
 * @brief      Calcula a faturação total de uma Fatura.
 *
 * @param      f        AVL de Fatura.
 * @param[in]  mes      O mês a procurar.
 * @param[in]  tipo     O tipo a procurar.
 * @param[in]  filial   A filial a procurar.
 *
 * @return     Retorna a faturação total.
 */
double getProfitMes(AVL *f, int mes, int tipo, int filial) {
    double r = 0;
    if (f) {
        if (filial == 0)
            r += getFaturacaoFatura(getStr(f), 0, mes, tipo);
        else
            r += getFaturacaoFatura(getStr(f), filial, mes, tipo);
        return r;
    }
    return 0;
}

/**
 * @brief      Função auxiliar da @ref getProductProfit.
 *
 * @param      f        AVL de Fatura.
 * @param      prod     O produto a procurar.
 * @param[in]  mes      O mês a procurar.
 * @param[in]  tipo     O tipo a procurar.
 * @param[in]  filial   A filial a procurar.
 *
 * @return     Retorna a faturação total.
 */
double getProductProfitaux (AVL *f, char *prod, int mes, int tipo, int filial) {
    if (f == NULL) return 0;
    if (strcmp(getKey(f), prod) == 0) return getProfitMes(f, mes, tipo, filial);
    else if (strcmp(getKey(f), prod) < 0) return getProductProfitaux(getRight(f), prod, mes, tipo, filial);
    else return getProductProfitaux(getLeft(f), prod, mes, tipo, filial);
}

/**
 * @brief      Função que calcula a faturação total de um produto com um certo tipo num certo mês e filial.
 *
 * @param      f        Estrutura Faturas.
 * @param      prod     O produto a procurar.
 * @param[in]  mes      O mês a procurar.
 * @param[in]  tipo     O tipo a procurar.
 * @param[in]  filial   A filial a procurar.
 *
 * @return     Retorna a faturação total.
 */
double getProductProfit(Faturas *f, char *prod, int mes, int tipo, int filial) {
    AVL *aux = f->avlF;
    return getProductProfitaux(aux, prod, mes, tipo, filial);
}


/**
 * @brief      Função que calcula o numero de Faturas.
 *
 * @param      f        Estrutura Faturas.
 *
 * @return     Retorna o número de Faturas.
 */
int numeroNodosAux (Faturas *f) {
    return numNodos(f->avlF);
}

/**
 * @brief      Função que insere todas as Fatura de Uma AVL num array.
 *
 * @param      f        AVL de Fatura.
 * @param      array    Array de Fatura onde vamos inserir as Faturas.
 * @param[in]  n        Posição onde vamos inserir uma Fatura.
 *
 * @return     Retorna o array de Fatura.
 */
Fatura **getAllFat(AVL *f, Fatura **array, int *n) {
    if (f) {
        array[*n] = cloneFatura((Fatura *)getStr(f));
        *n = *n + 1;
        array = getAllFat(getLeft(f), array, n);
        array = getAllFat(getRight(f), array, n);
    }
    return array;
}

/**
 * @brief      Função que insere as N Fatura dos N produtos mais vendidos num array.
 *
 * @param      f        Estrutura Faturas.
 * @param[in]  n        Numero de Produtos que queremos inserir.
 *
 * @return     Retorna o array com as N Fatura dos N produtos mais vendidos.
 */
Fatura **getNMaisVendidos(Faturas *f, int n) {
    int size = numNodos(f->avlF);
    int a = 0,i;
    Fatura ** array = malloc(size * sizeof(Fatura *));
    array = getAllFat(f->avlF, array, &a);
    qsort(array, size, sizeof(Fatura *), comparaQuantFatura);
    for (i = n; i < size; i++) {
        freeFatura(array[i]);
    }
    return array;
}

/**
 * @brief      Função que determina o número total de vendas num intervalo de meses.
 *
 * @param      f        Estrutura Faturas.
 * @param[in]  mes1     O primeiro mês do intervalo.
 * @param[in]  mes2     O segundo mês do intervalo.
 *
 * @return     Retorna o número total de vendas num intervalo de meses.
 */
int totalVendasIntMes (Faturas *f, int mes1, int mes2) {
    int i;
    int res = 0;
    if (mes1 <= 0 || mes2 > 12) return 0;
    for (i = mes1 -1; i < mes2 ; i++) {
        res += f->totalVendasMes[i];
    }
    return res;
}

/**
 * @brief      Função que determina a faturação total num intervalo de meses.
 *
 * @param      f        Estrutura Faturas.
 * @param[in]  mes1     O primeiro mês do intervalo.
 * @param[in]  mes2     O segundo mês do intervalo.
 *
 * @return     Retorna a faturação total num intervalo de meses.
 */
double totalFaturacaoIntMes (Faturas *f, int mes1, int mes2) {
    int i;
    double res = 0;
    if (mes1 <= 0 || mes2 > 12) return 0;
    for (i = mes1 - 1 ; i < mes2; i++) {
        res += f->totalFatMes[i];
    }
    return res;
}
