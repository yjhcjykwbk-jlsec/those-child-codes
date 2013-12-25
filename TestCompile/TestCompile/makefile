cc=gcc
cflags=
objects=$(ls | grep cpp | sed 's/\.cpp/\.o/g' )
$(objects):%.o:%.c %.h a.h
	$(cc) -c $(cflags) $< -o $@ 
testcompile:a1.o a2.o main.o d.o test/d.o
	$(cc) -o testcompile $^ 
all:
clean:
	rm *.o
