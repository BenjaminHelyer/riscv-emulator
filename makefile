CC=g++
IDIR=src\architectures\harvard_implementation\include
CFLAGS=-I$(IDIR)

SRCS = $(wildcard *.CPP)

ODIR=.\src

_DEPS = dataMemory.h riscvInstruction.h rTypeInstruction.h processor.h register.h instructionMemory.h controlUnit.h
DPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = testing\testbench_development_1.o architectures\harvard_implementation\dataMemory.o  architectures\harvard_implementation\riscvInstruction.o architectures\harvard_implementation\processor.o architectures\harvard_implementation\register.o architectures\harvard_implementation\instructionMemory.o architectures\harvard_implementation\controlUnit.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGSS)

mymake: $(TEST) $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	del -f src\testing\*.o
	del -f src\architectures\harvard_implementation\*.o