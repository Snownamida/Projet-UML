#include "sensor.h"
#include <chrono>
#include <thread>

using namespace std;

int main(int argc, char *argv[]) {

  SensorContainer sensorContainer;

  sensorContainer.loadFromFile("dataset/sensors.csv",
                               "dataset/measurements.csv");

  for (Sensor &sensor : sensorContainer.getSensors()) {
    sensor.setFalty(sensor.isFalty(sensorContainer));
  }

  ofstream faltyfile("dataset/falty.csv");
  faltyfile << "SensorID,Falty\n";
  for (Sensor &sensor : sensorContainer.getSensors()) {
    faltyfile << sensor.getSensorID() << "," << sensor.getFalty() << endl;
  }
  faltyfile.close();

  double indice = sensorContainer.calculateAirQuality(sensorContainer);

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

    switch (entry) {
    case 0: {
      system("clear");
      return 0;
    }
    case 1:
      // Statistiques generales
      {
        system("clear");

        cout << "INDICE DE QUALITE DE L'AIR : " << indice << "\r\n" << endl;

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

        int nbCapteurs = sensorContainer.getSensors().size();
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

          for (int i = 0; i < sensorContainer.getSensors().size(); i++) {

            if (sensorContainer[i].getFalty() == true) {
              cout << "\033[0;31m" /*red*/;
              cout << "Sensor ID: " << sensorContainer[i].getSensorID();
              cout << "\033[0m" /*default*/ << endl;
              cout << "Latitude: " << sensorContainer[i].getLatitude() << endl;
              cout << "Longitude: " << sensorContainer[i].getLongitude()
                   << "\r\n"
                   << endl;
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
