# Always re-run the benchmark.
.PHONY: benchmark.png
benchmark.png: l1vl3 plotscript.gnuplot
	./l1vl3 > values.dat
	gnuplot plotscript.gnuplot

l1vl3: l1vl3.c
	gcc l1vl3.c -o l1vl3
