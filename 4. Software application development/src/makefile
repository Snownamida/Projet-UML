main : main.o sensor.o container.o measurment.o
	g++ -o main main.o sensor.o container.o measurment.o

main.o : main.cpp 
	g++ -c main.cpp

sensor.o : sensor.cpp 
	g++ -c sensor.cpp

container.o : container.cpp 
	g++ -c container.cpp

measurment.o : measurment.cpp
	g++ -c measurment.cpp


clean:
	rm main main.o sensor.o container.o