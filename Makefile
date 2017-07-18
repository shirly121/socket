# compiler and options
CXX ?= g++
CXXFLAGS ?= -std=c++11

# needing and generated files 
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = $(patsubst %.cpp, %, $(SRCS))

INC = -I.

# end with .cc
LIB_OBJS = $(patsubst %.cc, %.o, $(wildcard *.cc))
LIB = $(patsubst %.o, lib%.a, $(LIB_OBJS))
LIBPATH = -L.
LIBNAME = $(patsubst %.o, -l%, $(LIB_OBJS))

.PHONY:all clean
all:$(TARGET)

# generate target, sequence is important, if a->b then a before b
$(TARGET):%:%.o $(LIB)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBPATH) $(LIBNAME)

$(OBJS):%.o:%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

# generate static lib
$(LIB):lib%.a:%.o
	ar cr $@ $<

$(LIB_OBJS):%.o:%.cc
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

clean:
	rm  $(TARGET) $(OBJS) $(LIB) $(LIB_OBJS)

#	@for name in $(TARGET);do\
#		$(CXX) $(INC) $(CXXFLAGS) -o $$name $$name.cpp $(wildcard *.cc);\
#done
