/**
 * @file   filial.c
 * @brief  Funções relativas ás filiais.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "filial.h"

int mesg = 0;

struct filiais {
    AVL* cliVendas[3][26]; /**<Avl que relaciona os clientes com todas as compras feitas por ele*/
    AVL* prodVendas[3][26]; /**<Avl que contem a lista de todos os clientes que compraram um certo produto assim como o tipo da compra*/
};

typedef struct prodCliente {
    char *prod; /**<O nome de um produto que um cliente comprou.*/
    int quantidades[12];/**<Array com as quantidades de produtos vendidas separadas por mês.*/
    double fatTotal;/**<O valor da faturação gerada pelo produto para um certo cliente.*/
} ProdCliente;

typedef struct listaProds {
    LISTAS *clienteN;/**<A lista de todos os clientes que compraram um produto sem promoção.*/
    LISTAS *clienteP;/**<A lista de todos os clientes que compraram um produto em promoção.*/
} ListaProds;

typedef struct cliVendas {
    int ocup; /**<Numero de produtos diferentes que um clientes comprou.*/
    int quantidades[12];/**<Quantidades totais que um cliente comprou por mês.*/
    ProdCliente **produtos;/**<Lista dos produtos que um cliente comprou.*/
} CliVendas;


/**
 * @brief      Função de comparação das quantidades vendidas num determinado mês
 *
 * @param[in]  a     Void pointer que depos será casted para a estrutura ProdCliente.
 * @param[in]  b     Void pointer que depos será casted para a estrutura ProdCliente.
 *
 * @return     Retorna positivo caso b seja maior que a.Ordena por ordem decrescente.
 */
int comparaQuantProdCliente (const void *a, const void *b) {
    ProdCliente *aa = *(ProdCliente **) a;
    ProdCliente *bb = *(ProdCliente **) b;
    return bb->quantidades[mesg - 1] - aa->quantidades[mesg - 1];
}

/**
 * @brief      Função de comparação da faturação total entre dois produtos.
 *
 * @param[in]  a     Void pointer que depos será casted para a estrutura ProdCliente.
 * @param[in]  b     Void pointer que depos será casted para a estrutura ProdCliente.
 *
 * @return     Retorna positivo caso b seja maior que a.Ordena por ordem decrescente.
 */
int comparaFatProdCliente (const void *a, const void *b) {
    ProdCliente *aa = *(ProdCliente **) a;
    ProdCliente *bb = *(ProdCliente **) b;
    return bb->fatTotal - aa->fatTotal;
}

/**
 * @brief      Função que inicializa a estrutura de Filiais.
 *
 * @return     Retorna a estrutura inicializada com as AVL todas a NULL.
 */
Filiais *initFiliais() {
    Filiais *f = malloc(sizeof(struct filiais));
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 26; j++) {
            f->cliVendas[i][j] = NULL;
            f->prodVendas[i][j] = NULL;
        }
    return f;
}

/**
 * @brief      Função que inicializa a estrutura de ListaProds.
 *
 * @return     Retorna a estrutura inicializada com as duas listas vazias.
 */
ListaProds * initListaProds() {
    ListaProds *r = malloc(sizeof(struct listaProds));
    r->clienteN = initLista();
    r->clienteP = initLista();
    return r;
}

/**
 * @brief      Função que inicializa a estrutura ProdCliente.
 *
 * @param      v     Venda que será adicionada à estrutura.
 *
 * @return     Retorna a estrutura inicializada com as informações da venda.
 */
ProdCliente *initProdCliente(VENDA *v) {
    ProdCliente *r = malloc(sizeof(struct prodCliente));
    r->prod = getProdVenda(v);
    memset(r->quantidades, 0, sizeof(int) * 12);
    r->quantidades[getMesVenda(v) - 1] = getQuantVenda(v);
    r->fatTotal = getTotalVenda(v);
    return r;
}

/**
 * @brief      Função que inicializa a estrutura CliVendas.
 *
 * @return     Retorna a estrutura inicializada.
 */
CliVendas *initCliVendas() {
    CliVendas *r = malloc(sizeof(struct cliVendas));
    memset(r->quantidades, 0, sizeof(int) * 12);
    r->produtos = NULL;
    r->ocup = 0;
    return r;
}

/**
 * @brief      Função que atualiza a estrutura de CliVendas caso um produto já se encontre na lista.
 *
 * @param      vd    Estrutura CliVendas que vai ser atualizada.
 * @param      v     Estrutura de Venda com as informações de uma linha de venda.
 */
