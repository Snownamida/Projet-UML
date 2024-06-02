#include "attribute.h"

Attribute::Attribute() {
    AttributeID = "";
    Unit = "";
    Description = "";
}

Attribute::Attribute(string AttributeID, string Unit, string Description) {
    this->AttributeID = AttributeID;
    this->Unit = Unit;
    this->Description = Description;
}

string Attribute::getAttributeID() {
    return AttributeID;
}

string Attribute::getUnit() {
    return Unit;
}

string Attribute::getDescription() {
    return Description;
}

void Attribute::setAttributeID(string AttributeID) {
    this->AttributeID = AttributeID;
}

void Attribute::setUnit(string Unit) {
    this->Unit = Unit;
}

void Attribute::setDescription(string Description) {
    this->Description = Description;
}

