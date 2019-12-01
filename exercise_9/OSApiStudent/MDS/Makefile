# List of files to build
SRCS=MessageDistributionSystem.cpp SubscriberHelper.cpp SubscriberId.cpp Publisher.cpp Subscriber.cpp main.cpp
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)
EXE=main
# The ?= means only set if was not specified on the cmd line - Set for your particular needs!
BASEPATH?=/home/stud/apps/OSApi
# Determine whether this is a debug build or not
ifdef DEBUG
CXXFLAGS=-ggdb -O0
LIBPATH=$(BASEPATH)/lib/host/debug
else
CXXFLAGS=-O2
LIBPATH=$(BASEPATH)/lib/host/release
endif
# Setup the CFLAGS to ensure that the relevant warnings, includes and defines.
CXXFLAGS+=-Wall -D_REENTRANT -DOS_LINUX -I. -I$(BASEPATH)/inc
CXX?=g++


# Then again, note how the flags are NOT part of the linking process
all: $(EXE)

$(EXE): $(DEPS) $(OBJS) 
	@echo "Linking $@"
	@g++ -o main $(OBJS) -L$(LIBPATH) -lOSApi -lrt -lpthread

%.o: %.cpp
	@echo "Compiling $<"
	@$(CXX) -o $@ -c $< $(CXXFLAGS)

%.d: %.cpp 
	@echo "Generating dependency for $<"
	@$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $^ > $@


all: main

clean:
	@echo "Cleaning up..."
	@rm -f $(EXE) $(OBJS) $(DEPS)


-include $(DEPS)
