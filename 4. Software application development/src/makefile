main : main.o sensor.o measurment.o
	g++ -o main main.o sensor.o measurment.o

main.o : main.cpp 
	g++ -c main.cpp

sensor.o : sensor.cpp 
	g++ -c sensor.cpp

measurment.o : measurment.cpp
	g++ -c measurment.cpp

clean:
	rm main *.o