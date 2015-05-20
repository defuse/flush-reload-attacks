set style line 1 lc rgb "blue"

set terminal latex size 8cm,8cm
set output 'distribution.tex'  
set boxwidth 0.5
set style fill solid
set xlabel "Correctly recovered out of 10 trials"
set ylabel "Number of pages"
set notitle
set key off
plot "distribution.dat" using 1:3:xtic(2) with boxes ls 1


