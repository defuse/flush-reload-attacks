clear
reset
set key off
set border 3
set auto
 
set xrange[0:500]
set xtics 50
 
# Make some suitable labels.
set title "Demo graph"
set xlabel "Value"
set ylabel "Count"
 
set terminal png enhanced font arial 14 size 800, 600
ft="png"
# Set the output-file name.
set output "benchmark.png"
 
set style histogram clustered gap 1
set style fill solid border -1
 
binwidth=5
set boxwidth binwidth
bin(x,width)=width*floor(x/width) + binwidth/2.0
 
plot 'values.dat' using (bin($1,binwidth)):(1.0) smooth freq with boxes
