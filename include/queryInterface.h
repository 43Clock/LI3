#ifndef queryinterface_h
#define queryinterface_h 

#include "view.h"
#include "sgv.h"
#include "macros.h"
#include "listas.h"

void prodStartedByLetterQuery(SGV *sgv);
void prodNCompradosQuery(SGV *sgv);
void clientesTodosFilQuery(SGV *sgv);
void prodEclientesNcompQuery(SGV *sgv);
void nMaisVendidosQuery(SGV *sgv);
void faturacaoAndVendasFilialQuery(SGV *sgv);
void clientesMesEFilialQuery(SGV *sgv);

#endif