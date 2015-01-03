spy: spy.c flushreload.c flushreload.h args.h
	gcc -c flushreload.c -o flushreload.o
	gcc -c spy.c -o spy.o
	gcc -lelf spy.o flushreload.o -o spy

.PHONY: clean
clean:
	rm -f spy spy.o flushreload.o
