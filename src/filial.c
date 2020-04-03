#include "filial.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct filiais {
    AVL* cliVendas[3]; /**<Avl que relaciona os clientes com todas as compras feitas por ele>*/
    AVL* prodVendas[3]; /**<Avl que contem a lista de todos os clientes que compraram um certo produto assim como o tipo da compra>*/
};


typedef struct prodCliente {
    char *prod;
    int quantidades[12];
    double fatTotal;
} ProdCliente;

typedef struct listaProds {
    LISTAS *clienteN;
    LISTAS *clienteP;
} ListaProds;

typedef struct cliVendas {
    int ocup;
    int quantidades[12];
    ProdCliente **produtos;
} CliVendas;


Filiais *initFiliais() {
    Filiais *f = malloc(sizeof(struct filiais));
    for (int i = 0; i < 3; i++) {
        f->cliVendas[i] = NULL;
        f->prodVendas[i] = NULL;
    }
    return f;
}

ListaProds * initListaProds() {
    ListaProds *r = malloc(sizeof(struct listaProds));
    r->clienteN = initLista();
    r->clienteP = initLista();
    return r;
}

ProdCliente *initProdCliente(VENDA *v) {
    ProdCliente *r = malloc(sizeof(struct prodCliente));
    r->prod = strdup(getProdVenda(v));
    memset(r->quantidades, 0, sizeof(int) * 12);
    r->quantidades[getMesVenda(v) - 1] = getQuantVenda(v);
    r->fatTotal = getTotalVenda(v);
    return r;
}

CliVendas *initCliVendas() {
    CliVendas *r = malloc(sizeof(struct cliVendas));
    memset(r->quantidades, 0, sizeof(int) * 12);
    r->produtos = NULL;
    r->ocup = 0;
    return r;
}

void updateCliVendas(CliVendas *vd, VENDA *v) {
    ProdCliente *aux = *vd->produtos;
    int flag = 0;
    vd->quantidades[getMesVenda(v) - 1] += getQuantVenda(v);
    for (int i = 0; i < vd->ocup && !flag; i++)
        if (strcmp(aux->prod, getProdVenda(v)) == 0) {
            flag = 1;
            aux->quantidades[getMesVenda(v) - 1] += getQuantVenda(v);
            aux->fatTotal += getTotalVenda(v);
        }
}

int searchProdutoLista(CliVendas *vd, char *prod) {
    ProdCliente *aux = *vd->produtos;
    int flag = 0;
    for (int i = 0; i < vd->ocup && !flag; i++)
        if (strcmp(aux->prod, prod) == 0)
            flag = 1;
    return flag;
}

