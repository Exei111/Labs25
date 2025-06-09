#ifndef MYCLASS_H
#define MYCLASS_H
#include <iostream>
namespace planets {
class Planet {
public:
    Planet(const char* name, int diameter, int life, int satellites);
    Planet();
    Planet(const Planet& other);
    ~Planet();

    Planet& operator=(const Planet& other);
    bool operator==(const Planet& other);
    bool operator>(const Planet& other);
    friend std::ostream& operator<<(std::ostream& out, const Planet& other);
    friend std::ifstream& operator>>(std::ifstream& in, const Planet& other);


    static void loadFromFile(const char * filename);
    static void sort();
    static void printDb();

    static void addToDb(const char* name, int diameter, int life, int satelites);
    static void addToDb(Planet findPlanet);

    static void removeFromDb(const char* name);
    static void saveToFile();
    static void editDb(const char* name, Planet newValue);

    static int getIndexOfPlanet(Planet findPlanet);
    static int getIndexOfPlanet(const char* findName);


    char* getName();
    int getDiameter();
    int getLife();
    int getSatellites();

    void setName(char* name);
    void setDiameter(int diameter);
    void setLife(int life);
    void setSatelites(int satelites);


private:
    char* name;
    int diameter;
    int life;
    int satellites;


};
}
#endif // MYCLASS_H