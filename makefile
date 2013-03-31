# SOURCE ###############################################################
SRC := main.c queue.c getopt.c Point.c
OBJ = $(patsubst %.c,$(ODIR)/%.o,$(SRC))
DIR := $(patsubst %.c,%.dir,$(SRC))

# PROGRAMS #############################################################
CC := gcc
RM := rm -f
MKDIR := mkdir -p

# DIRECTORIES ##########################################################
VPATH := queue:getopt:Point
BDIR := bin
ODIR := obj

# LINKER ###############################################################
LDLIBS := -L. 
LDFLAGS := -lm

# MONTAGEM DO PROGRAMA #################################################
conectivity: $(OBJ) | $(DIR) $(ODIR) $(BDIR)
	$(CC) $^ -o $(BDIR)/$@ $(LDLIBS) $(LDFLAGS)

%.dir:
	@ $(MAKE) -C $* --no-print-directory

$(BDIR):
	@ echo Criando diretório de binários "$(ODIR)"
	$(MKDIR) $@

$(ODIR):
	@ echo Criando diretório de objetos "$(ODIR)"
	$(MKDIR) $@

# OUTRAS OPÇÕES ########################################################
clean:
	$(RM) $(ODIR)/*.o
