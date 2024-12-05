LIBS := `root-config --libs`
CXXFLAGS :=  `root-config --cflags` -g3 -Wall --pedantic -std=c++20

esercizio4.1: Vel_luce.cpp 
	g++ -o Vel_luce Vel_luce.cpp ${CXXFLAGS} ${LIBS}

clean:
	rm -f esercizio4.1