SOURCES = main.cpp part1.cpp part2.cpp
OBJECTS = $(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))
DEPS = $(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.d))
EXE = $(addprefix $(EXE_DIR)/,prog)
CXXFLAGS = -I.

ifeq (${ARCH},host)
CXX = g++
BUILD_DIR = ~/build/host
EXE_DIR = ~/bin/host
endif

ifeq (${ARCH},target)
CXX = arm-rpizw-g++
BUILD_DIR = ~/build/target
EXE_DIR = ~/bin/target
endif

$(EXE): $(DEPS) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

${BUILD_DIR}/%.d: %.cpp
	$(CXX) -MT $(@:.d=.o) -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT $@ -MM $(CXXFLAGS) $< >> $@

${BUILD_DIR}/%.o: %.cpp
	$(CXX) -c -o $@ $<

format: $(SOURCES:.cpp=.format)
%.format: %.cpp
	@echo "Formatting file '$<'"...
	@clang-format -i $<
	@echo "" > $@

tidy: $(SOURCES:.cpp=.tidy)
%.tidy: %.cpp
	@echo "Tidying the file '$<'"...
	@clang-tidy $< -- $(CXXFLAGS)
	@echo "" > $@

clean:
	rm -f $(EXE) $(DEPS) $(OBJECTS)

ifneq ($(filter-out clean format tidy,$(MAKECMDGOALS)),)
-include $(DEPS)
endif
