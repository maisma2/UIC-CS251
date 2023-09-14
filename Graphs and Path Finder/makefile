build:
	rm -f application.exe
	g++ -std=c++11 -Wall main.cpp dist.cpp osm.cpp tinyxml2.cpp -o application.exe

run:
	./application.exe

buildtest:
	rm -f testing.exe
	cp -f graph.h graphTest/
	g++ -std=c++11 -Wall graphTest/testing.cpp -o testing.exe
	rm -f graphTest/graph.h

runtest:
	./testing.exe
	

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./application.exe
