cc=gcc
cflags=
objects=$(ls | grep cpp | sed 's/\.cpp/\.o/g' )
$(objects):%.o:%.c
	$(cc) -c $(cflags) $< -o $@ 
testcompile:*.o test/*.o
	$(cc) -o *.o test/*.o
all:
