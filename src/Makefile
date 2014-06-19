
PRG=mips
SRC=pipeline_stage.cpp context.cpp test_pipeline.cpp

INCLUDEDIR=../include/
LIBDIR=../lib/

CXXFLAGS=-std=c++11 -O0 -Wall -Werror -pthread -ltbb

CC=gcc
CXX=g++

OBJ=$(SRC:.cpp=.o)

all : $(PRG)

$(PRG) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(addprefix -L, $(LIBDIR)) \
	    $(addprefix objs/, $(notdir $^)) -o $@

%.o : %.c | objs
	$(CC) $(CFLAGS) $(addprefix -I, $(INCLUDEDIR)) -c $< -o objs/$@

%.o : %.cpp | objs
	$(CXX) $(CXXFLAGS) $(addprefix -I, $(INCLUDEDIR)) -c $< -o objs/$@

objs :
	mkdir -p objs

clean :
	rm -rf objs/

.PHONY : all clean
