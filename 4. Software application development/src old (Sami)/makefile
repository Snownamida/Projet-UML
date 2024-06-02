main: main.o attribute.o measurment.o sensor.o container.o
	g++ -o main main.o attribute.o measurment.o sensor.o container.o

main.o: main.cpp
	g++ -c main.cpp

attribute.o: attribute.cpp
	g++ -c attribute.cpp

measurment.o: measurment.cpp
	g++ -c measurment.cpp

sensor.o: sensor.cpp
	g++ -c sensor.cpp	

container.o: container.cpp
	g++ -c container.cpp

clean:
	rm -f *.o
	rm -f ../main