
gnuplot <<- EOF 
        set term png
        set output "cheapInserction.png"
	set terminal pngcairo size 1280,720 enhanced font 'Arial,10'
	plot 'salida.tour' using 2:3 w l
EOF

gnuplot <<- EOF 
        set term png
        set output "chsolutionProvided.png"
	set terminal pngcairo size 1280,720 enhanced font 'Arial,10'
	plot 'salida_suya.tour' using 2:3 w l
EOF
