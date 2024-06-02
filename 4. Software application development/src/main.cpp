#include "sensor.h"
#include <chrono>
#include <thread>

using namespace std;

int main() {

  SensorContainer sensorContainer;

  sensorContainer.init();

<<<<<<< HEAD
  /*
  Sensor * sensor = new Sensor("Sensor01", 1.1, 1.5);
  Sensor * sensor2 = new Sensor("Sensor02", 3, 5);
  sensorContainer.addSensor(sensor);
  sensorContainer.addSensor(sensor2);
=======
  for (Sensor sensor : sensorContainer.getSensors()) {
    sensor.setFalty(sensor.isFalty(sensorContainer));
  }
>>>>>>> d8da88760b2454b831bb6dd767f70ecedfbc08ac

  ofstream faltyfile("dataset/falty.csv");
  faltyfile << "SensorID,Falty\n";
  for (Sensor sensor : sensorContainer.getSensors()) {
    faltyfile << sensor.getSensorID() << "," << sensor.getFalty() << "\n";
  }
  faltyfile.close();

<<<<<<< HEAD
  sensor->displayMeasurments();
  */
=======
  bool quit = false;
  while (!quit) {
    int entry = -1;
    system("clear");
    cout << "[0] Quitter" << endl;
    cout << "[1] Statistiques generales" << endl;
    cout << "[2] Statistiques personnailsees" << endl;
    cout << "[3] Capteurs defaillants" << endl;
    cout << "\r\nEntrer la selection :\r\n> ";
    cin >> entry;
>>>>>>> d8da88760b2454b831bb6dd767f70ecedfbc08ac

    switch (entry) {
    case 0: {
      system("clear");
      return 0;
    }
    case 1:
      // Statistiques generales
      {
        system("clear");

        /*affichage des stats*/

        while (entry != 0) {
          cout << "Statistiques Generales" << endl;
          cout << "[0] Retour au Menu principal" << endl;
          cout << "Entrer la selection :" << endl;
          cin >> entry;
          cout << endl;
        }
        break;
      }
    case 2:
      // Statistiques personnalisées
      {
        system("clear");
        int selection = 1;

        int nbCapteurs = 10;
        while (selection != 0) {
          cout << "Statistiques personnalisées" << endl;
          cout << "\033[0;31m" /*red*/ << "\r\nCAPTEURS FONCTIONNELS\r\n"
               << "\033[0m" << endl;

          cout << sensorContainer << endl;

          cout << "\r\nSelectionner un capteur de depart :" << endl;
          cout << "[0] Retour au Menu principal" << endl;
          cout << "> ";
          cin >> selection;

          if (selection <= nbCapteurs && selection > 0) {
            system("clear");

            // choix de la zone
            cout
                << "Statistiques personnalisées (Choix de la taille de la zone)"
                << endl;
            cout << "[0] Retour au Menu principal" << endl;
            cout << "\033[0;31m" /*red*/ << "\r\n[1] Petite" << endl;
            cout << "[2] Moyenne" << endl;
            cout << "[3] Grande \r\n"
                 << "\033[0m" /*default*/ << endl;
            cout << "Selectionner une taille de zone :" << endl;
            cout << "> ";
            cin >> selection;

            if (selection <= nbCapteurs && selection > 0) {
              system("clear");

              // choix de la temporalité
              cout << "Statistiques personnalisées (Choix de la temporalité)"
                   << endl;
              cout << "[0] Retour au Menu principal" << endl;
              cout << "\033[0;31m" /*red*/ << "\r\n[1] Instant donne" << endl;
              cout << "[2] Duree donnee \r\n"
                   << "\033[0m" /*default*/ << endl;
              cout << "Selectionner une temporalite :" << endl;
              cout << "> ";
              cin >> selection;

              switch (selection) {
              case 0:
                break;

              case 1:

                break;

              case 2:

                break;

              default:
                break;
              }

              break;

            } else if (selection == 0) {

              break;

            } else {

              cout << "Erreur de saisie, retour au Menu de selection dans :"
                   << endl;
              for (int i = 0; i < 3; i++) {
                cout << "\r" << 3 - i << "s" << flush;
                this_thread::sleep_for(chrono::seconds(1));
              }
            }

          } else if (selection == 0) {
            break;
          } else {
            cout << "Erreur de saisie, retour au Menu de selection dans :"
                 << endl;
            for (int i = 0; i < 3; i++) {
              cout << "\r" << 3 - i << "s" << flush;
              this_thread::sleep_for(chrono::seconds(1));
            }
          }
        }

        break;
      }
    case 3:
      // Capteurs défaillants
      {
        system("clear");

        while (entry != 0) {
          cout << "Cpateurs defaillants" << endl;

<<<<<<< HEAD
          for (int i = 0; i < sensorContainer.getSensors().size(); i++)
          {
            if (sensorContainer.getSensors()[i]->getFalty() == true)
            {
              cout << "Sensor ID: " << sensorContainer.getSensors()[i]->getSensorID() << endl;
              cout << "Latitude: " << sensorContainer.getSensors()[i]->getLatitude() << endl;
              cout << "Longitude: " << sensorContainer.getSensors()[i]->getLongitude() << endl;
=======
          for (int i = 0; i < sensorContainer.getSensors().size(); i++) {
            cout << "passé par là" << endl;

            if (sensorContainer[i].getFalty() == true) {
              cout << "Sensor ID: " << sensorContainer[i].getSensorID() << endl;
              cout << "Latitude: " << sensorContainer[i].getLatitude() << endl;
              cout << "Longitude: " << sensorContainer[i].getLongitude()
                   << endl;
>>>>>>> d8da88760b2454b831bb6dd767f70ecedfbc08ac
            }
          }

          cout << endl;

          cout << "[X] Voir les informations du capteur n°X" << endl;
          cout << "[0] Retour au Menu principal" << endl;
          cout << "Entrer la selection :" << endl;
          cin >> entry;
          cout << endl;
        }
        break;
      }
    default:
      // Erreur de saisie
      {
        system("clear");
        cout << "Erreur de saisie, retour au Menu dans :" << endl;
        for (int i = 0; i < 3; i++) {
          cout << "\r" << 3 - i << "s" << flush;
          this_thread::sleep_for(chrono::seconds(1));
        }
        system("clear");
        break;
      }
    }
  }
  return 0;
}
