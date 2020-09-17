#main
sim_main: main.o simulated_annealing.o test.o
	g++ -o sim simulated_annealing.o test.o main.o

main.o: main.cpp
	g++ -c main.cpp

simulated_annealing.o: simulated_annealing.cpp simulated_annealing.h
	g++ -c simulated_annealing.cpp

test.o: test.cpp test.h
	g++ -c test.cpp

#make clean
clean:
	rm -f sim main.o simulated_annealing.o test.o a.out

#make debug
debug: main.o simulated_annealing.o test.o
	g++ -g3 simulated_annealing.o test.o main.o --debug

#make debug2
debugg: main.cpp simulated_annealing.cpp test.cpp
	g++ -g3 -o sim simulated_annealing.cpp test.cpp main.cpp
