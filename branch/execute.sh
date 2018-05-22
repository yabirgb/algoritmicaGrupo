#!/bin/bash

for i in {3..20}
do
    echo "Generating map $i"
    python src/generarMapa.py $i mapas/mapa$i
done

touch salida_bb.dat
touch salida_back.dat

for i in {3..20}
do
    echo "Executing $i"
    ./bin/bb mapas/mapa$i.tsp mapa$i >> salida_bb.dat
    ./bin/back mapas/mapa$i.tsp mapa$i >> salida_back.dat
done
exit 0
