#!/bin/bash

NORMAL="\\033[0;39m"
VERT="\\033[1;32m"
ROUGE="\\033[1;31m"

for test in `find . -name '*.test'`; do
    varfile=`echo $test | grep -o "[0-9]\+"`
    ../mips $test > ${varfile}.result
    if diff ${varfile}.result ${varfile}.ref > /dev/null
        then echo -e "[${VERT}OK${NORMAL}] ${varfile}.test"
        else echo -e "[${ROUGE}KO${NORMAL}] ${varfile}.test"
    fi 
done