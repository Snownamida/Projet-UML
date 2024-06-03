main : output/main.o output/sensor.o output/measurment.o
	c++ -o main output/main.o output/sensor.o output/measurment.o

output/main.o : src/main.cpp src/sensor.h
	c++ -o output/main.o -c src/main.cpp

output/sensor.o : src/sensor.cpp src/sensor.h src/measurment.h
	c++ -o output/sensor.o -c src/sensor.cpp

output/measurment.o : src/measurment.cpp src/measurment.h
	c++ -o output/measurment.o -c src/measurment.cpp

clean:
	rm main output/*.o