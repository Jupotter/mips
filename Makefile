
PRG=mips


all : $(PRG)

$(PRG) :
	make -C src/ $@
	mv src/$@ .

clean :
	-rm $(PRG)
	-make -C src clean

.PHONY : all clean