void updateCliVendas(CliVendas *vd, VENDA *v) {
    ProdCliente *aux = *vd->produtos;
    int flag = 0, i;
    char *prod = getProdVenda(v);
    vd->quantidades[getMesVenda(v) - 1] += getQuantVenda(v);
    for (i = 0; i < vd->ocup && !flag; i++)
        if (strcmp(aux->prod, prod) == 0) {
            flag = 1;
            aux->quantidades[getMesVenda(v) - 1] += getQuantVenda(v);
            aux->fatTotal += getTotalVenda(v);
        }
    free(prod);
}

/**
 * @brief      Função que verifica se um produto já se encontra na estrutura CliVendas.
 *
 * @param      vd    Estrutura CliVendas que vai ser analisada.
 * @param      prod  Produto a procurar na estrutura CliVendas.
 *
 * @return     Retorna 1 se encontra o produto,0 se não encontrar.
 */
int searchProdutoLista(CliVendas *vd, char *prod) {
    ProdCliente *aux = *vd->produtos;
    int flag = 0, i;
    for (i = 0; i < vd->ocup && !flag; i++)
        if (strcmp(aux->prod, prod) == 0)
            flag = 1;
    return flag;
}

/**
 * @brief      Adiciona uma estrutura ProdCliente na estrutura CliVendas.
 *
 * @param      v     Estrutura CliVendas que vai ser atualizada.
 * @param      p     Estrutura ProdCliente que vai ser adicionada à Clivendas
 */
void addProdVendaToCliVenda(CliVendas *v, ProdCliente *p) {
    int i;
    if (!searchProdutoLista(v, p->prod) && p->quantidades[mesg - 1]) {
        v->produtos[v->ocup++] = p;
    }
    else {
        for (i = 0; i < v->ocup; i++)
            if (strcmp(v->produtos[i]->prod, p->prod) == 0 && p->quantidades[mesg - 1])
                v->produtos[i]->quantidades[mesg - 1] += p->quantidades[mesg - 1];
    }
}

/**
 * @brief      Função que insere a informação de uma venda na sua respetiva AVL.
 *
 * @param      v     Venda que vai ser adicionada.
 * @param      f     Estrutura Filiais que vai ser atualizada.
 */
void addVendaToFilial(VENDA *v, Filiais *f) {
    int filial = getFilialVenda(v) - 1;
    char *cli = getClienteVenda(v);
    char *pro = getProdVenda(v);
    AVL *cp = searchAVLr(f->cliVendas[filial][cli[0] - 'A'], cli);
    AVL *pd = searchAVLr(f->prodVendas[filial][pro[0] - 'A'], pro);
    int tipo = getTipoVenda(v);
    if (!cp) {
        CliVendas *a = initCliVendas();
        a->quantidades[getMesVenda(v) - 1] += getQuantVenda(v);
        ProdCliente *p = initProdCliente(v);
        a->produtos = malloc(sizeof(struct prodCliente));
        a->produtos[a->ocup++] = p;
        f->cliVendas[filial][cli[0] - 'A'] = insert(f->cliVendas[filial][cli[0] - 'A'], strdup(cli), a);
    }
    else {
        AVL *aux = cp;
        if (searchProdutoLista(getStr(aux), pro)) {
            updateCliVendas(getStr(aux), v);
        }
        else {
            CliVendas *a = (CliVendas *)getStr(aux);
            a->quantidades[getMesVenda(v) - 1] += getQuantVenda(v);
            ProdCliente *p = initProdCliente(v);
            ProdCliente **tmp = realloc(a->produtos, (a->ocup + 1) * sizeof*tmp);
            a->produtos = tmp;
            a->produtos[a->ocup++] = p;
        }
    }
    if (!pd) {
        ListaProds *listas = initListaProds();
        if (tipo == 0) {
            addLista(listas->clienteN, cli);
        }
        else {
            addLista(listas->clienteP, cli);
        }
        f->prodVendas[filial][pro[0] - 'A'] = insert(f->prodVendas[filial][pro[0] - 'A'], strdup(pro), listas);
    }
    else {
        AVL *aux = pd;
        ListaProds *l = (ListaProds *) getStr(aux);
        if (tipo == 0) {
            if (getSize(l->clienteN) == getOcupados(l->clienteN)) reallocLista(l->clienteN);
            addLista(l->clienteN, cli);
        }
        else {
            if (getSize(l->clienteP) == getOcupados(l->clienteP)) reallocLista(l->clienteP);
            addLista(l->clienteP, cli);

        }
    }
    free(cli);
    free(pro);
}

