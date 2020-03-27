#define MAX 32


typedef struct lista{
    char str[MAX];
}LISTA;

typedef struct listas{
    int size;
    int ocup;
    char **listas;
}LISTAS;

typedef struct venda{
    char *a;
    float b;
    int c;
    char d;
    char *e;
    int f;
    int g;
}VENDA;

typedef struct vendas{
    int size;
    int ocup;
    VENDA *vendas;
}VENDAS;

int checkClientes(char *test);
int checkProdutos(char *test);
void initVendas(VENDAS *vendas);
void reallocVendas(VENDAS *vendas);
void reallocLista(LISTAS *lista);
void initLista(LISTAS *lista);
void addLista(LISTAS *lista,char *str);
void filterStr(char *str);
void sort(char **lista,int n,int b);
void sort2(char **lista,int n);