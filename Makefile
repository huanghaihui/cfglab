CXX := clang++
CFLAGS := -Wall `llvm-config --cxxflags` -fno-rtti
LDFLAGS := `llvm-config --ldflags`
LIBS := `llvm-config --libs`
OPT := opt

#name of the library to build
LIBRARYNAME := mycfg.so

TEST_PROGS :=


SRCS :=  callinfo.cpp
OBJS := $(SRCS:%.cc=%.o)

all : $(LIBRARYNAME)

#incude tht makefile implementation stuff


%.o : %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<
             
%.so : callinfo.o
	$(CXX) $(CFLAGS) $(LDFLAGS) -shared -o $@ $^ $(LDFLAGS)
                     
clean :
	rm -f $(OBJS) $(LIBRARYNAME)
                     
test : 
	$(OPT) -load ./mycfg.so < tests/cp.bc > /dev/null
