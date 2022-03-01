CC=gcc
FLAGS=-O2 -Wall

SRCDIR=src

SRC=$(wildcard $(SRCDIR)/*.c)
EXE=dtstructs

$(EXE): $(SRC)
	$(CC) $(FLAGS) $^ -o $@

debug: FLAGS=-g -Wall
debug: $(EXE) 