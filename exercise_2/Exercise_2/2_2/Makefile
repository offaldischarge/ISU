SRC = main.cpp part1.cpp part2.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = parts
COMP = g++
TARGETS = all parts part1.o part2.o clean help

.PHONY: all
all: $(EXEC)
$(EXEC): $(OBJ)
	$(COMP) -o $@ $^

%.o: %.cpp
	$(COMP) -c -o $@ $<

PHONY: clean
clean:
	rm -f $(EXEC) *.o *.out *.gch

help:
	@echo $(TARGETS)

#$<: replaced by the first prerequisite of the rule.
#$^: replaced by the list of all prerequisites of the rule.
#$@: replaced by the target name
#$?: list of prerequisites that are newer than the target is (if target does not exist, they are all considered newer).
