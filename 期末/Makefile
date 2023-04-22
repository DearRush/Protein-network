ALL:calculate.out
function.o: function.cpp lib.h
	g++ -c function.cpp -o function.o
main.o: main.cpp lib.h
	g++ -c main.cpp -o main.o
calculate.out: main.o function.o 
	g++ main.o function.o -o calculate.out 