#if !defined(USER_H)
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class PrivateUser {
public:
  PrivateUser();
  PrivateUser(string UserID, string SensorID);
  string getUserID();
  string getSensorID();
  void setUserID(int UserID);
  void setSensorID(int SensorID);

private:
  string UserID;
  string SensorID;
};

#endif