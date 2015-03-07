clear
reset
set key off
set border 3
set auto
 
set xrange[0:10]
set xtics 1
 
# Make some suitable labels.
set title "Demo graph"
set xlabel "Page"
set ylabel "Distance"
 
set terminal png enhanced font arial 14 size 800, 600
ft="png"
# Set the output-file name.
set output "distanceplot.png"
 
plot 'values.dat' using 1:2 title 'A', \
     'values.dat' using 1:3 title 'B', \
     'values.dat' using 1:4 title 'C'
