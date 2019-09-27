SRC = main.cpp part1.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = parts
CXX = g++
LIB = libpart2.a
TARGETS = all parts part1.o clean help

.PHONY: all
all: $(EXEC)
$(EXEC): $(OBJ) $(LIB)
	$(CXX) -o $@ $(OBJ) -L. -lpart2

%.o: %.cpp
	$(CXX) -c -o $@ $<

$(LIB): part2.o
	ar rcs $@ $^ part2.h

part2.o: part2.cpp part2.h
	$(CXX) -c -o $@ $<

PHONY: clean
clean:
	rm -f $(EXEC) *.o *.out

help:
	@echo $(TARGETS)

#$<: replaced by the first prerequisite of the rule.
#$^: replaced by the list of all prerequisites of the rule.
#$@: replaced by the target name
#$?: list of prerequisites that are newer than the target is (if target does not exist, they are all considered newer).
