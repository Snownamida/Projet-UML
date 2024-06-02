#if !defined(CONTAINER_H)
#define CONTAINER_H

#include "sensor.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>


using namespace std;

struct Quality {
  int o3;
  int so2;
  int no2;
  int pm10;
  int distance;
};

class Sensor;

class Container {
private:
  vector<Sensor *> sensors;

public:
  void init();

  Container(/* args */);

  void addSensor(Sensor *sensor);

  friend ostream &operator<<(ostream &os, const Container &container);

  Sensor *getSensor(string sensorID);

  vector<Sensor *> getSensors() const { return sensors; }

  void checkFaltySensors();

  ~Container();
};

#endif