#if !defined(SENSOR_H)
#define SENSOR_H

#include "measurment.h"
#include <string>
#include <vector>
#include <numeric>
#include <cmath>
#include <fstream>

struct Quali {
  int o3;
  int so2;
  int no2;
  int pm10;
  int distance;
};

struct Similarity {
  string captID;
  double score;
};

class Sensor {

public:
  Sensor();
  Sensor(string sensorID, float latitude, float longitude);
  string getSensorID() const;
  float getLatitude() const;
  float getLongitude() const;
  vector<Measurment> getMeasurments() const;
  void setSensorID(string sensorID);
  void setLatitude(float latitude);
  void setLongitude(float longitude);
  void setMeasurments(vector<Measurment> measurments);
  void setFalty(bool falty);

  double distance(Sensor s2);

  void addMeasurement(Measurment measurement);

  
  friend ostream& operator<<(ostream& os, const Sensor& s);

  bool IsFalty(vector<Sensor> sensors);
  Similarity*getSimilar(stamp debut, stamp fin, vector<Sensor> sensors);

private:
  string sensorID;
  float latitude;
  float longitude;
  vector<Measurment> measurments;
  bool falty;
};

#endif