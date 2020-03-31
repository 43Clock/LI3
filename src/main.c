#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mytree.h"
#include "listas.h"
#include "vendas.h"
#include "faturas.h"
#include "filial.h"
#include "view.h"
#include "sgv.h"
#include "queryInterface.h"


#define MAX 64

int main(){
	SGV *sgv = initSGV();
	
	//prodNCompradosQuery(sgv);
	clientesTodosFilQuery(sgv);
	//prodEclientesNcompQuery(sgv);
	destroySGV(sgv);
}