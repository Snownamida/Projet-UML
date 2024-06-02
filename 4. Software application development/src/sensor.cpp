#include "sensor.h"

string types[] = {"03", "SO2", "NO2", "PM10"};

Sensor::Sensor() {
  sensorID = "";
  latitude = 0;
  longitude = 0;
}

double Sensor::distance(Sensor *capt2) {
  return sqrt(pow(this->getLatitude() - capt2->getLatitude(), 2) +
              pow(this->getLongitude() - capt2->getLongitude(), 2));
}

Sensor::Sensor(string SensorID, float Latitude, float Longitude) {
  this->sensorID = SensorID;
  this->latitude = Latitude;
  this->longitude = Longitude;
  this->falty = false;
}

void Sensor::addMeasurment(Measurment *measurment) {
  measurments.push_back(measurment);
}

void Sensor::displayMeasurments() {
  for (int i = 0; i < measurments.size(); i++) {
    cout << "Measurment ID: " << measurments[i]->getSensorID() << endl;
    cout << "Date: " << measurments[i]->getDate().annee << endl;
    cout << "Sensor ID: " << measurments[i]->getSensorID() << endl;
    cout << "Attribute: " << measurments[i]->getAttributeID() << endl;
    cout << "Value: " << measurments[i]->getValue() << endl;
  }
}

bool Sensor::IsFalty(Container container) {

  printf("Sensor ID: %s\n", this->getSensorID().c_str());

  for (const auto &t : types) {
    vector<double> moyenne;

    for (const auto &m : this->getMeasurments()) {

      if (m->getAttributeID() == t) {
        moyenne.push_back(m->getValue());
      }

      double moyenneMeasurment =
          moyenne.size() > 0
              ? accumulate(moyenne.begin(), moyenne.end(), 0) / moyenne.size()
              : 0;
      int rayon = 150;

      int nbCapt = 0;
      int sum = 0;

      for (const auto &s : container.getSensors()) {
        if (this->distance(s) < rayon &&
            s->getSensorID() != this->getSensorID()) {
          for (const auto &m : s->getMeasurments()) {
            if (m->getAttributeID() == t) {
              sum += m->getValue();
              nbCapt++;
            }
          }
        }
      }

      double moyenneVoisinage = nbCapt > 0 ? sum / nbCapt : 0;
      ofstream file("dataset/falty.csv", ios::app);

      if (moyenneMeasurment < 0.5 * moyenneVoisinage ||
          moyenneMeasurment > 2 * moyenneVoisinage) {
        this->setFalty(true);

        file << this->getSensorID() << ",true\n";
        return true;
      } else {
        file << this->getSensorID() << ",false\n";
        return false;
      }
    }
  }

  return false;
}