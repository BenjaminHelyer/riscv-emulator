CC=g++
IDIR=src\architectures\harvard_implementation\include
CFLAGS=-I$(IDIR)

SRCS = $(wildcard *.CPP)

ODIR=.\src

_DEPS = data.h instructions.h processor.h
DPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = testing\testbench_development_1.o architectures\harvard_implementation\data.o  architectures\harvard_implementation\instructions.o architectures\harvard_implementation\processor.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGSS)

mymake: $(TEST) $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	del -f src\testing\*.o
	del -f src\architectures\harvard_implementation\*.o