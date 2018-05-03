gnuplot <<- EOF 
  set terminal gif animate delay 50 size 1280,720 enhanced font 'Arial,10'
  set output 'far.gif'
  set key off 
   do for [i=1:21] { 
     plot sprintf('far_%d.tour', i) using 2:3 w l, 'far_21.tour' using 2:3 with points lc rgb "blue" ps 3 
;
  }
EOF
