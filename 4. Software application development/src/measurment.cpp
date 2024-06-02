

using namespace std;

#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>



#include "measurment.h"




Measurment::Measurment(string date, string sensorID, string attributeID, double value)
{

    string datetime = date;

    int year, month, day, hour, minute, second;
    char dash1, dash2, space, colon1, colon2;
    istringstream datetime_stream(datetime);

    datetime_stream >> year >> dash1 >> month >> dash2 >> day >> space >> hour >> colon1 >> minute >> colon2 >> second;

    stamp s;
    heure h;

    s.annee = year;
    s.mois = month;
    s.jour = day;
    h.h = hour;
    h.m = minute;
    h.s = second;
    s.h = h;

    this->date = s;
    this->sensorID = sensorID;
    this->attributeID = attributeID;
    this->value = value;

}

string Measurment::getSensorID() const
{
    return sensorID;
}

string Measurment::getAttributeID()const
{
    return attributeID;
}

double Measurment::getValue()const
{
    return value;
}

stamp Measurment::getDate() const
{
    return date;
}


Measurment::~Measurment ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Log>" << endl;
#endif
} //----- 


ostream &operator<<(ostream &os, const Measurment &measurment)
{
    os << "Sensor ID: " << measurment.sensorID << endl;
    os << "Attribute ID: " << measurment.attributeID << endl;
    os << "Value: " << measurment.value << endl;
    os << "Date: " << measurment.date.annee << "-" << measurment.date.mois << "-" << measurment.date.jour << " " << measurment.date.h.h << ":" << measurment.date.h.m << ":" << measurment.date.h.s << endl;
    return os;
}

