DEBUG_FLAGS = -g
EXEC_FILE=bottom.exe

bottom.exe: Debug/main.o Debug/bottom.o
	g++ Debug/main.o Debug/bottom.o -o bottom.exe

Debug/bottom.o: bottom.cpp bottom.h
	g++ -c bottom.cpp -o Debug/bottom.o

Debug/main.o: main.cpp
	g++ -c main.cpp -o Debug/main.o

clean:
	rm Debug/*.o bottom.exe 