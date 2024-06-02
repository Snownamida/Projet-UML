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

using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe
//
//
//------------------------------------------------------------------------

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
  //----------------------------------------------------------------- PUBLIC

public:
  //----------------------------------------------------- Méthodes publiques

  //-------------------------------------------- Constructeurs - destructeur

  Measurment(string date, string sensorID, string attributeID, double value);


  friend ostream& operator<<(ostream& os, const Measurment& m);

  // all getters
  string getSensorID() const;
  string getAttributeID()const;
  double getValue()const;
  stamp getDate()const;

  virtual ~Measurment();

  //------------------------------------------------------------------ PRIVE

protected:
  //----------------------------------------------------- Méthodes protégées

  //----------------------------------------------------- Attributs protégés
  string sensorID;
  string attributeID;
  double value;
  stamp date;
};

//-------------------------------- Autres définitions dépendantes de  Log>

#endif
