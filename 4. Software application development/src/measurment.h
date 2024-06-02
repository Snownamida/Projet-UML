#if !defined(Measurment_H)
#define Measurment_H

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

using namespace std;

// MeasureType enum
enum MeasureType { O3, SO2, NO2, PM10 };

struct heure {
  int h;
  int m;
  int s;
};

struct stamp {
  heure h;
  int jour;
  int mois;
  int annee;
};

class Measurment {

public:
  Measurment(string date, string sensorID, MeasureType measureType,
             double value);
  friend ostream &operator<<(ostream &os, const Measurment &measurment);

  // all getters
  string getSensorID() const;
  MeasureType getMeasureType() const;
  double getValue() const;
  stamp getDate() const;

protected:
  string sensorID;
  MeasureType measureType;
  double value;
  stamp date;
};

#endif
