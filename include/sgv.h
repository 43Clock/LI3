#ifndef sgv_h
#define sgv_h 

#include "listas.h"
#include "vendas.h"
#include "mytree.h"
#include "sgv.h"
#include "faturas.h"
#include "filial.h"
#include "view.h"

#define MAX 64

typedef struct sgv SGV;

SGV *initSGV();
void destroySGV(SGV *sgv);



#endif