
PRG=mips
SRC=main.cc pipeline_stage.cc context.cc instruction_fetch.cc \
    execution.cc memory_stage.cc write_back.cc instruction_decode.cc \
    register.cc register_file.cc pipeline.cc hazard_unit.cc \
    forwarding_unit.cc

INCLUDEDIR=../include/
LIBDIR=../lib/

M_CXXFLAGS=-std=c++11 -O0 -g -ggdb -Wall -Werror -Wl,--no-as-needed $(CXXFLAGS)
M_LDFLAGS=-ltbb -lrt $(LDFLAGS)

CC=gcc
CXX=g++

OBJ=$(addprefix objs/, $(notdir $(SRC:.cc=.o)))

all : $(PRG)

$(PRG) : $(OBJ)
	$(CXX) $(M_CXXFLAGS) $(addprefix -L, $(LIBDIR)) \
	    $^ -o $@ $(M_LDFLAGS)

objs/%.o : %.c Makefile | objs
	$(CC) $(M_CFLAGS) $(addprefix -I, $(INCLUDEDIR)) -c $< -o $@

objs/%.o : %.cc Makefile | objs
	$(CXX) $(M_CXXFLAGS) $(addprefix -I, $(INCLUDEDIR)) -c $< -o $@

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