/**
 * @brief      Função que calcula o número de clientes que compraram um determinado produto num filial.
 *
 * @param      f       Estrutura Filiais.
 * @param[in]  filial  Filial a procurar.
 * @param      prod    O produto que se quer procurar.
 *
 * @return     Retorna a quantidade de clientes.
 */
int nVendaProduto(Filiais *f, int filial, char *prod) {
    AVL *aux = f->prodVendas[filial - 1][prod[0] - 'A'];
    while (aux && strcmp(getKey(aux), prod) != 0) {
        if (strcmp(prod, getKey(aux)) < 0) aux = getLeft(aux);
        else aux = getRight(aux);
    }
    if (aux)
        return getOcupados(((ListaProds *)getStr(aux))->clienteN) + getOcupados(((ListaProds *)getStr(aux))->clienteP);
    else return 0;
}

/**
 * @brief      Função que calcula o número de produtos nunca comprados em nenhuma filial.
 *
 * @param      f     Estrutura Filiais.
 * @param      prod  A lista com todos os produtos válidos
 *
 * @return     Retorna o número de produtos nunca comprados em nenhuma filial.
 */
int numProdNcomprados(Filiais * f, LISTAS * prod) {
    int res = 0, i;
    char *pro;
    for (i = 0; i < getOcupados(prod); i++) {
        pro = getIndex(prod, i);
        int f1 = searchAVL(f->prodVendas[0][pro[0] - 'A'], pro);
        int f2 = searchAVL(f->prodVendas[1][pro[0] - 'A'], pro);
        int f3 = searchAVL(f->prodVendas[2][pro[0] - 'A'], pro);
        if (!f1 && !f2 && !f3) {
            res++;
        }
    }
    return res;
}

/**
 * @brief      Função que calcula o número de clientes que não compraram nada
 *
 * @param      f         Estrutura Filiais.
 * @param      clientes  A lista com todos os produtos validos.
 *
 * @return     Retorna o número de clientes que não compraram nada.
 */
int numCliNcompradores(Filiais * f, LISTAS * clientes) {
    int res = 0, i;
    char *cliente;
    for (i = 0; i < getOcupados(clientes); i++) {
        cliente = getIndex(clientes, i);
        int f1 = searchAVL(f->cliVendas[0][cliente[0] - 'A'], cliente);
        int f2 = searchAVL(f->cliVendas[1][cliente[0] - 'A'], cliente);
        int f3 = searchAVL(f->cliVendas[2][cliente[0] - 'A'], cliente);
        if (!f1 && !f2 && !f3) {
            res++;
        }
    }
    return res;
}

/**
 * @brief      Função que cria uma lista com os produtos não comprados numa filial.
 *
 * @param      f       Estrutura Filiais.
 * @param[in]  filial  Filial é suposto analisar.Caso de ser 0 é para todas em filiais.
 * @param      prod    A lista com todos os produtos válidos.
 * @param      res     A lista que vais ser criada com os produtos não comprados numa filial.
 */
void listaProdNcomprados(Filiais * f, int filial, LISTAS * prod, LISTAS * res) {
    int i;
    char *pro;
    if (filial == 0) {
        for (i = 0; i < getOcupados(prod); i++) {
            pro = getIndex(prod, i);
            int f1 = searchAVL(f->prodVendas[0][pro[0] - 'A'], pro);
            int f2 = searchAVL(f->prodVendas[1][pro[0] - 'A'], pro);
            int f3 = searchAVL(f->prodVendas[2][pro[0] - 'A'], pro);
            if (!f1 && !f2 && !f3) {
                if (getSize(res) == getOcupados(res)) reallocLista(res);
                addLista(res, pro);
            }
        }
    }
    else {
        for (i = 0; i < getOcupados(prod); i++) {
            pro = getIndex(prod, i);
            int f1 = searchAVL(f->prodVendas[filial - 1][pro[0] - 'A'], pro);
            if (!f1) {
                if (getSize(res) == getOcupados(res)) reallocLista(res);
                addLista(res, pro);
            }
        }
    }
}

/**
 * @brief      Função auxiliar da @ref listaClientesTodosFliais.
 *
 * @param      f         Estrutura Filiais.
 * @param      res       A lista de todos os clientes válidos.
 * @param      clientes  Lista que é criada como os clientes que compraram em todos os filiais.
 */
