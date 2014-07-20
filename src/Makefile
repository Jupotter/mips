
PRG=mips
SRC=test_pipeline.cpp pipeline_stage.cpp context.cpp instruction_fetch.cpp \
    execution.cpp memory_stage.cpp write_back.cpp instruction_decode.cpp \
    register.cpp register_file.cpp pipeline.cpp

INCLUDEDIR=../include/
LIBDIR=../lib/

CXXFLAGS=-std=c++11 -O0 -g -ggdb -Wall -Werror -Wl,--no-as-needed
LDFLAGS=-ltbb -lrt

CC=gcc
CXX=g++

OBJ=$(addprefix objs/, $(notdir $(SRC:.cpp=.o)))

all : $(PRG)

$(PRG) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(addprefix -L, $(LIBDIR)) \
	    $^ -o $@ $(LDFLAGS)

objs/%.o : %.c | objs
	$(CC) $(CFLAGS) $(addprefix -I, $(INCLUDEDIR)) -c $< -o $@

objs/%.o : %.cpp | objs
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
