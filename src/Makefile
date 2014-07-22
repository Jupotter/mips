
PRG=mips
SRC=main.cc pipeline_stage.cc context.cc instruction_fetch.cc \
    execution.cc memory_stage.cc write_back.cc instruction_decode.cc \
    register.cc register_file.cc pipeline.cc hazard_unit.cc \
    forwarding_unit.cc

INCLUDEDIR=../include/
LIBDIR=../lib/

CXXFLAGS=-std=c++11 -O0 -g -ggdb -Wall -Werror -Wl,--no-as-needed -DDEBUG
LDFLAGS=-ltbb -lrt

CC=gcc
CXX=g++

OBJ=$(addprefix objs/, $(notdir $(SRC:.cc=.o)))

all : $(PRG)

$(PRG) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(addprefix -L, $(LIBDIR)) \
	    $^ -o $@ $(LDFLAGS)

objs/%.o : %.c Makefile | objs
	$(CC) $(CFLAGS) $(addprefix -I, $(INCLUDEDIR)) -c $< -o $@

objs/%.o : %.cc Makefile | objs
	$(CXX) $(CXXFLAGS) $(addprefix -I, $(INCLUDEDIR)) -c $< -o $@

objs :
	mkdir -p objs

clean :
	rm -rf objs/
	rm ${PRG}
	rm -rf test/*.result

launch : $(PRG)
	./$(PRG)

test :
	cd test && ./test.sh

.PHONY : all clean launch test
