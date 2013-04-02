# SOURCE ###############################################################
SRC := main.c queue.c getopt.c Point.c grid.c ipqueue.c pltree.c kruskal.c 
OBJ = $(patsubst %.c,$(ODIR)/%.o,$(SRC))
DIR := $(patsubst %.c,%.dir,$(SRC))

# PROGRAMS #############################################################
CC := gcc
RM := rm -f
MKDIR := mkdir -p

# DIRECTORIES ##########################################################
BDIR := bin
ODIR := obj
VPATH := $(BDIR):queue:getopt:Point:kruskal:grid

# LINKER ###############################################################
LDLIBS := -L. 
LDFLAGS := -lm

# MONTAGEM DO PROGRAMA #################################################
conectivity: $(OBJ) | $(BDIR)
	$(CC) $^ -o $(BDIR)/$@ $(LDLIBS) $(LDFLAGS)

$(OBJ): $(ODIR) | $(DIR)

%.dir:
	@ $(MAKE) -C $* --no-print-directory

$(BDIR):
	@ echo Criando diretório de binários "$(ODIR)"
	$(MKDIR) $@

$(ODIR):
	@ echo Criando diretório de objetos "$(ODIR)"
	-$(MKDIR) $@

# OUTRAS OPÇÕES ########################################################
clean:
	$(RM) $(ODIR)/*.o
