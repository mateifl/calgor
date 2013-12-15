GS = -g
EXEC_FILE=bottom.exe
TARGET=Debug
BOOST_INCL="D:/apps/boost_1_54_0"

all: $(TARGET)/pop1.exe $(TARGET)/bottom.exe

#bottom: $(TARGET)/bottom.exe

$(TARGET)/pop1.exe: $(TARGET)/pop1.o
    g++ -O2 $(TARGET)/pop1.o -o $(TARGET)/pop1.exe

$(TARGET)/bottom.exe: $(TARGET)/bottom.o
    g++ $(TARGET)/bottom.o -o $(TARGET)/bottom.exe

$(TARGET)/pop1.o: pop1.cpp
    g++ -c pop1.cpp -o $(TARGET)/pop1.o
       
$(TARGET)/bottom.o: bottom.cpp bottom.h
    g++ -c bottom.cpp -o $(TARGET)/bottom.o

clean:
    rm $(TARGET)/*.o $(TARGET)/bottom.exe $(TARGET)/pop1.exe
