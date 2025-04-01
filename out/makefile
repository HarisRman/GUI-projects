libs =-lraylib -lm
f :=main

all:
	gcc ../$(f).c -o bin/$(f) $(libs)
debug:
	gcc -g ../$(f).c -o bin/$(f) $(libs)
run_debug:
	gdb bin/$(f)		
clean:
	rm bin/$(f)

run:
	bin/$(f)