void addVendaToFilial(VENDA *v, Filiais *f) {
    int filial = getFilialVenda(v) - 1;
    char *cli = getClienteVenda(v);
    char *pro = getProdVenda(v);
    int cp = searchAVL(f->cliVendas[filial], cli);
    int pd = searchAVL(f->prodVendas[filial], pro);
    int tipo = getTipoVenda(v);
    if (!cp) {
        CliVendas *a = initCliVendas();
        a->quantidades[getMesVenda(v) - 1] += getQuantVenda(v);
        ProdCliente *p = initProdCliente(v);
        a->produtos = malloc(sizeof(struct prodCliente));
        a->produtos[a->ocup++] = p;
        f->cliVendas[filial] = insert(f->cliVendas[filial], cli, a);
    }
    else {
        AVL *aux = f->cliVendas[filial];
        while (aux && strcmp(aux->key, cli) != 0) {
            if (strcmp(cli, aux->key) < 0) aux = aux->left;
            else aux = aux->right;
        }
        if (searchProdutoLista(aux->str, pro)) {
            updateCliVendas(aux->str, v);
        }
        else {
            CliVendas *a = (CliVendas *)aux->str;
            a->quantidades[getMesVenda(v) - 1] += getQuantVenda(v);
            ProdCliente *p = initProdCliente(v);
            a->produtos = realloc(a->produtos, (a->ocup + 1) * sizeof(ProdCliente *));
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
        f->prodVendas[filial] = insert(f->prodVendas[filial], pro, listas);
    }
    else {

        AVL *aux = f->prodVendas[filial];
        while (aux && strcmp(aux->key, pro) != 0) {
            if (strcmp(pro, aux->key) < 0) aux = aux->left;
            else aux = aux->right;
        }
        ListaProds *l = (ListaProds *) aux->str;
        if (tipo == 0) {
            if (l->clienteN->size == l->clienteN->ocup) reallocLista(l->clienteN);
            addLista(l->clienteN, pro);
        }
        else {
            if (l->clienteP->size == l->clienteP->ocup) reallocLista(l->clienteP);
            addLista(l->clienteP, pro);

        }
    }
    
}

int nVendaProduto(Filiais *f, int filial, char *prod) {
    AVL *aux = f->prodVendas[filial-1];
    while (aux && strcmp(aux->key, prod) != 0) {
        if (strcmp(prod, aux->key) < 0) aux = aux->left;
        else aux = aux->right;
    }
    if(aux)
        return ((ListaProds *)aux->str)->clienteN->ocup + ((ListaProds *)aux->str)->clienteP->ocup;
    else return 0;
}

int numProdNcomprados(Filiais * f, LISTAS * prod) {
    int res = 0;
    for (int i = 0; i < prod->ocup; i++) {
        int f1 = searchAVL(f->prodVendas[0], prod->listas[i]);
        int f2 = searchAVL(f->prodVendas[1], prod->listas[i]);
        int f3 = searchAVL(f->prodVendas[2], prod->listas[i]);
        if (!f1 && !f2 && !f3) {
            res++;
        }
    }
    return res;
}

int numCliNcompradores(Filiais * f, LISTAS * clientes) {
    int res = 0;
    for (int i = 0; i < clientes->ocup; i++) {
        int f1 = searchAVL(f->cliVendas[0], clientes->listas[i]);
        int f2 = searchAVL(f->cliVendas[1], clientes->listas[i]);
        int f3 = searchAVL(f->cliVendas[2], clientes->listas[i]);
        if (!f1 && !f2 && !f3) {
            res++;
        }
    }
    return res;
}

void listaProdNcomprados(Filiais * f, int filial, LISTAS * prod, LISTAS * res) {
    AVL *aux;
    if (filial == 0) { //Caso em que só queremos ver se o prod foi comprado ou não
        for (int i = 0; i < prod->ocup; i++) {
            int f1 = searchAVL(f->prodVendas[0], prod->listas[i]);
            int f2 = searchAVL(f->prodVendas[1], prod->listas[i]);
            int f3 = searchAVL(f->prodVendas[2], prod->listas[i]);
            if (!f1 && !f2 && !f3) {
                if (res->size == res->ocup) reallocLista(res);
                addLista(res, prod->listas[i]);
            }
        }
    }
    else {
        for (int i = 0; i < prod->ocup; i++) {
            int f1 = searchAVL(f->prodVendas[filial - 1], prod->listas[i]);
            if (!f1) {
                if (res->size == res->ocup) reallocLista(res);
                addLista(res, prod->listas[i]);
            }
        }
    }
}


void filialAllCheck(Filiais * f, LISTAS * res, LISTAS * clientes) {
    for (int i = 0; i < clientes->ocup; i++) {
        int f1 = searchAVL(f->cliVendas[0], clientes->listas[i]);
        int f2 = searchAVL(f->cliVendas[1], clientes->listas[i]);
        int f3 = searchAVL(f->cliVendas[2], clientes->listas[i]);
        if (f1 && f2 && f3) {
            if (res->size == res->ocup) reallocLista(res);
            addLista(res, clientes->listas[i]);
        }
    }
}

// Query 7
int nprodClienteMes (Filiais * f, char * cliente, int mes, int filial) {
    return nprodClienteMesAux(f->cliVendas[filial-1], cliente, mes); 
} 

int nprodClienteMesAux (AVL *f, char * cliente, int mes){
    CliVendas *l = (CliVendas *) f->str;
    if (f) {
        if (strcmp (f->key, cliente) == 0) {
            return l->quantidades[mes-1];
        }
        else {
            if (strcmp (f->key, cliente) > 0) return nprodClienteMesAux (f->left, cliente, mes);
            else return nprodClienteMesAux (f->right, cliente, mes);
        }
    }
    return 0; 
}

//Função para a query 5s
LISTAS *listaClientesTodosFliais(Filiais * f, LISTAS * clientes) { //Lista n ordenada é preciso dps usar o qsort no output
    LISTAS *res = initLista();
    filialAllCheck(f, res, clientes);
    return res;
}

void freeProdCli(ProdCliente *p) {
    free(p->prod);
    free(p);
}

void freeCliVendas(void *cv) {
    CliVendas *c = (CliVendas *)cv;
    for (int i = 0; i < c->ocup; i++) {
        freeProdCli(c->produtos[i]);
    }
    free(c);
}

void freeProdVendas(void *pv) {
    ListaProds *p = (ListaProds *)pv;
    freeLista(p->clienteN);
    freeLista(p->clienteP);
    free(p);
}

void freeFiliais(Filiais * f) {
    for (int i = 0; i < 3; i++) {
        freeAVL(f->cliVendas[i], freeCliVendas);
        freeAVL(f->prodVendas[i], freeProdVendas);
    }
    free(f);
}