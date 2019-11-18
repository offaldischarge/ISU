SRCS = PLCS.cpp
OBJ = $(SRCS:.cpp=.o)
EXE = plcs

BASEPATH=..
# Determine whether this is a debug build or not
ifdef DEBUG
CXXFLAGS=-ggdb -O0
LIBPATH=$(BASEPATH)/lib/host/debug
else
CXXFLAGS=-O2
LIBPATH=$(BASEPATH)/lib/host/release
endif
# Setup the CFLAGS to ensure that the relevant warnings, includes and defines.
CXXFLAGS+=-Wall -D_REENTRANT -DOS_LINUX -I$(BASEPATH)/inc

# Note how the flags are part of the compilation of .cpp file(s)
%.o: %.cpp
	g++ $(CXXFLAGS) -c -o $@ $^

# Then again, note how the flags are NOT part of the linking process
$(EXE): $(OBJ)
	g++ -o $(EXE) $(OBJ) -L$(LIBPATH) -lOSApi -lrt -lpthread

all: $(EXE)

clean:
	rm -f *.o $(EXE)
