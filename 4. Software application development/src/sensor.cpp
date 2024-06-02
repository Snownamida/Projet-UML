#include "sensor.h"
#include <vector>

string types[] = {"03", "SO2", "NO2", "PM10"};

static double average(vector<Measurment> measurments) {
  if (measurments.size() == 0) {
    return 0;
  }

  double sum = 0;
  for (int i = 0; i < measurments.size(); i++) {
    sum += measurments[i].getValue();
  }
  return sum / measurments.size();
}

Sensor::Sensor() {
  sensorID = "";
  latitude = 0;
  longitude = 0;
}

double Sensor::distance(Sensor &capt2) {
  return sqrt(pow(latitude - capt2.latitude, 2) +
              pow(longitude - capt2.longitude, 2));
}

Sensor::Sensor(string SensorID, float Latitude, float Longitude) {
  this->sensorID = SensorID;
  this->latitude = Latitude;
  this->longitude = Longitude;
}

void Sensor::addMeasurment(Measurment &measurment) {
  switch (measurment.getMeasureType()) {
  case O3:
    measurments_O3.push_back(measurment);
    break;
  case SO2:
    measurments_SO2.push_back(measurment);
    break;
  case NO2:
    measurments_NO2.push_back(measurment);
    break;
  case PM10:
    measurments_PM10.push_back(measurment);
    break;
  }
}

void Sensor::displayMeasurments() const {
  cout << "O3: " << endl;
  for (int i = 0; i < measurments_O3.size(); i++) {
    cout << measurments_O3[i] << endl;
  }

  cout << "SO2: " << endl;
  for (int i = 0; i < measurments_SO2.size(); i++) {
    cout << measurments_SO2[i] << endl;
  }

  cout << "NO2: " << endl;
  for (int i = 0; i < measurments_NO2.size(); i++) {
    cout << measurments_NO2[i] << endl;
  }

  cout << "PM10: " << endl;
  for (int i = 0; i < measurments_PM10.size(); i++) {
    cout << measurments_PM10[i] << endl;
  }
}

bool Sensor::isFalty(SensorContainer sensorContainer) {

  cout << "Sensor ID: %s" << this->getSensorID() << endl;
  const int RAYON = 150;

  double average_O3 = average(measurments_O3);
  double average_SO2 = average(measurments_SO2);
  double average_NO2 = average(measurments_NO2);
  double average_PM10 = average(measurments_PM10);

  vector<Measurment> measurments_neighbour_O3;
  vector<Measurment> measurments_neighbour_SO2;
  vector<Measurment> measurments_neighbour_NO2;
  vector<Measurment> measurments_neighbour_PM10;

  for (int i = 0; i < sensorContainer.getSensors().size(); i++) {
    if (distance(sensorContainer[i]) < RAYON &&
        sensorID != sensorContainer.getSensors()[i].sensorID) {
      measurments_neighbour_O3.insert(measurments_neighbour_O3.end(),
                                      sensorContainer[i].measurments_O3.begin(),
                                      sensorContainer[i].measurments_O3.end());
      measurments_neighbour_SO2.insert(
          measurments_neighbour_SO2.end(),
          sensorContainer[i].measurments_SO2.begin(),
          sensorContainer[i].measurments_SO2.end());
      measurments_neighbour_NO2.insert(
          measurments_neighbour_NO2.end(),
          sensorContainer[i].measurments_NO2.begin(),
          sensorContainer[i].measurments_NO2.end());
      measurments_neighbour_PM10.insert(
          measurments_neighbour_PM10.end(),
          sensorContainer[i].measurments_PM10.begin(),
          sensorContainer[i].measurments_PM10.end());
    }
  }

  double average_neighbour_O3 = average(measurments_neighbour_O3);
  double average_neighbour_SO2 = average(measurments_neighbour_SO2);
  double average_neighbour_NO2 = average(measurments_neighbour_NO2);
  double average_neighbour_PM10 = average(measurments_neighbour_PM10);

  if (average_O3 < 0.5 * average_neighbour_O3 ||
      average_O3 > 2 * average_neighbour_O3 ||
      average_SO2 < 0.5 * average_neighbour_SO2 ||
      average_SO2 > 2 * average_neighbour_SO2 ||
      average_NO2 < 0.5 * average_neighbour_NO2 ||
      average_NO2 > 2 * average_neighbour_NO2 ||
      average_PM10 < 0.5 * average_neighbour_PM10 ||
      average_PM10 > 2 * average_neighbour_PM10) {

    return true;
  }

  return false;
}

void SensorContainer::addSensor(Sensor &sensor) { sensors.push_back(sensor); }

ostream &operator<<(ostream &os, const SensorContainer &container) {
  for (int i = 0; i < container.sensors.size(); i++) {
    cout << "\033[0;31m" /*red*/ << "\r\n[" << i << "]\033[0m" << endl;
    os << "Sensor ID: " << container.sensors[i].getSensorID() << endl;
    os << "Latitude: " << container.sensors[i].getLatitude() << endl;
    os << "Longitude: " << container.sensors[i].getLongitude() << endl;
    //cout << "\033[0;34m" /*blue*/;
    // os << "\r\nMeasurments: " << endl;
    // container.sensors[i]->displayMeasurments();
    // cout << "\033[0m \r\n"  << endl;
    cout << endl;
  }
  return os;
}

Sensor &SensorContainer::findSensorById(string sensorID) {
  for (int i = 0; i < sensors.size(); i++) {
    if (sensors[i].getSensorID() == sensorID) {
      return sensors[i];
    }
  }
  throw "Sensor not found";
}

void SensorContainer::init() {
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
    this->addSensor(*newSensor);
  }

  sensorFile.close();

  // Initialisation des mesures des capteurs
  ifstream measurmentFile("../dataset/measurements.csv");

  if (!measurmentFile.is_open()) {
    cerr << "Erreur: impossible d'ouvrir le fichier." << endl;
    return;
  }

  while (getline(measurmentFile, line)) { // Lire le fichier ligne par ligne
    stringstream lineStream(line);        // Convertir la ligne en stream
    string cell;

    string date;
    string idSensor;
    MeasureType measureTypem;
    double data;

    // Lire chaque cellule séparée par des points-virgules
    getline(lineStream, cell, ';');
    date = cell;

    getline(lineStream, cell, ';');
    idSensor = cell;

    getline(lineStream, cell, ';');
    if (cell == "O3") {
      measureTypem = O3;
    } else if (cell == "SO2") {
      measureTypem = SO2;
    } else if (cell == "NO2") {
      measureTypem = NO2;
    } else if (cell == "PM10") {
      measureTypem = PM10;
    }

    getline(lineStream, cell, ';');
    data = stod(cell);

    Measurment *measurement =
        new Measurment(date, idSensor, measureTypem, data);

    findSensorById(idSensor).addMeasurment(*measurement);
  }

  measurmentFile.close();
}
