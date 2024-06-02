#if !defined(SENSOR_H)
#define SENSOR_H

#include "measurment.h"
#include <cmath>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

class SensorContainer;

class Sensor {
public:
  Sensor();
  Sensor(string sensorID, float latitude, float longitude);

  double distance(Sensor *s2);
  void addMeasurment(Measurment *measurment);
  void displayMeasurments();

  string getSensorID() const { return sensorID; }
  float getLatitude() const { return latitude; }
  float getLongitude() const { return longitude; }
  bool getFalty() const { return falty; }
  vector<Measurment *> getMeasurments() const { return measurments; }

  void setSensorID(string sensorID) { this->sensorID = sensorID; }
  void setLatitude(float latitude) { this->latitude = latitude; }
  void setLongitude(float longitude) { this->longitude = longitude; }
  void setFalty(bool falty) { this->falty = falty; }

  bool IsFalty(SensorContainer sensorContainer);

private:
  string sensorID;
  float latitude;
  float longitude;
  vector<Measurment *> measurments;
  bool falty;
};

struct Quality {
  int o3;
  int so2;
  int no2;
  int pm10;
  int distance;
};

class SensorContainer {
private:
  vector<Sensor *> sensors;

public:
  void init();

  void addSensor(Sensor *sensor);

  friend ostream &operator<<(ostream &os, const SensorContainer &container);

  Sensor *getSensor(string sensorID);

  vector<Sensor *> getSensors() const { return sensors; }

  void checkFaltySensors();
};

#endif