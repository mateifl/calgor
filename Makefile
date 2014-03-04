DEBUG_FLAGS = -g
DIST_FOLDER = Debug

$(DIST_FOLDER)/anarc08f_list.exe: $(DIST_FOLDER)/anarc08f_list.o
	g++ -g $(DIST_FOLDER)/anarc08f_list.o -o  $(DIST_FOLDER)/anarc08f_list

$(DIST_FOLDER)/anarc08f_list.o: anarc08f_list.cpp 
	g++ -g anarc08f_list.cpp -c  -o $(DIST_FOLDER)/anarc08f_list.o

$(DIST_FOLDER)/anarc08f.exe: $(DIST_FOLDER)/anarc08f.o
	g++ -g $(DIST_FOLDER)/anarc08f.o -o  $(DIST_FOLDER)/anarc08f

$(DIST_FOLDER)/anarc08f.o: anarc08f.cpp 
	g++ -g anarc08f.cpp -c  -o $(DIST_FOLDER)/anarc08f.o

clean:
	rm $(DIST_FOLDER)/*.o $(DIST_FOLDER)/*.exe 