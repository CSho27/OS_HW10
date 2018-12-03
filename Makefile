all: prob1.o prob2.o
	gcc -o prob1 prob1.o -lrt -pthread -lm
	gcc -o prob2 prob2.o -lrt -pthread -lm
	
prob1.o: prob1.c
	gcc -Wall -Werror -g -c prob1.c -fopenmp
	
prob2.o: prob2.c
	gcc -Wall -Werror -g -c prob2.c -fopenmp

clean:
	rm -f *.o
	rm -f prob1
	rm -f prob2