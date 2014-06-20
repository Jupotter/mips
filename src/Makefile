
PRG=mips
SRC=pipeline_stage.cpp context.cpp test_pipeline.cpp instruction_fetch.cpp \
    execution.cpp

INCLUDEDIR=../include/
LIBDIR=../lib/

CXXFLAGS=-std=c++11 -O0 -g -ggdb -Wall -Werror
LDFLAGS=-ltbb -lrt

CC=gcc
CXX=g++

OBJ=$(SRC:.cpp=.o)

all : $(PRG)

$(PRG) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(addprefix -L, $(LIBDIR)) \
	    $(addprefix objs/, $(notdir $^)) -o $@ $(LDFLAGS)

%.o : %.c | objs
	$(CC) $(CFLAGS) $(addprefix -I, $(INCLUDEDIR)) -c $< -o objs/$@

%.o : %.cpp | objs
	$(CXX) $(CXXFLAGS) $(addprefix -I, $(INCLUDEDIR)) -c $< -o objs/$@

objs :
	mkdir -p objs

clean :
	rm -rf objs/
	rm ${PRG}

.PHONY : all clean
