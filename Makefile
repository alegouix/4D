CC=gcc
CFLAGS=-g -Wall -Werror
LD=-lSDL2 -lSDL2main -lm -lSDL2_image
BINPATH=bin
SRCPATH=src

build: $(BINPATH) $(BINPATH)/engine

run:
	make build
	./$(BINPATH)/engine

$(BINPATH):
	mkdir $(BINPATH)

$(BINPATH)/engine: $(BINPATH)/main.o
	$(CC) $(BINPATH)/*.o -o $(BINPATH)/engine ${LD}

$(BINPATH)/main.o: $(SRCPATH)/main.* $(BINPATH)/engine.o
	$(CC) -c ${CFLAGS} $(SRCPATH)/main.c -o $(BINPATH)/main.o

$(BINPATH)/engine.o: $(BINPATH)/point.o $(BINPATH)/draw.o $(BINPATH)/model.o $(BINPATH)/utils.o
	

$(BINPATH)/point.o: $(SRCPATH)/point.*
	$(CC) -c ${CFLAGS} $(SRCPATH)/point.c -o $(BINPATH)/point.o

$(BINPATH)/draw.o: $(SRCPATH)/draw.* $(BINPATH)/point.o
	$(CC) -c ${CFLAGS} $(SRCPATH)/draw.c -o $(BINPATH)/draw.o

$(BINPATH)/model.o: $(SRCPATH)/model.*
	$(CC) -c ${CFLAGS} $(SRCPATH)/model.c -o $(BINPATH)/model.o

$(BINPATH)/utils.o: $(SRCPATH)/utils.*
	$(CC) -c ${CFLAGS} $(SRCPATH)/utils.c -o $(BINPATH)/utils.o

clean:
	rm -r $(BINPATH)