void filialAllCheck(Filiais * f, LISTAS * res, LISTAS * clientes) {
    int i;
    char *cliente;
    for (i = 0; i < getOcupados(clientes); i++) {
        cliente = getIndex(clientes, i);
        int f1 = searchAVL(f->cliVendas[0][cliente[0] - 'A'], cliente);
        int f2 = searchAVL(f->cliVendas[1][cliente[0] - 'A'], cliente);
        int f3 = searchAVL(f->cliVendas[2][cliente[0] - 'A'], cliente);
        if (f1 && f2 && f3) {
            if (getSize(res) == getOcupados(res)) reallocLista(res);
            addLista(res, cliente);
        }
    }
}

/**
 * @brief      Função que calcula a quantidade comprada por um cliente num determinado mês e filial.
 *
 * @param      f        Estrutura Filiais.
 * @param      cliente  O cliente a procurar.
 * @param[in]  mes      O mês a procurar
 * @param[in]  filial   A filial a procurar
 *
 * @return     Retorna a quantidade comprada por um cliente.
 */
int nprodClienteMes (Filiais * f, char * cliente, int mes, int filial) {
    return nprodClienteMesAux(f->cliVendas[filial - 1][cliente[0] - 'A'], cliente, mes);
}

/**
 * @brief      Função auxiliar da @ref nprodClienteMes.
 *
 * @param      f        AVL de cliVendas de uma certa filial.
 * @param      cliente  O cliente a procurar.
 * @param[in]  mes      O mes a procurar.
 *
 * @return     Retorna a quantidade comprada por um cliente.
 */
int nprodClienteMesAux (AVL *f, char * cliente, int mes) {
    CliVendas *l = (CliVendas *) getStr(f);
    if (f) {
        if (strcmp (getKey(f), cliente) == 0) {
            return l->quantidades[mes - 1];
        }
        else {
            if (strcmp (getKey(f), cliente) > 0) return nprodClienteMesAux (getLeft(f), cliente, mes);
            else return nprodClienteMesAux (getRight(f), cliente, mes);
        }
    }
    return 0;
}

/**
 * @brief      Função que devolva a lista de todos os clientes que compraram um produto sem ser em promoção
 *
 * @param      f       Estrutura Filiais.
 * @param      prod    O produto que se quer procurar.
 * @param[in]  filial  A filial que se quer procurar.
 *
 * @return     Retorna a lista de clientes que compraram um produto não em promoção.
 */
LISTAS  *lClienteProdFilialN (Filiais * f, char *prod, int filial) {
    return lClienteProdFilialNAux (f->prodVendas[filial - 1][prod[0] - 'A'], prod);
}

/**
 * @brief      Função auxiliar da @ref lClienteProdFilialN
 *
 * @param      f     AVL de ProdCli de uma certa filial.
 * @param      prod  O produto a procurar.
 *
 * @return     Retorna a lista de clientes que compraram um produto não em promoção.
 */
LISTAS *lClienteProdFilialNAux  (AVL *f , char *prod) {
    ListaProds *l = (ListaProds *) getStr(f);
    if (f) {
        if (strcmp (getKey(f), prod) == 0) {
            return l->clienteN;
        }
        else {
            if (strcmp (getKey(f), prod) > 0) return lClienteProdFilialNAux  (getLeft(f), prod);
            else return lClienteProdFilialNAux (getRight(f), prod);
        }
    }
    return NULL;
}

/**
 * @brief      Função que devolva a lista de todos os clientes que compraram um produto em promoção
 *
 * @param      f       Estrutura Filiais.
 * @param      prod    O produto que se quer procurar.
 * @param[in]  filial  A filial que se quer procurar.
 *
 * @return     Retorna a lista de clientes que compraram um produto em promoção.
 */
LISTAS  *lClienteProdFilialP (Filiais * f, char *prod, int filial) {
    return lClienteProdFilialPAux (f->prodVendas[filial - 1][prod[0] - 'A'], prod);
}


/**
 * @brief      Função auxiliar da @ref lClienteProdFilialP
 *
 * @param      f     AVL de ProdCli de uma certa filial.
 * @param      prod  O produto a procurar.
 *
 * @return     Retorna a lista de clientes que compraram um produto em promoção.
 */
