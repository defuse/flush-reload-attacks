spy: spy.c flushreload.c flushreload.h args.h cpuid.h elftools.h attacktools.h
	gcc -c flushreload.c -o flushreload.o
	gcc -c spy.c -o spy.o
	gcc spy.o flushreload.o -lelf -o spy

.PHONY: clean
clean:
	rm -f spy spy.o flushreload.o
