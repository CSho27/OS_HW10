all: prob1.o
	gcc -o prob1 prob1.o -lrt -pthrea
	
prob1.o: prob1.c
	gcc -Wall -Werror -g -c prob1.c -fopenmp
	
clean:
	rm -f *.o
	rm -f prob1