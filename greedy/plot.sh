
#USO:
#./plot.sh [cheap/near] [mapa sin .tour]

gnuplot <<- EOF 
        set term png
        set output "imagenes/$1_$2.png"
	set terminal pngcairo size 1280,720 enhanced font 'Arial,10'
        plot 'salida/$1_$2.tour' using 2:3 w l
EOF

#gnuplot <<- EOF 
#        set term png
#        set output "$1_$2_ofrecido.png"
#	set terminal pngcairo size 1280,720 enhanced font 'Arial,10'
#	plot '$1_$2_ofrecido.tour' using 2:3 w l
#EOF
