/*************************************************************************
                         Log -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $2024$ par $BP3313$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe  Log> (fichier Log.h) ----------------
#if !defined(Measurment_H)
#define Measurment_H
//--------------------------------------------------- Interfaces utilisées
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <iostream>
#include "container.h"
using namespace std;


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

class Container;

class Measurment {


public:


  Measurment(string date, string sensorID, string attributeID, double value);
  friend ostream &operator<<(ostream &os, const Measurment &measurment);





  // all getters
  string getSensorID() const;
  string getAttributeID()const;
  double getValue()const;
  stamp getDate()const;

  virtual ~Measurment();


protected:

  string sensorID;
  string attributeID;
  double value;
  stamp date;
};


#endif
