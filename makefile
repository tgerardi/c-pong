IDIR = include
CC = gcc
CFLAGS = -I$(IDIR)

ODIR = obj
BDIR = bin
LDIR = lib

LIBS = -lraylib -lm

_DEPS = pong.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = pong.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR) $(BDIR):
	mkdir -p $@

$(ODIR)/%.o: src/%.c $(DEPS) | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/pong: $(OBJ) | $(BDIR)
	$(CC) -o $@ $^ $(LIBS)

.PHONY: all clean install

all: $(BDIR)/pong

clean:
	rm -rf bin/ $(ODIR)/*.o $(BDIR)/* *~ core $(IDIR)/*~

install: $(BDIR)/pong
	sudo cp $(BDIR)/pong /usr/local/bin/
	sudo chmod +x /usr/local/bin/pong