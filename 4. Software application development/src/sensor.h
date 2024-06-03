#if !defined(SENSOR_H)
#define SENSOR_H

#include "measurment.h"
#include <cmath>
#include <fstream>
#include <numeric>
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

class SensorContainer;

// There are 4 measurements (one of each of the 4 types: O3, SO2, NO2, PM10) per
// sensor
class Sensor {
public:
  Sensor();
  Sensor(string sensorID, float latitude, float longitude);

  double distance(Sensor &s2);
  double distanceTo(Sensor &sensor2);
  void addMeasurment(Measurment &measurment);
  void displayMeasurments() const;

  string getSensorID() const { return sensorID; }
  float getLatitude() const { return latitude; }
  float getLongitude() const { return longitude; }
  bool getFalty() const { return falty; }
  vector<Measurment> getMeasurmentsO3() { return measurments_O3; }
  vector<Measurment> getMeasurmentsSO2() { return measurments_SO2; }
  vector<Measurment> getMeasurmentsNO2() { return measurments_NO2; }
  vector<Measurment> getMeasurmentsPM10() { return measurments_PM10; }

  std::vector<Measurment> &operator[](MeasureType type) {
    switch (type) {
    case O3:
      return measurments_O3;
    case SO2:
      return measurments_SO2;
    case PM10:
      return measurments_PM10;
    case NO2:
      return measurments_NO2;
    }
  }

  void setSensorID(string sensorID) { this->sensorID = sensorID; }
  void setLatitude(float latitude) { this->latitude = latitude; }
  void setLongitude(float longitude) { this->longitude = longitude; }
  void setFalty(bool falty) { this->falty = falty; }

  bool isFalty(SensorContainer sensorContainer);

private:
  string sensorID;
  float latitude;
  float longitude;
  bool falty;

  vector<Measurment> measurments_O3;
  vector<Measurment> measurments_SO2;
  vector<Measurment> measurments_NO2;
  vector<Measurment> measurments_PM10;
};



class SensorContainer {
private:
  vector<Sensor> sensors;

public:
  void loadFromFile(const string &sensorFilePath,
                    const string &measurmentFilePath);

  void addSensor(Sensor &sensor);

  friend ostream &operator<<(ostream &os, const SensorContainer &container);

  Sensor &findSensorById(const string &sensorID);

  vector<Sensor> &getSensors() { return sensors; }

  Sensor &operator[](int i) { return sensors[i]; }

  double calculateAirQuality();
};

#endif