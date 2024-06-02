#include "container.h"
#include "sensor.h"
#include "measurment.h"

using namespace std;

Container::Container(/* args */)
{
}

Container::~Container()
{
}

void Container::display()
{
    for (const auto &s : this->sensors)
    {
        cout << "Sensor ID: " << s.getSensorID() << endl;
        cout << "Latitude: " << s.getLatitude() << endl;
        cout << "Longitude: " << s.getLongitude() << endl;
        cout << "Measurments: " << endl;
        for (const auto &m : s.getMeasurments())
        {
            cout << "Attribute ID: " << m.getAttributeID() << endl;
            cout << "Value: " << m.getValue() << endl;
        }
        cout << endl;
    }
}

void Container::init()
{
    //Initialisation des capteurs
    ifstream sensorFile("csv/sensors.csv");

    if (!sensorFile.is_open()) {
        cerr << "Erreur: impossible d'ouvrir le fichier." << endl;
        return;
    }

    string line;

    while (getline(sensorFile, line)) { // Lire le fichier ligne par ligne
        stringstream lineStream(line); // Convertir la ligne en stream
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

        this->sensors.push_back(*(new Sensor(id, latitude, longitude)));
    }

    sensorFile.close();

    //Initialisation des mesures des capteurs
    ifstream measurmentFile("csv/measurements.csv");

    if (!measurmentFile.is_open()) {
        cerr << "Erreur: impossible d'ouvrir le fichier." << endl;
        return;
    }

    while (getline(measurmentFile, line)) { // Lire le fichier ligne par ligne
        stringstream lineStream(line); // Convertir la ligne en stream
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

        Measurment measurement = Measurment(date, idSensor, mollecule, data);
        Sensor s = this->findById(idSensor);

        s.addMeasurement(measurement);
        
    }

    measurmentFile.close();
}

Sensor Container::findById(string id)
{
    for (const auto &s : this->sensors)
    {
        if (s.getSensorID() == id)
        {
            return s;
        }
    }
    return Sensor();

}

double Container::dist_coords(double long1, double lat1, double long2, double lat2) {
    return sqrt(pow(lat1 - lat2, 2) + pow(long1 - long2, 2));
}

Quality Container::calculateQuality(double longi, double lat)
{
    int minDist = INT16_MAX;
    Sensor sensorMin;

    for (const auto &s : this->sensors) {
        double dist = dist_coords(s.getLongitude(), s.getLatitude(), longi, lat);
        if (dist < minDist) {
        minDist = dist;
        sensorMin = s;
        }
    }

    Quality q;
    q.distance = minDist;
    vector<double> moyenneo3;
    vector<double> moyenneso2;
    vector<double> moyenneno2;
    vector<double> moyennepm10;

    for (auto const &m : sensorMin.getMeasurments()) {
        if (m.getAttributeID() == "03") {
        moyenneo3.push_back(m.getValue());
        } else if (m.getAttributeID() == "SO2") {
        moyenneso2.push_back(m.getValue());
        } else if (m.getAttributeID() == "NO2") {
        moyenneno2.push_back(m.getValue());
        } else if (m.getAttributeID() == "PM10") {
        moyennepm10.push_back(m.getValue());
        }

        q.no2 = moyenneno2.size() > 0
                    ? accumulate(moyenneno2.begin(), moyenneno2.end(), 0) /
                        moyenneno2.size()
                    : 0;
        q.o3 = moyenneo3.size() > 0
                    ? accumulate(moyenneo3.begin(), moyenneo3.end(), 0) /
                            moyenneo3.size()
                    : 0;
        q.pm10 = moyennepm10.size() > 0
                    ? accumulate(moyennepm10.begin(), moyennepm10.end(), 0) /
                        moyennepm10.size()
                    : 0;
        q.so2 = moyenneso2.size() > 0
                    ? accumulate(moyenneso2.begin(), moyenneso2.end(), 0) /
                        moyenneso2.size()
                    : 0;
        return q;
    }
    return q;
}