#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interpretador.h"
#include "interface.h"

#define MAX 64

int main(){
	SGV *sgv = initSGV();
	interpreter(sgv);
	return 0;
}