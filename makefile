CC=g++
IDIR=src
CFLAGS=-I$(IDIR)

SRCS = $(wildcard *.CPP)

ODIR=.\src

_DEPS = architectures\harvard_implementation\include\dataMemory.h architectures\harvard_implementation\include\riscvInstruction.h architectures\harvard_implementation\include\rTypeInstruction.h architectures\harvard_implementation\include\processor.h architectures\harvard_implementation\include\register.h architectures\harvard_implementation\include\instructionMemory.h architectures\harvard_implementation\include\controlUnit.h architectures\harvard_implementation\include\ioPeripheral.h interface\command_line\include\commands.h
DPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o interface\command_line\commands.o architectures\harvard_implementation\dataMemory.o  architectures\harvard_implementation\riscvInstruction.o architectures\harvard_implementation\processor.o architectures\harvard_implementation\register.o architectures\harvard_implementation\instructionMemory.o architectures\harvard_implementation\controlUnit.o architectures\harvard_implementation\IoPeripheral.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGSS)

mymake: $(TEST) $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	del -f src\testing\*.o
	del -f src\architectures\harvard_implementation\*.o
	del -f src\interface\command_line\*.o
	del -f src\*.o