#ifndef queryinterface_h
#define queryinterface_h 

#include "view.h"
#include "interface.h"
#include "macros.h"


SGV *escolherPathFicheirosQuery(SGV *sgv);
void prodStartedByLetterQuery(SGV *sgv);
void prodNCompradosQuery(SGV *sgv);
void clientesTodosFilQuery(SGV *sgv);
void prodEclientesNcompQuery(SGV *sgv);
void nMaisVendidosQuery(SGV *sgv);
void faturacaoAndVendasFilialQuery(SGV *sgv);
void clientesMesEFilialQuery(SGV *sgv);
void totVendaseFatIntMesQuery(SGV * sgv);
void produtoClientetipoQuery (SGV *sgv);
void prodMaisCompradosCliMesQuery(SGV * sgv);
void clientTopProfitquery (SGV *sgv);
void lastQuery (SGV *sgv);
#endif
