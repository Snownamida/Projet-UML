#if !defined(Attribute_H)
#define Attribute_H

#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

class Attribute {
public:
  Attribute();
  Attribute(string AttributeID, string Unit, string Description);
  string getAttributeID();
  string getUnit();
  string getDescription();
  void setAttributeID(string AttributeID);
  void setUnit(string Unit);
  void setDescription(string Description);

private:
  string AttributeID;
  string Unit;
  string Description;
};

#endif