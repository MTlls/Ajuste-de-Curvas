#!/bin/bash

METRICA="FLOPS_DP ENERGY"
CPU=3

LIKWID_HOME=/home/soft/likwid
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"

PROGRAM="ajustePol"
MAKEFILE="make"
PURGE="purge"

if [ $# -ne 1 ]; then
    echo "O programa não foi chamado com o argumento correto." >&2
    return 1
fi

INPUT_FILE="$1"

make -B CFLAGS="${CFLAGS}"

for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./${PROGRAM} < ${INPUT_FILE} > ${k}.log

    if [ "$k" == "FLOPS_DP" ]; then
        # Extrai o campo DP MFLOP/s e AVX DP MFLOPS/s dos logs do grupo FLOPS_DP

        # Para o primeiro marcador (GERADOR_SL)
        dp_mflops_gera=$(awk '/Region GERACAO_SL, Group 1: FLOPS_DP/,/Region SOLUCAO_SL, Group 1: FLOPS_DP/' ${k}.log | grep -E 'DP \[?MFLOP/s\]?' | sed 's/ //g' | cut -d '|' -f 3)

        # Extrai os respectivos campos
        dp_gera=$(echo "$dp_mflops_gera" | sed -n '1p')
        avx_gera=$(echo "$dp_mflops_gera" | sed -n '2p')

        # Para o segundo marcador (SOLUCAO_SL)
        dp_mflops_solucao=$(awk '/Region SOLUCAO_SL, Group 1: FLOPS_DP/,/Region GERACAO_SL, Group 1: FLOPS_DP/' ${k}.log | grep -E 'DP \[?MFLOP/s\]?' | sed 's/ //g' | cut -d '|' -f 3)
        
        # Extrai os respectivos campos
        dp_solucao=$(echo "$dp_mflops_solucao" | sed -n '1p')
        avx_solucao=$(echo "$dp_mflops_solucao" | sed -n '2p')

    elif [ "$k" == "ENERGY" ]; then
        # Extrai o campo Energy[J] dos logs do grupo ENERGY
        
        # Para o primeiro marcador (GERADOR_SL)
        energy_gera=$(awk '/Region GERACAO_SL, Group 1: ENERGY/,/Region SOLUCAO_SL, Group 1: ENERGY/' ${k}.log | grep -E 'Energy+ \[J\]' | sed 's/ //g' | cut -d '|' -f 3)

        # Para o segundo marcador (SOLUCAO_SL)
        energy_solucao=$(awk '/Region SOLUCAO_SL, Group 1: ENERGY/,/Region GERACAO_SL, Group 1: ENERGY/' ${k}.log | grep -E 'Energy+ \[J\]' | sed 's/ //g' | cut -d '|' -f 3)
    fi
done

# Retorna tudo depois dos dois primeiros intervalos de "..----.."  e imprime tudo antes do proximo "----..."
# Utilizado o FLOPS_DP.log mas podia ser o ENERGY.log
sed '1,/^-*$/d' FLOPS_DP.log | awk '/^-+$/ {exit} {print}'

# Impressao dos resultados
printf '%75s\n' | tr ' ' '-'
echo "[Resultado das Métricas]"

echo "Ao gerar o sistema linear (geraSL)"
printf "%17s %s\n" "DP MFLOP/s:" "$dp_gera"
printf "%17s %s\n" "AVX DP MFLOP/s:" "$avx_gera"
printf "%17s %s\n" "Energy[J]:" "$energy_gera"
echo
echo "Ao solucionar o sistema linear (solSL)"
printf "%17s %s\n" "DP MFLOP/s:" "$dp_solucao"
printf "%17s %s\n" "AVX DP MFLOP/s:" "$avx_solucao"
printf "%17s %s\n" "Energy[J]:" "$energy_solucao"
echo

make purge