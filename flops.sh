#!/bin/bash

METRICA="FLOPS_DP ENERGY"
CPU=3

LIKWID_HOME=/home/soft/likwid
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"

PROGRAM="ajustePol"
MAKEFILE="make"
PURGE="purge"

if [ $# -ne 2 ]; then
    echo "O programa não foi chamado com o argumento correto." >&2
    return 1
fi

ARG="$1"
INPUT_FILE="$2"

make -B CFLAGS="${CFLAGS}" LFLAGS="${LFLAGS}"

for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./${PROGRAM} ${arg} < ${INPUT_FILE} > ${k}.log
done

echo
grep -E 'fL\(x\)' FLOPS_DP.log
grep -e 'Tempo Lagrange' FLOPS_DP.log | sed 's/$//'
awk '/Region POLINOMIO_1, Group 1: FLOPS_DP/,/Region POLINOMIO_2, Group 1: FLOPS_DP/' FLOPS_DP.log | awk '/DP \[?MFLOP\/s\]?/ && !/AVX DP \[?MFLOP\/s\]?/' | sed 's/ //g' | cut -d '|' -f 3 | sed 's/$/ MFLOP\/s/'
echo

grep -E 'fN\(x\)' FLOPS_DP.log
grep -e 'Tempo Newton' FLOPS_DP.log | sed 's/$//'
awk '/Region POLINOMIO_2, Group 1: FLOPS_DP/,/Region POLINOMIO_1, Group 1: FLOPS_DP/' FLOPS_DP.log | awk '/DP \[?MFLOP\/s\]?/ && !/AVX DP \[?MFLOP\/s\]?/' | sed 's/ //g' | cut -d '|' -f 3 | sed 's/$/ MFLOP\/s/'
echo


make purge