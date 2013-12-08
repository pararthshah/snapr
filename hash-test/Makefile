#
# Makefile for non-Microsoft compilers
#	tested only on Linux

include ../Makefile.config

HEADER = Engine.h
CPP = Engine.cpp

TEST = GroupParTest HashTest 

all: $(TEST)

# COMPILE
HashTest: HashTest.cpp $(CSNAP)/Snap.o
	$(CC) $(CXXFLAGS) -o $@ $@.cpp $(CSNAP)/Snap.o -I$(CSNAP) -I$(CGLIB) $(LDFLAGS) $(LIBS)

GroupParTest: GroupParTest.cpp $(CSNAP)/Snap.o
	$(CC) $(CXXFLAGS) -o $@ $@.cpp $(CSNAP)/Snap.o -I$(CSNAP) -I$(CGLIB) $(LDFLAGS) $(LIBS)

$(CSNAP)/Snap.o:
	$(MAKE) -C $(CSNAP)

clean:
	rm -f *.o $(TEST) *.exe *.out
	rm -rf Debug Release
	rm -rf *.Err demo*.dat
