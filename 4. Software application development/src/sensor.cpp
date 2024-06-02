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

bool Sensor::IsFalty(SensorContainer sensorContainer) {

  cout << "Sensor ID: %s" << this->getSensorID() << endl;

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

      for (const auto &s : sensorContainer.getSensors()) {
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

void SensorContainer::addSensor(Sensor *sensor) { sensors.push_back(sensor); }

ostream &operator<<(ostream &os, const SensorContainer &container) {
  for (int i = 0; i < container.sensors.size(); i++) {
    os << "Sensor ID: " << container.sensors[i]->getSensorID() << endl;
    os << "Latitude: " << container.sensors[i]->getLatitude() << endl;
    os << "Longitude: " << container.sensors[i]->getLongitude() << endl;
    os << "Measurments: " << endl;
    container.sensors[i]->displayMeasurments();
    cout << endl;
  }
  return os;
}

Sensor *SensorContainer::getSensor(string sensorID) {
  for (int i = 0; i < sensors.size(); i++) {
    if (sensors[i]->getSensorID() == sensorID) {
      return sensors[i];
    }
  }
  return NULL;
}

void SensorContainer::init() {
  ofstream file("dataset/falty.csv");
  file << "SensorID,Falty\n";

  // Initialisation des capteurs
  ifstream sensorFile("dataset/sensors.csv");

  if (!sensorFile.is_open()) {
    cerr << "Erreur: impossible d'ouvrir le fichier." << endl;
    return;
  }

  string line;

  while (getline(sensorFile, line)) { // Lire le fichier ligne par ligne
    stringstream lineStream(line);    // Convertir la ligne en stream
    string cell;

    string id;
    float latitude;
    float longitude;

    // Lire chaque cellule séparée par des points-virgules
    getline(lineStream, cell, ';');
    id = cell;

    getline(lineStream, cell, ';');
    latitude = stof(cell);

    getline(lineStream, cell, ';');
    longitude = stof(cell);

    Sensor *newSensor = new Sensor(id, latitude, longitude);
    this->addSensor(newSensor);
  }

  sensorFile.close();

  // Initialisation des mesures des capteurs
  ifstream measurmentFile("dataset/measurements.csv");

  if (!measurmentFile.is_open()) {
    cerr << "Erreur: impossible d'ouvrir le fichier." << endl;
    return;
  }

  while (getline(measurmentFile, line)) { // Lire le fichier ligne par ligne
    stringstream lineStream(line);        // Convertir la ligne en stream
    string cell;

    string date;
    string idSensor;
    string mollecule;
    double data;

    // Lire chaque cellule séparée par des points-virgules
    getline(lineStream, cell, ';');
    date = cell;

    getline(lineStream, cell, ';');
    idSensor = cell;

    getline(lineStream, cell, ';');
    mollecule = cell;

    getline(lineStream, cell, ';');
    data = stod(cell);

    Measurment *measurement = new Measurment(date, idSensor, mollecule, data);
    Sensor *sensor = this->getSensor(idSensor);

    sensor->addMeasurment(measurement);
  }

  measurmentFile.close();
}
