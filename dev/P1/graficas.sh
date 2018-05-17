#!/bin/bash

baseDIR="/home/yabir/Documents/algoritmicaGrupo"
outDIR="/home/yabir/Documents/algoritmicaGrupo/Completo/P1/plots"
nombres=("Norberto" "Javier" "Jose Antonio" "Yábir")

burbuja=("${baseDIR}/Norbi/P1/data/ordenacion/salida_burbuja.dat" "${baseDIR}/Javi/P1/data/burbuja.dat" "${baseDIR}/Jose/P1/output/burbuja_O0.dat" "${baseDIR}/Yabir/P1/output/burbuja_O0.dat")

muchos=""
for ((i=0;i<${#nombres[@]};i++)); do

    nuevo="'${burbuja[i]}' with lines lw 2 title '${nombres[i]}', "
    muchos=$muchos$nuevo
done

level=0
gnuplot <<- EOF
        set xlabel "Tamaño del vector"
        set ylabel "Tiempo (seg)"
        set title "Comparativa algoritmo burbuja -O0"
	set key left top
        set term png
	set grid ytics xtics mytics  # draw lines for each ytics and mytics
	set mytics 2           # set the spacing for the mytics
	set grid               # enable the grid
        set output "${outDIR}/burbuja.png"
        plot ${muchos::-2}
EOF


#
#=======================
#

datos=("${baseDIR}/Norbi/P1/data/ordenacion/salida_insercion.dat" "${baseDIR}/Javi/P1/data/insercion.dat" "${baseDIR}/Jose/P1/output/insercion_O0.dat" "${baseDIR}/Yabir/P1/output/insercion_O0.dat")

muchos=""
for ((i=0;i<${#nombres[@]};i++)); do

    nuevo="'${datos[i]}' with lines lw 2 title '${nombres[i]}', "
    muchos=$muchos$nuevo
done

level=0
gnuplot <<- EOF
        set xlabel "Tamaño del vector"
        set ylabel "Tiempo (seg)"
        set title "Comparativa algoritmo de inserción -O0"
	set key left top
	set grid ytics xtics mytics  # draw lines for each ytics and mytics
	set mytics 2           # set the spacing for the mytics
	set grid               # enable the grid
        set term png
        set output "${outDIR}/insercion.png"
        plot ${muchos::-2}
EOF

#
#=======================
#

datos=("${baseDIR}/Norbi/P1/data/ordenacion/salida_seleccion.dat" "${baseDIR}/Javi/P1/data/seleccion.dat" "${baseDIR}/Jose/P1/output/seleccion_O0.dat" "${baseDIR}/Yabir/P1/output/seleccion_O0.dat")

muchos=""
for ((i=0;i<${#nombres[@]};i++)); do

    nuevo="'${datos[i]}' with lines lw 2 title '${nombres[i]}', "
    muchos=$muchos$nuevo
done

level=0
gnuplot <<- EOF
        set xlabel "Tamaño del vector"
        set ylabel "Tiempo (seg)"
        set title "Comparativa algoritmo de selección -O0"
	set key left top
	set grid ytics xtics mytics  # draw lines for each ytics and mytics
	set mytics 2           # set the spacing for the mytics
	set grid               # enable the grid
        set term png
        set output "${outDIR}/seleccion.png"
        plot ${muchos::-2}
EOF

#
#=======================
#

datos=("${baseDIR}/Norbi/P1/data/ordenacion/salida_mergesort.dat" "${baseDIR}/Javi/P1/data/mergesort2.dat" "${baseDIR}/Jose/P1/output/mergesort_O0.dat" "${baseDIR}/Yabir/P1/output/mergesort_O0.dat")

muchos=""
for ((i=0;i<${#nombres[@]};i++)); do

    nuevo="'${datos[i]}' with lines lw 3 title '${nombres[i]}', "
    muchos=$muchos$nuevo
done

level=0
gnuplot <<- EOF
        set xlabel "Tamaño del vector"
        set ylabel "Tiempo (seg)"
        set title "Comparativa algoritmo mergesort -O0"
	set key left top
	set grid ytics xtics mytics  # draw lines for each ytics and mytics
	set mytics 2           # set the spacing for the mytics
	set grid               # enable the grid
        set term png
        set output "${outDIR}/mergesort.png"
        plot ${muchos::-2}
EOF

#
#=======================
#

datos=("${baseDIR}/Norbi/P1/data/ordenacion/salida_quicksort.dat" "${baseDIR}/Javi/P1/data/quicksort2.dat" "${baseDIR}/Jose/P1/output/quicksort_O0.dat" "${baseDIR}/Yabir/P1/output/quicksort_O0.dat")

muchos=""
for ((i=0;i<${#nombres[@]};i++)); do

    nuevo="'${datos[i]}' with lines lw 2 title '${nombres[i]}', "
    muchos=$muchos$nuevo
done

level=0
gnuplot <<- EOF
        set xlabel "Tamaño del vector"
        set ylabel "Tiempo (seg)"
        set title "Comparativa algoritmo quicksort -O0"
	set key left top
	set grid ytics xtics mytics  # draw lines for each ytics and mytics
	set mytics 2           # set the spacing for the mytics
	set grid               # enable the grid
        set term png
        set output "${outDIR}/quicksort.png"
        plot ${muchos::-2}
EOF

#
#=======================
#

datos=("${baseDIR}/Norbi/P1/data/ordenacion/salida_heapsort.dat" "${baseDIR}/Javi/P1/data/heapsort2.dat" "${baseDIR}/Jose/P1/output/heapsort_O0.dat" "${baseDIR}/Yabir/P1/output/heapsort_O0.dat")

muchos=""
for ((i=0;i<${#nombres[@]};i++)); do

    nuevo="'${datos[i]}' with lines lw 2 title '${nombres[i]}', "
    muchos=$muchos$nuevo
done

level=0
gnuplot <<- EOF
        set xlabel "Tamaño del vector"
        set ylabel "Tiempo (seg)"
        set title "Comparativa algoritmo heapsort -O0"
	set key left top
	set grid ytics xtics mytics  # draw lines for each ytics and mytics
	set mytics 2           # set the spacing for the mytics
	set grid               # enable the grid
        set term png
        set output "${outDIR}/heapsort.png"
        plot ${muchos::-2}
EOF

#
#=======================
#

datos=("${baseDIR}/Norbi/P1/data/salida_floyd.dat" "${baseDIR}/Javi/P1/data/floyd.dat" "${baseDIR}/Jose/P1/output/floyd_O0.dat" "${baseDIR}/Yabir/P1/output/floyd_O0.dat")

muchos=""
for ((i=0;i<${#nombres[@]};i++)); do

    nuevo="'${datos[i]}' with lines lw 2 title '${nombres[i]}', "
    muchos=$muchos$nuevo
done

level=0
gnuplot <<- EOF
        set xlabel "Tamaño del vector"
        set ylabel "Tiempo (seg)"
        set title "Comparativa algoritmo floyd -O0"
	set key left top
	set grid ytics xtics mytics  # draw lines for each ytics and mytics
	set mytics 2           # set the spacing for the mytics
	set grid               # enable the grid
        set term png
        set output "${outDIR}/floyd.png"
        plot ${muchos::-2}
EOF

#
#=======================
#

datos=("${baseDIR}/Norbi/P1/data/salida_hanoi.dat" "${baseDIR}/Javi/P1/data/hanoi.dat" "${baseDIR}/Jose/P1/output/hanoi_O0.dat" "${baseDIR}/Yabir/P1/output/hanoi_O0.dat")

muchos=""
for ((i=0;i<${#nombres[@]};i++)); do

    nuevo="'${datos[i]}' with lines lw 2 title '${nombres[i]}', "
    muchos=$muchos$nuevo
done

level=0
gnuplot <<- EOF
        set xlabel "Tamaño del vector"
        set ylabel "Tiempo (seg)"
        set title "Comparativa algoritmo hanoi -O0"
	set key left top
	set grid ytics xtics mytics  # draw lines for each ytics and mytics
	set mytics 2           # set the spacing for the mytics
	set grid               # enable the grid
        set term png
        set output "${outDIR}/hanoi.png"
        plot ${muchos::-2}
EOF
