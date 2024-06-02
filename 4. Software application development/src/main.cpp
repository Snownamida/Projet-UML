#include "container.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>


using namespace std;

int main() {

  Container container;

  /*

  Sensor * sensor = new Sensor("Sensor01", 1.1, 1.5);
  Sensor * sensor2 = new Sensor("Sensor02", 3, 5);
  container.addSensor(sensor);
  container.addSensor(sensor2);

  Measurment * measurment = new Measurment("2021-01-01 12:00:00", "Sensor01",
  "Attribute01", 1.5); Measurment * measurment2 = new Measurment("2022-01-01
  12:00:00", "Sensor02", "Attribute01", 3.5); sensor->addMeasurment(measurment);
  sensor->addMeasurment(measurment2);

  sensor->displayMeasurments();

  */

  container.init();

  container.checkFaltySensors();

  return 0;
}
