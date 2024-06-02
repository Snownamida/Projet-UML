#include "sensor.h"
#include <string>


double Sensor::distance(Sensor capt2) {
  return sqrt(pow(this->getLatitude() - capt2.getLatitude(), 2) +
              pow(this->getLongitude() - capt2.getLongitude(), 2));
}

string types[] = {"03", "SO2", "NO2", "PM10"};

Sensor::Sensor() {
  sensorID = "";
  latitude = 0;
  longitude = 0;
}

Sensor::Sensor(string SensorID, float Latitude, float Longitude) {
  this->sensorID = SensorID;
  this->latitude = Latitude;
  this->longitude = Longitude;
  this->falty = false;
}

// getters
string Sensor::getSensorID() const { return sensorID; }
float Sensor::getLatitude() const { return latitude; }
float Sensor::getLongitude() const { return longitude; }
vector<Measurment> Sensor::getMeasurments() const { return measurments; }

// setters
void Sensor::setSensorID(string SensorID) { this->sensorID = SensorID; }
void Sensor::setLatitude(float Latitude) { this->latitude = Latitude; }
void Sensor::setLongitude(float Longitude) { this->longitude = Longitude; }
void Sensor::setMeasurments(vector<Measurment> measurments) { this->measurments = measurments; }
void Sensor::setFalty(bool falty) { this->falty = falty; }
bool Sensor::IsFalty(vector<Sensor> sensors) {

  for (const auto &t : types) {
    vector<double> moyenne;

    for (const auto &m : this->getMeasurments()) {

      if (m.getAttributeID() == t) {
        moyenne.push_back(m.getValue());
      }

      double moyenneMeasurment =
          moyenne.size() > 0
              ? accumulate(moyenne.begin(), moyenne.end(), 0) / moyenne.size()
              : 0;
      int rayon = 10;

      int nbCapt = 0;
      int sum = 0;

      for (const auto &s : sensors) {
        if (this->distance(s) < rayon &&
            s.getSensorID() != this->getSensorID()) {
          for (const auto &m : s.getMeasurments()) {
            if (m.getAttributeID() == t) {
              sum += m.getValue();
              nbCapt++;
            }
          }
        }
      }

      

      double moyenneVoisinage = nbCapt > 0 ? sum / nbCapt : 0;

      if (moyenneMeasurment < 0.5 * moyenneVoisinage ||
          moyenneMeasurment > 2 * moyenneVoisinage) {
        this->setFalty(true);
        ofstream file("../csv/falty.csv");
        file << "SensorID,Falty\n";
        file << this->getSensorID() << ",true\n";
        return true;
      } else {
        ofstream file("../csv/falty.csv");
        file << "SensorID,Falty\n";
        file << this->getSensorID() << ",false\n";
        return false;
      }
    }
  }

  return false;
}

void Sensor::addMeasurement(Measurment measurement)
{
  (this->measurments).push_back(measurement);
  return ;
}

ostream& operator<<(ostream& os, const Sensor& s) {
    os << "Sensor ID: " << s.getSensorID() << "\n"
       << "(" << s.getLatitude() << ", " << s.getLongitude() << ")\n";    
    return os;
}

Similarity *Sensor::getSimilar(stamp debut, stamp fin, vector<Sensor> sensors) {
  Similarity *sim = new Similarity[sensors.size()];
  int i = 0;

  double moyenneO3Capt;
  double moyenneSO2Capt;
  double moyenneNO2Capt;
  double moyennePM10Capt;

  double moyenneO3_S;
  double moyenneSO2_S;
  double moyenneNO2_S;
  double moyennePM10_S;

  int scoreMoyen = 0;

  for (const auto &m : this->getMeasurments()) {
    if (m.getAttributeID() == "03") {
      moyenneO3Capt += m.getValue();
    }
    if (m.getAttributeID() == "SO2") {
      moyenneSO2Capt += m.getValue();
    }
    if (m.getAttributeID() == "NO2") {
      moyenneNO2Capt += m.getValue();
    }
    if (m.getAttributeID() == "PM10") {
      moyennePM10Capt += m.getValue();
    }
  }

  moyenneO3Capt = moyenneO3Capt / this->getMeasurments().size();
  moyenneSO2Capt = moyenneSO2Capt / this->getMeasurments().size();
  moyenneNO2Capt = moyenneNO2Capt / this->getMeasurments().size();
  moyennePM10Capt = moyennePM10Capt / this->getMeasurments().size();

  for (const auto &s : sensors) {
    if (s.getSensorID() != this->getSensorID()) {
      for (const auto &m : s.getMeasurments()) {
        if (m.getAttributeID() == "03") {
          moyenneO3_S += m.getValue();
        }
        if (m.getAttributeID() == "SO2") {
          moyenneSO2_S += m.getValue();
        }
        if (m.getAttributeID() == "NO2") {
          moyenneNO2_S += m.getValue();
        }
        if (m.getAttributeID() == "PM10") {
          moyennePM10_S += m.getValue();
        }
        moyenneO3_S = moyenneO3_S / s.getMeasurments().size();
        moyenneSO2_S = moyenneSO2_S / s.getMeasurments().size();
        moyenneNO2_S = moyenneNO2_S / s.getMeasurments().size();
        moyennePM10_S = moyennePM10_S / s.getMeasurments().size();
        scoreMoyen = (abs(moyenneO3Capt - moyenneO3_S) +
                      abs(moyenneSO2Capt - moyenneSO2_S) +
                      abs(moyenneNO2Capt - moyenneNO2_S) +
                      abs(moyennePM10Capt - moyennePM10_S)) /
                     4;
        sim[i].captID = s.getSensorID();
        sim[i].score = scoreMoyen;
        i++;
      }
    }
  }
  return sim;
}