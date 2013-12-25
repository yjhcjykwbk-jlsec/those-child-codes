addtest:main.o add.o
	gcc -o addtest main.o add.o
add.o:add.c add.h
	gcc -c -o add.o add.c
main.o:main.c
	gcc -c -o main.o main.c
clean:
	-rm -f addtest main.o add.o