LISTAS *lClienteProdFilialPAux  (AVL *f , char *prod) {
    ListaProds *l = (ListaProds *) getStr(f);
    if (f) {
        if (strcmp (getKey(f), prod) == 0) {
            return l->clienteP;
        }
        else {
            if (strcmp (getKey(f), prod) > 0) return lClienteProdFilialPAux  (getLeft(f), prod);
            else return lClienteProdFilialPAux (getRight(f), prod);
        }
    }
    return NULL;
}

/**
 * @brief      Função que cria uma lista dos clientes que compraram em todas as filiais.
 *
 * @param      f         Estrutura Filiais.
 * @param      clientes  A lista de todos os clientes válidos.
 *
 * @return     Retorna a lista de todos os clientes que compraram em todas as filiais.
 */
LISTAS *listaClientesTodosFliais(Filiais * f, LISTAS * clientes) {
    LISTAS *res = initLista();
    filialAllCheck(f, res, clientes);
    return res;
}

/**
 * @brief      Função que dá free à estrutura ProdCli.
 *
 * @param      p     Estrutura ProdCli a dar free.
 */
void freeProdCli(ProdCliente *p) {
    free(p->prod);
    free(p);
}

/**
 * @brief      Função que dá free à estrutura CliVendas.
 *
 * @param      cv    Void pointer que vai ser casted para estrutura CliVendas a dar free.
 */
void freeCliVendas(void *cv) {
    CliVendas *c = (CliVendas *)cv;
    int i;
    for (i = 0; i < c->ocup; i++) {
        freeProdCli(c->produtos[i]);
    }
    free(c->produtos);
    free(c);
}

/**
 * @brief      Função que dá free à estrutura ProdVendas.
 *
 * @param      pv    Void pointer que vai ser casted para estrutura ProdVendas a dar free.
 */
void freeProdVendas(void *pv) {
    ListaProds *p = (ListaProds *)pv;
    freeLista(p->clienteN);
    freeLista(p->clienteP);
    free(p);
}

/**
 * @brief      Função que dá free à estrutura Filiais.
 *
 * @param      f     Estrutura Filiais a dar free.
 */
void freeFiliais(Filiais * f) {
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 26; j++) {
            freeAVL(f->cliVendas[i][j], freeCliVendas);
            freeAVL(f->prodVendas[i][j], freeProdVendas);
        }
    free(f);
}

/**
 * @brief      Função que cria um clone de um ProdCliente.
 *
 * @param      a     ProdCliente a ser colonado.
 *
 * @return     Retorna o clone.
 */
ProdCliente *cloneProdCliente(ProdCliente *a) {
    int i;
    ProdCliente *aux = malloc(sizeof(ProdCliente));
    for (i = 0; i < 12; i++) {
        aux->quantidades[i] = a->quantidades[i];
    }
    aux->prod = strdup(a->prod);
    aux->fatTotal = a->fatTotal;
    return aux;
}

/**
 * @brief      Função que retorna a lista ordenada dos produtos mais comprados por um cliente.
 *
 * @param      f        Estrutura Filiais.
 * @param      cliente  Cliente a procurar.
 * @param[in]  mes      Mês a procurar.
 *
 * @return     Retorna uma estrutura CliVendas ordenada com os produtos mais comprados por um cliente.
 */
CliVendas *clientFavouriteProducts (Filiais *f, char *cliente, int mes) {
    CliVendas *res = initCliVendas();
    mesg = mes;
    AVL *a1 = f->cliVendas[0][cliente[0] - 'A'], *a2 = f->cliVendas[1][cliente[0] - 'A'], *a3 = f->cliVendas[2][cliente[0] - 'A'];
    while (a1 && strcmp(getKey(a1), cliente) != 0) {
        if (strcmp(cliente, getKey(a1)) < 0) a1 = getLeft(a1);
        else a1 = getRight(a1);
    }
    while (a2 && strcmp(getKey(a2), cliente) != 0) {
        if (strcmp(cliente, getKey(a2)) < 0) a2 = getLeft(a2);
        else a2 = getRight(a2);
    }
    while (a3 && strcmp(getKey(a3), cliente) != 0) {
        if (strcmp(cliente, getKey(a3)) < 0) a3 = getLeft(a3);
        else a3 = getRight(a3);
    }
    int size1, size2, size3, size, i, total = 0;;
    size1 = (a1) ? ((CliVendas *)getStr(a1))->ocup : 0;
    size2 = (a2) ? ((CliVendas *)getStr(a2))->ocup : 0;
    size3 = (a3) ? ((CliVendas *)getStr(a3))->ocup : 0;
    size = size1 + size2 + size3;
    res->produtos = malloc(size * sizeof(ProdCliente *));
    for (i = 0; i < size1; i++, total++) {
        addProdVendaToCliVenda(res, ((CliVendas *)getStr(a1))->produtos[i]);
    }
    for (i = 0; i < size2; i++, total++) {
        addProdVendaToCliVenda(res, ((CliVendas *)getStr(a2))->produtos[i]);
    }
    for (i = 0; i < size3; i++, total++) {
        addProdVendaToCliVenda(res, ((CliVendas *)getStr(a3))->produtos[i]);
    }
    qsort(res->produtos, res->ocup, sizeof(ProdCliente *), comparaQuantProdCliente);
    
    return res;
}

/**
 * @brief      Função auxiliar da @ref clientTopProfit.
 */
void addProdVendaToCliVenda2 (CliVendas *v, ProdCliente *p) {
    int i;
    if (!searchProdutoLista(v, p->prod)) {
        v->produtos[v->ocup++] = p;
    }
    else {
        for (i = 0; i < v->ocup; i++)
            if (strcmp(v->produtos[i]->prod, p->prod) == 0)
                v->produtos[i]->fatTotal += p->fatTotal;
    }
}

/**
 * @brief      Função que retorna a lista ordenada dos produtos em que foram gastados mais dinheiro por um cliente.
 *
 * @param      f        Estrutura Filiais.
 * @param      cliente  Cliente a procurar.
 * @param[in]  n        Mês a procurar.
 *
 * @return     Retorna uma estrutura CliVendas com a lista ordenada dos produtos em que um cliente gastou mais dinheiro.
 */
CliVendas *clientTopProfit (Filiais *f, char *cliente, int n) {
    CliVendas *res = initCliVendas();
    AVL *a1 = f->cliVendas[0][cliente[0] - 'A'], *a2 = f->cliVendas[1][cliente[0] - 'A'], *a3 = f->cliVendas[2][cliente[0] - 'A'];
    while (a1 && strcmp(getKey(a1), cliente) != 0) {
        if (strcmp(cliente, getKey(a1)) < 0) a1 = getLeft(a1);
        else a1 = getRight(a1);
    }
    while (a2 && strcmp(getKey(a2), cliente) != 0) {
        if (strcmp(cliente, getKey(a2)) < 0) a2 = getLeft(a2);
        else a2 = getRight(a2);
    }
    while (a3 && strcmp(getKey(a3), cliente) != 0) {
        if (strcmp(cliente, getKey(a3)) < 0) a3 = getLeft(a3);
        else a3 = getRight(a3);
    }
    int size1, size2, size3, size, i, total = 0;;
    size1 = (a1) ? ((CliVendas *)getStr(a1))->ocup : 0;
    size2 = (a2) ? ((CliVendas *)getStr(a2))->ocup : 0;
    size3 = (a3) ? ((CliVendas *)getStr(a3))->ocup : 0;
    size = size1 + size2 + size3;
    res->produtos = malloc(size * sizeof(ProdCliente *));
    for (i = 0; i < size1; i++, total++) {
        addProdVendaToCliVenda2(res, cloneProdCliente(((CliVendas *)getStr(a1))->produtos[i]));
    }
    for (i = 0; i < size2; i++, total++) {
        addProdVendaToCliVenda2(res, cloneProdCliente(((CliVendas *)getStr(a2))->produtos[i]));
    }
    for (i = 0; i < size3; i++, total++) {
        addProdVendaToCliVenda2(res, cloneProdCliente(((CliVendas *)getStr(a3))->produtos[i]));
    }
    qsort(res->produtos, res->ocup, sizeof(ProdCliente *), comparaFatProdCliente);
    for (i = n; i < size; i++) {
        freeProdCli(res->produtos[i]);
    }
    if (res->ocup > n) res->ocup = n;
    return res;
}


int getClienteVendaOcup(CliVendas *c) {
    return c->ocup;
}

char *getProdAtInxdexCliVenda(CliVendas *c, int index) {
    return c->produtos[index]->prod;
}

int getQuantAtIndexMesCliVenda(CliVendas *c, int index, int mes) {
    return c->produtos[index]->quantidades[mes - 1];
}

double getFatAtIndexCliVenda(CliVendas *c, int index) {
    return c->produtos[index]->fatTotal;
}

ProdCliente **getProdCliente(CliVendas *c){
    return c->produtos;
}