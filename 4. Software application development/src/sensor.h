#if !defined(SENSOR_H)
#define SENSOR_H

#include <string>
#include <vector>
#include <numeric>
#include <cmath>
#include <fstream>
#include "measurment.h"
using namespace std;

class Measurment;

class Sensor {

public:
    Sensor();
    Sensor(string sensorID, float latitude, float longitude);

    double distance(Sensor *s2);
    void addMeasurment(Measurment * measurment);
    void displayMeasurments();

    string getSensorID() const { return sensorID; }
    float getLatitude() const { return latitude; }
    float getLongitude() const { return longitude; }
    bool getFalty() const { return falty; }
    vector<Measurment*> getMeasurments() const { return measurments; }

    void setSensorID(string sensorID) { this->sensorID = sensorID; }
    void setLatitude(float latitude) { this->latitude = latitude; }
    void setLongitude(float longitude) { this->longitude = longitude; }
    void setFalty(bool falty) { this->falty = falty; }

    bool IsFalty(Container container);
  
private:
  string sensorID;
  float latitude;
  float longitude;
  vector<Measurment*> measurments;
  bool falty;
};

#endif