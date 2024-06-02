#include "sensor.h"
#include <iostream>
#include <map>
#include <vector>

string types[] = {"03", "SO2", "NO2", "PM10"};

static double sum(vector<Measurment> measurments) {
  double sum = 0;
  for (int i = 0; i < measurments.size(); i++) {
    sum += measurments[i].getValue();
  }
  return sum;
}

static double average(vector<Measurment> measurments) {
  if (measurments.size() == 0) {
    return 0;
  }

  return sum(measurments) / measurments.size();
}

Sensor::Sensor() {
  sensorID = "";
  latitude = 0;
  longitude = 0;
}

static map<pair<string, string>, double> distanceCache;

double Sensor::distance(Sensor &sensor2) {
  auto key = make_pair(sensorID, sensor2.sensorID);
  auto reverseKey = make_pair(sensor2.sensorID, sensorID);

  // 检查缓存中是否已经存在该距离
  if (distanceCache.find(key) != distanceCache.end()) {
    return distanceCache[key];
  }
  if (distanceCache.find(reverseKey) != distanceCache.end()) {
    return distanceCache[reverseKey];
  }

  // Haversine formula
  const double R = 6371e3;             // metres
  double phi1 = latitude * M_PI / 180; // φ, λ in radians
  double phi2 = sensor2.latitude * M_PI / 180;
  double deltaPhi = (sensor2.latitude - latitude) * M_PI / 180;
  double deltaLambda = (sensor2.longitude - longitude) * M_PI / 180;

  double a = sin(deltaPhi / 2) * sin(deltaPhi / 2) + cos(phi1) * cos(phi2) *
                                                         sin(deltaLambda / 2) *
                                                         sin(deltaLambda / 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));

  return R * c; // in metres
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

  const int RAYON = 100000;
  const float SEUIL_MIN = 0.7;
  const float SEUIL_MAX = 1.3;

  double average_O3 = average(measurments_O3);
  double average_SO2 = average(measurments_SO2);
  double average_NO2 = average(measurments_NO2);
  double average_PM10 = average(measurments_PM10);

  double sum_neighbour_O3 = 0;
  unsigned int count_neighbour_O3 = 0;
  double sum_neighbour_SO2 = 0;
  unsigned int count_neighbour_SO2 = 0;
  double sum_neighbour_NO2 = 0;
  unsigned int count_neighbour_NO2 = 0;
  double sum_neighbour_PM10 = 0;
  unsigned int count_neighbour_PM10 = 0;

  for (int i = 0; i < sensorContainer.getSensors().size(); i++) {
    if (distance(sensorContainer[i]) < RAYON &&
        sensorID != sensorContainer.getSensors()[i].sensorID) {
      sum_neighbour_O3 += sum(sensorContainer[i].getMeasurmentsO3());
      count_neighbour_O3 += sensorContainer[i].getMeasurmentsO3().size();
      sum_neighbour_SO2 += sum(sensorContainer[i].getMeasurmentsSO2());
      count_neighbour_SO2 += sensorContainer[i].getMeasurmentsSO2().size();
      sum_neighbour_NO2 += sum(sensorContainer[i].getMeasurmentsNO2());
      count_neighbour_NO2 += sensorContainer[i].getMeasurmentsNO2().size();
      sum_neighbour_PM10 += sum(sensorContainer[i].getMeasurmentsPM10());
      count_neighbour_PM10 += sensorContainer[i].getMeasurmentsPM10().size();
    }
  }

  double average_neighbour_O3 = sum_neighbour_O3 / count_neighbour_O3;
  double average_neighbour_SO2 = sum_neighbour_SO2 / count_neighbour_SO2;
  double average_neighbour_NO2 = sum_neighbour_NO2 / count_neighbour_NO2;
  double average_neighbour_PM10 = sum_neighbour_PM10 / count_neighbour_PM10;

  // cout << "Sensor ID: " << sensorID << endl;
  // cout << "O3: " << average_O3 << " " << average_neighbour_O3 << endl;
  // cout << "SO2: " << average_SO2 << " " << average_neighbour_SO2 << endl;
  // cout << "NO2: " << average_NO2 << " " << average_neighbour_NO2 << endl;
  // cout << "PM10: " << average_PM10 << " " << average_neighbour_PM10 << endl;

  if (average_O3 > average_neighbour_O3 * SEUIL_MAX ||
      average_O3 < average_neighbour_O3 * SEUIL_MIN ||
      average_SO2 > average_neighbour_SO2 * SEUIL_MAX ||
      average_SO2 < average_neighbour_SO2 * SEUIL_MIN ||
      average_NO2 > average_neighbour_NO2 * SEUIL_MAX ||
      average_NO2 < average_neighbour_NO2 * SEUIL_MIN ||
      average_PM10 > average_neighbour_PM10 * SEUIL_MAX ||
      average_PM10 < average_neighbour_PM10 * SEUIL_MIN) {
    cout << "Sensor ID: " << sensorID << " is falty" << endl;
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
    // cout << "\033[0;34m" /*blue*/;
    //  os << "\r\nMeasurments: " << endl;
    //  container.sensors[i]->displayMeasurments();
    //  cout << "\033[0m \r\n"  << endl;
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
    throw runtime_error("Erreur: impossible de lire le fichier sensors.csv");
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
  ifstream measurmentFile("dataset/measurements.csv");

  if (!measurmentFile.is_open()) {
    throw runtime_error(
        "Erreur: impossible de lire le fichier measurements.csv");
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
