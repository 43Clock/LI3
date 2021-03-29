IDIR =../include
CC=gcc
CFLAGS=-O3 -ansi -D_GNU_SOURCE -Wall -g -I$(IDIR)

ODIR=obj

_DEPS = vendas.h listas.h mytree.h fatura.h faturas.h filial.h view.h interface.h queryInterface.h macros.h interpretador.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o listas.o vendas.o mytree.o fatura.o faturas.o filial.o view.o interface.o queryInterface.o interpretador.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	[ -d $(ODIR) ] || mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	doxygen Doxyfile

clean:
	rm program
	rm -rf ../docs/html
	rm -rf ../docs/latex
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
