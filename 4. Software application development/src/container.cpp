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


void Container::addSensor(Sensor *sensor)
{
    sensors.push_back(sensor);
}


ostream &operator<<(ostream &os, const Container &container)
{
    for (int i = 0; i < container.sensors.size(); i++)
    {
        os << "Sensor ID: " << container.sensors[i]->getSensorID() << endl;
        os << "Latitude: " << container.sensors[i]->getLatitude() << endl;
        os << "Longitude: " << container.sensors[i]->getLongitude() << endl;
        os << "Measurments: " << endl;
        container.sensors[i]->displayMeasurments();

    }
    return os;
}

Sensor * Container::getSensor(string sensorID)
{
    for (int i = 0; i < sensors.size(); i++)
    {
        if (sensors[i]->getSensorID() == sensorID)
        {
            return sensors[i];
        }
    }
    return NULL;
}

void Container::init()
{
    ofstream file("dataset/falty.csv");
    file << "SensorID,Falty\n";

    //Initialisation des capteurs
    ifstream sensorFile("dataset/sensors.csv");

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

        Sensor * newSensor = new Sensor(id, latitude, longitude);
        this->addSensor(newSensor);
    }

    sensorFile.close();

    //Initialisation des mesures des capteurs
    ifstream measurmentFile("dataset/measurements.csv");

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

        Measurment * measurement = new Measurment(date, idSensor, mollecule, data);
        Sensor * sensor = this->getSensor(idSensor);

        sensor->addMeasurment(measurement);

        
    }

    measurmentFile.close();

    
}

void Container::checkFaltySensors()
{
    for (int i = 0; i < sensors.size(); i++)
    {
        if (sensors[i]->IsFalty(*this))
        {
            cout << "Sensor " << sensors[i]->getSensorID() << " is falty" << endl;
        }
    }
}

